#include "s21_matrix_tests.h"

START_TEST(s21_transpose_matrix_right) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 7;
      C.matrix[j][i] = t / 7;
    }
  }
  int ret = s21_transpose(&A, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_transpose_matrix_wrong) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 7;
      C.matrix[j][i] = t / 7 + 1;
    }
  }
  int ret = s21_transpose(&A, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(FAILURE, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_transpose_matrix_null) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  int ret = s21_transpose(&A, &R);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s;
  TCase *tc_transpose;

  s = suite_create("Transpose_matrix");

  tc_transpose = tcase_create("Transpose");

  // s21_transpose_matrix
  tcase_add_test(tc_transpose, s21_transpose_matrix_right);
  tcase_add_test(tc_transpose, s21_transpose_matrix_wrong);
  tcase_add_test(tc_transpose, s21_transpose_matrix_null);

  suite_add_tcase(s, tc_transpose);

  return s;
}