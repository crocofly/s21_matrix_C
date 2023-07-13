#include "s21_matrix_tests.h"

START_TEST(s21_multm_matrix_simple) {
  int rowsA = 2;
  int columnsA = 1;
  int columnsB = 2;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(columnsA, columnsB, &B);
  s21_create_matrix(rowsA, columnsB, &C);
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < columnsA; j++) {
      A.matrix[i][j] = i + 2;
    }
  }
  for (int i = 0; i < columnsA; i++) {
    for (int j = 0; j < columnsB; j++) {
      B.matrix[i][j] = j + 1;
    }
  }
  C.matrix[0][0] = 2;
  C.matrix[0][1] = 4;
  C.matrix[1][0] = 3;
  C.matrix[1][1] = 6;
  int ret = s21_mult_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_multm_matrix_right) {
  int rowsA = rand() % 100 + 1;
  int columnsA = rand() % 100 + 1;
  int columnsB = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(columnsA, columnsB, &B);
  s21_create_matrix(rowsA, columnsB, &C);
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < columnsA; j++) {
      double t = rand();
      A.matrix[i][j] = t / 3;
    }
  }
  for (int i = 0; i < columnsA; i++) {
    for (int j = 0; j < columnsB; j++) {
      double t = rand();
      B.matrix[i][j] = t / 5;
    }
  }
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      for (int k = 0; k < A.columns; k++) {
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }
  int ret = s21_mult_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_multm_matrix_wrong_numb) {
  int rowsA = rand() % 100 + 1;
  int columnsA = rand() % 100 + 1;
  int columnsB = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(columnsA, columnsB, &B);
  s21_create_matrix(rowsA, columnsB, &C);
  for (int i = 0; i < rowsA; i++) {
    for (int j = 0; j < columnsA; j++) {
      double t = rand();
      A.matrix[i][j] = t / 3;
    }
  }
  for (int i = 0; i < columnsA; i++) {
    for (int j = 0; j < columnsB; j++) {
      double t = rand();
      B.matrix[i][j] = t / 5;
    }
  }
  int temp = 0;
  for (int i = 0; i < C.rows; i++) {
    for (int j = 0; j < C.columns; j++) {
      for (int k = 0; k < A.columns; k++) {
        temp = A.matrix[i][k] * B.matrix[k][j] + 10;
        C.matrix[i][j] += temp;
      }
    }
  }
  int ret = s21_mult_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(FAILURE, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_multm_matrix_w_rc) {
  int rowsA = rand() % 100 + 1;
  int columnsA = rand() % 100 + 1;
  int columnsB = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(columnsA + 1, columnsB, &B);
  int ret = s21_mult_matrix(&A, &B, &R);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_multm_matrix_null) {
  int rowsA = 0;
  int columnsA = rand() % 100 + 1;
  int columnsB = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  s21_create_matrix(rowsA, columnsA, &A);
  s21_create_matrix(columnsA, columnsB, &B);
  int ret = s21_mult_matrix(&A, &B, &R);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *multm_matrix_suite(void) {
  Suite *s;
  TCase *tc_multm;

  s = suite_create("Multm_matrix");

  tc_multm = tcase_create("Multm");

  // s21_multm_matrix
  tcase_add_test(tc_multm, s21_multm_matrix_simple);
  tcase_add_test(tc_multm, s21_multm_matrix_right);
  tcase_add_test(tc_multm, s21_multm_matrix_wrong_numb);
  tcase_add_test(tc_multm, s21_multm_matrix_w_rc);
  tcase_add_test(tc_multm, s21_multm_matrix_null);

  suite_add_tcase(s, tc_multm);

  return s;
}