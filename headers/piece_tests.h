#ifndef PIECE_TESTS_H
#define PIECE_TESTS_H

#include "piece.h"


#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

void test_is_piece_beyond_limit(void);
void test_piece_init(void);

void test_shift_x_axis(void); 
void test_shift_y_axis(void);
void test_shift_z_axis(void);

void test_rotation_x_axis(void); 
void test_rotation_y_axis(void);
void test_rotation_z_axis(void);

void test_bring_piece_back(void);

void test_get_piece_limit(void);

void test_piece_compare(void);

#endif