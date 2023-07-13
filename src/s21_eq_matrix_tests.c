#include "s21_matrix_tests.h"

START_TEST(s21_eq_matrix_simple) {
  int rows = 3;
  int columns = 3;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      M.matrix[i][j] = i;
      N.matrix[i][j] = i + 1;
    }
  }
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(FAILURE, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

START_TEST(s21_eq_matrix_right) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      M.matrix[i][j] = t / 3;
      N.matrix[i][j] = t / 3;
    }
  }
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(SUCCESS, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

START_TEST(s21_eq_matrix_wrong_numb) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      M.matrix[i][j] = t / 3;
      N.matrix[i][j] = t / 7;
    }
  }
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(FAILURE, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

START_TEST(s21_eq_matrix_w_r) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows + 1, columns, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      M.matrix[i][j] = t / 3;
      N.matrix[i][j] = t / 3;
    }
  }
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(FAILURE, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

START_TEST(s21_eq_matrix_w_c) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns + 1, &N);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      M.matrix[i][j] = t / 3;
      N.matrix[i][j] = t / 3;
    }
  }
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(FAILURE, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

START_TEST(s21_eq_matrix_null) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  matrix_t N = {0};
  s21_create_matrix(rows, columns, &M);
  s21_create_matrix(rows, columns, &N);
  int ret = s21_eq_matrix(&M, &N);
  ck_assert_int_eq(FAILURE, ret);
  s21_remove_matrix(&M);
  s21_remove_matrix(&N);
}
END_TEST

Suite *eq_matrix_suite(void) {
  Suite *s;
  TCase *tc_eq;

  s = suite_create("Eq_matrix");

  tc_eq = tcase_create("Eq");

  // s21_eq_matrix
  tcase_add_test(tc_eq, s21_eq_matrix_simple);
  tcase_add_test(tc_eq, s21_eq_matrix_right);
  tcase_add_test(tc_eq, s21_eq_matrix_wrong_numb);
  tcase_add_test(tc_eq, s21_eq_matrix_w_r);
  tcase_add_test(tc_eq, s21_eq_matrix_w_c);
  tcase_add_test(tc_eq, s21_eq_matrix_null);

  suite_add_tcase(s, tc_eq);

  return s;
}