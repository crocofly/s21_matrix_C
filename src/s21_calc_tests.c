#include "s21_matrix_tests.h"

START_TEST(s21_calc_matrix_simple_2x2) {
  int rows = 2;
  int columns = 2;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 7;
  C.matrix[0][0] = 7;
  C.matrix[0][1] = -4;
  C.matrix[1][0] = -1;
  C.matrix[1][1] = 5;
  int ret = s21_calc_complements(&A, &R);
  ck_assert_int_eq(0, ret);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_matrix_simple_3x3) {
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
  C.matrix[0][1] = -10;
  C.matrix[0][2] = 5;
  C.matrix[1][0] = -2;
  C.matrix[1][1] = 21;
  C.matrix[1][2] = -9;
  C.matrix[2][0] = 1;
  C.matrix[2][1] = -8;
  C.matrix[2][2] = 2;
  int ret = s21_calc_complements(&A, &R);
  ck_assert_int_eq(0, ret);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_calc_matrix_right) {
  int rows = rand() % 10 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, rows, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      double t = rand();
      A.matrix[i][j] = t / 7;
    }
  }
  int ret = s21_calc_complements(&A, &R);
  ck_assert_int_eq(0, ret);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(s21_calc_matrix_w_rc) {
  int rows = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, rows + 1, &A);
  int ret = s21_calc_complements(&A, &R);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_matrix_null) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t A = {0};
  matrix_t R = {0};
  s21_create_matrix(rows, columns, &A);
  int ret = s21_calc_complements(&A, &R);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_minor_r) {
  int rows = 3;
  matrix_t A = {0};
  matrix_t R = {0};
  matrix_t C = {0};
  s21_create_matrix(rows, rows, &A);
  s21_create_matrix(A.rows - 1, A.columns - 1, &C);
  s21_create_matrix(A.rows - 1, A.columns - 1, &R);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  C.matrix[0][0] = 1;
  C.matrix[0][1] = 3;
  C.matrix[1][0] = 7;
  C.matrix[1][1] = 9;
  s21_minor(&A, 1, 1, &R);
  int res = s21_eq_matrix(&C, &R);
  ck_assert_int_eq(SUCCESS, res);
  s21_remove_matrix(&A);
}
END_TEST

Suite *calc_suite(void) {
  Suite *s;
  TCase *tc_calc;

  s = suite_create("Calc_matrix");

  tc_calc = tcase_create("Calc");

  // s21_calc_matrix
  tcase_add_test(tc_calc, s21_calc_matrix_simple_2x2);
  tcase_add_test(tc_calc, s21_calc_matrix_simple_3x3);
  tcase_add_test(tc_calc, s21_calc_matrix_right);
  tcase_add_test(tc_calc, s21_calc_matrix_w_rc);
  tcase_add_test(tc_calc, s21_calc_matrix_null);
  tcase_add_test(tc_calc, s21_minor_r);
  suite_add_tcase(s, tc_calc);

  return s;
}