#include "s21_matrix_tests.h"

START_TEST(s21_sub_matrix_right) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 3;
      B.matrix[i][j] = t / 5;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  int ret = s21_sub_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_wrong_numb) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 3;
      B.matrix[i][j] = t / 5;
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j] + 1;
    }
  }
  int ret = s21_sub_matrix(&A, &B, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(FAILURE, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_matrix_w_r) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows + 1, columns, &B);
  int ret = s21_sub_matrix(&A, &B, &R);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_w_c) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns + 1, &A);
  s21_create_matrix(rows, columns, &B);
  int ret = s21_sub_matrix(&A, &B, &R);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sub_matrix_null) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  int ret = s21_sub_matrix(&A, &B, &R);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *sub_matrix_suite(void) {
  Suite *s;
  TCase *tc_sub;

  s = suite_create("Sub_matrix");

  tc_sub = tcase_create("Sub");

  // s21_sub_matrix
  tcase_add_test(tc_sub, s21_sub_matrix_right);
  tcase_add_test(tc_sub, s21_sub_matrix_wrong_numb);
  tcase_add_test(tc_sub, s21_sub_matrix_w_r);
  tcase_add_test(tc_sub, s21_sub_matrix_w_c);
  tcase_add_test(tc_sub, s21_sub_matrix_null);

  suite_add_tcase(s, tc_sub);

  return s;
}