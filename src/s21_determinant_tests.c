#include "s21_matrix_tests.h"

START_TEST(s21_determinant_matrix_simple_1) {
  int rows = 1;
  int columns = 1;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 5;
  double det = 5;
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(res, det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_matrix_simple_2x2) {
  int rows = 2;
  int columns = 2;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 7;
  double det = 31;
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(res, det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_matrix_simple_3x3) {
  int rows = 3;
  int columns = 3;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 5;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 7;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;
  double det = 55;
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(res, det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_matrix_right) {
  int rows = 4;
  int columns = 4;
  matrix_t A = {0};
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 1;
  A.matrix[0][3] = 5;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 7;
  A.matrix[1][2] = 8;
  A.matrix[1][3] = 6;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;
  A.matrix[2][3] = 3;
  A.matrix[3][0] = 0;
  A.matrix[3][1] = 2;
  A.matrix[3][2] = 0;
  A.matrix[3][3] = 2;
  double det = -44;
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(res, det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_matrix_wrong_numb) {
  int rows = rand() % 10 + 1;
  matrix_t A = {0};
  s21_create_matrix(rows, rows, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      A.matrix[i][j] = 4;
    }
  }
  double det = 5;
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(0, ret);
  ck_assert_double_ne(res, det);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_matrix_w_rc) {
  int rows = rand() % 100 + 1;
  matrix_t A = {0};
  s21_create_matrix(rows, rows + 1, &A);
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(2, ret);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_matrix_null) {
  int rows = rand() % 100 + 1;
  matrix_t A = {0};
  s21_create_matrix(rows, 0, &A);
  double res = 0;
  int ret = s21_determinant(&A, &res);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&A);
}
END_TEST

Suite *determinant_suite(void) {
  Suite *s;
  TCase *tc_determinant;

  s = suite_create("Determinant_matrix");

  tc_determinant = tcase_create("Determinant");

  // s21_determinant_matrix
  tcase_add_test(tc_determinant, s21_determinant_matrix_simple_1);
  tcase_add_test(tc_determinant, s21_determinant_matrix_simple_2x2);
  tcase_add_test(tc_determinant, s21_determinant_matrix_simple_3x3);
  tcase_add_test(tc_determinant, s21_determinant_matrix_right);
  tcase_add_test(tc_determinant, s21_determinant_matrix_wrong_numb);
  tcase_add_test(tc_determinant, s21_determinant_matrix_w_rc);
  tcase_add_test(tc_determinant, s21_determinant_matrix_null);

  suite_add_tcase(s, tc_determinant);

  return s;
}