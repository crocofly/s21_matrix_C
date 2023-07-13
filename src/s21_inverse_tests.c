#include "s21_matrix_tests.h"

START_TEST(s21_inverse_matrix_simple_1) {
  int rows = 1;
  int columns = 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 5;
  int ret = s21_inverse_matrix(&A, &R);
  double inv = 0.2;
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(inv, R.matrix[0][0]);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(s21_inverse_matrix_simple_2x2) {
  int rows = 2;
  int columns = 2;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 1;

  C.matrix[0][0] = -0.2;
  C.matrix[0][1] = 0.4;
  C.matrix[1][0] = 0.8;
  C.matrix[1][1] = -0.6;
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(0, ret);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_inverse_matrix_simple_3x3) {
  int rows = 3;
  int columns = 3;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  A.matrix[0][0] = 6;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 1;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 4;
  C.matrix[0][0] = 0;
  C.matrix[0][1] = 0.4;
  C.matrix[0][2] = -0.2;
  C.matrix[1][0] = 2;
  C.matrix[1][1] = -4.2;
  C.matrix[1][2] = 1.6;
  C.matrix[2][0] = -1;
  C.matrix[2][1] = 1.8;
  C.matrix[2][2] = -0.4;
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(0, ret);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_inverse_matrix_det_0) {
  int rows = 2;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, rows, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      A.matrix[i][j] = 7;
    }
  }
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_wrong_2x2) {
  int rows = 2;
  int columns = 2;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  A.matrix[0][0] = 3;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 1;
  C.matrix[0][0] = 0;
  C.matrix[0][1] = 0;
  C.matrix[1][0] = 0.8;
  C.matrix[1][1] = -0.6;
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(0, ret);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(FAILURE, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_inverse_matrix_w_rc) {
  int rows = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, rows + 1, &A);
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_null) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  int ret = s21_inverse_matrix(&A, &R);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
}
END_TEST

Suite *inverse_suite(void) {
  Suite *s;
  TCase *tc_inverse;

  s = suite_create("Inverse_matrix");

  tc_inverse = tcase_create("Inverse");

  // s21_inverse_matrix
  tcase_add_test(tc_inverse, s21_inverse_matrix_simple_1);
  tcase_add_test(tc_inverse, s21_inverse_matrix_simple_2x2);
  tcase_add_test(tc_inverse, s21_inverse_matrix_det_0);
  tcase_add_test(tc_inverse, s21_inverse_matrix_simple_3x3);
  tcase_add_test(tc_inverse, s21_inverse_matrix_wrong_2x2);
  tcase_add_test(tc_inverse, s21_inverse_matrix_w_rc);
  tcase_add_test(tc_inverse, s21_inverse_matrix_null);

  suite_add_tcase(s, tc_inverse);

  return s;
}