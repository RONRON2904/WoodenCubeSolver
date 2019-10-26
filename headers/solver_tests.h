#ifndef SOLVER_TESTS_H
#define SOLVER_TESTS_H

#include "solver.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

void test_comb_init(void);
void test_shift(void);
void test_rotate(void);
void test_insert_new_piece(void);
void test_piece_exist(void);
void test_place_available(void);
void test_find_all_rotated_combinations(void);
void test_find_all_shifted_combinations(void);
void test_get_comb_indices(void);
void test_get_global_index(void);
void test_find_next_index(void);
void test_find_all_combinations(void);

#endif