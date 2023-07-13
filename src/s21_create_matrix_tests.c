#include "s21_matrix_tests.h"

START_TEST(s21_create_matrix_right) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  int ret = s21_create_matrix(rows, columns, &M);
  ck_assert_int_eq(0, ret);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      M.matrix[i][j] = t / 3;
      ck_assert_ldouble_eq_tol(t / 3, M.matrix[i][j], 10e-7);
    }
  }
  ck_assert_int_eq(M.rows, rows);
  ck_assert_int_eq(M.columns, columns);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(s21_create_matrix_wrong1) {
  int rows = 0;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  int ret = s21_create_matrix(rows, columns, &M);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(s21_create_matrix_wrong2) {
  int rows = rand() % 100 + 1;
  int columns = 0;
  matrix_t M = {0};
  int ret = s21_create_matrix(rows, columns, &M);
  ck_assert_int_eq(1, ret);
  s21_remove_matrix(&M);
}
END_TEST

START_TEST(s21_create_matrix_wrong3) {
  int rows = rand() % 100 + 1;
  int columns = rand() % 100 + 1;
  matrix_t M = {0};
  int ret = s21_create_matrix(rows, columns, &M);
  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(M.rows, rows);
  ck_assert_int_eq(M.columns, columns);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double t = rand();
      M.matrix[i][j] = t / 5;
      ck_assert_ldouble_eq_tol(t / 5, M.matrix[i][j], 10e-7);
    }
  }
  s21_remove_matrix(&M);
}
END_TEST

Suite *create_matrix_suite(void) {
  Suite *s;
  TCase *tc_mcreate;

  s = suite_create("Create_matrix");

  tc_mcreate = tcase_create("create");

  // s21_create_matrix
  tcase_add_test(tc_mcreate, s21_create_matrix_right);
  tcase_add_test(tc_mcreate, s21_create_matrix_wrong1);
  tcase_add_test(tc_mcreate, s21_create_matrix_wrong2);
  tcase_add_test(tc_mcreate, s21_create_matrix_wrong3);

  suite_add_tcase(s, tc_mcreate);

  return s;
}
