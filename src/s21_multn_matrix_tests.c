#include "s21_matrix_tests.h"

START_TEST(s21_multn_matrix_right) {
  double number = (rand() % 100 + 1) / 3;
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 2;
      C.matrix[i][j] = number * A.matrix[i][j];
    }
  }
  int ret = s21_mult_number(&A, number, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_multn_matrix_wrong_numb) {
  double number = (rand() % 100 + 1) / 3;
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      A.matrix[i][j] = t / 2;
      C.matrix[i][j] = number * A.matrix[i][j] * 2;
    }
  }
  int ret = s21_mult_number(&A, number, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(FAILURE, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_multn_matrix_null) {
  double number = (rand() % 100 + 1) / 3;
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  int ret = s21_mult_number(&A, number, &R);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
}
END_TEST

Suite *multn_matrix_suite(void) {
  Suite *s;
  TCase *tc_multn;

  s = suite_create("Multn_matrix");

  tc_multn = tcase_create("Multn");

  // s21_multn_matrix
  tcase_add_test(tc_multn, s21_multn_matrix_right);
  tcase_add_test(tc_multn, s21_multn_matrix_wrong_numb);
  tcase_add_test(tc_multn, s21_multn_matrix_null);

  suite_add_tcase(s, tc_multn);

  return s;
}