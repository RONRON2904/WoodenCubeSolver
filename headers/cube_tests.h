#ifndef CUBE_TESTS_H
#define CUBE_TESTS_H

#include "cube.h"


#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"

void test_init_cube(void);
void test_is_cube_full(void);
void test_is_place_occupied(void); 
void test_fill_boxes(void);

#endif