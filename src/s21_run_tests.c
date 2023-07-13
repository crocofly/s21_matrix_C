#include "./s21_matrix_tests.h"

int main(void) {
  int no_failed;
  Suite *s, *ss, *sss, *ssss, *sssss;
  Suite *n, *nn, *nnn, *nnnn, *nnnnn;
  SRunner *runner;

  s = create_matrix_suite();
  ss = eq_matrix_suite();
  sss = sum_matrix_suite();
  ssss = sub_matrix_suite();
  sssss = multn_matrix_suite();
  n = multm_matrix_suite();
  nn = transpose_suite();
  nnn = determinant_suite();
  nnnn = calc_suite();
  nnnnn = inverse_suite();

  runner = srunner_create(s);
  srunner_add_suite(runner, ss);
  srunner_add_suite(runner, sss);
  srunner_add_suite(runner, ssss);
  srunner_add_suite(runner, sssss);
  srunner_add_suite(runner, n);
  srunner_add_suite(runner, nn);
  srunner_add_suite(runner, nnn);
  srunner_add_suite(runner, nnnn);
  srunner_add_suite(runner, nnnnn);

  srunner_run_all(runner, CK_NORMAL);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return no_failed == 0 ? 0 : 1;
}