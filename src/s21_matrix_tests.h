#ifndef SRC_S21_MATRIX_TESTS_H
#define SRC_S21_MATRIX_TESTS_H

#include <stdlib.h>
#include <time.h>

#include "./s21_matrix.h"
#include "check.h"

Suite *create_matrix_suite(void);
Suite *eq_matrix_suite(void);
Suite *sum_matrix_suite(void);
Suite *sub_matrix_suite(void);
Suite *multn_matrix_suite(void);
Suite *multm_matrix_suite(void);
Suite *transpose_suite(void);
Suite *calc_suite(void);
Suite *determinant_suite(void);
Suite *inverse_suite(void);

#endif
