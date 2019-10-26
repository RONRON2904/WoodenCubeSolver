#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/cube_tests.h"

void test_init_cube(void){
    struct Cube *cube;
    int size = 4;
    cube = init_cube(cube, size);
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++)
                assert(cube->boxes[(cube->size * i) + (j * cube->size * cube->size) + k].id_piece == -1);

    assert(cube->size == 4);
    assert(cube->nb_boxes_left == 64);

    printf(GREEN "test_init_cube passed !\n" RESET);
}

void test_is_cube_full(void){
    struct Cube *cube;
    int size = 3;
    cube = init_cube(cube, size);
    cube->nb_boxes_left = 0;
    
    assert(is_cube_full(cube));

    printf(GREEN "test_is_cube_full passed !\n" RESET);
}

void test_is_place_occupied(void){
    struct Cube *cube;
    int size = 4;
    cube = init_cube(cube, size);

    int coords[6] = {0, 0, 0, 1, 0, 1};
    assert(!is_place_occupied(cube, coords, 2));
    cube->boxes[(cube->size * 1) + (0 * cube->size * cube->size) + 1].id_piece = 0;
    assert(is_place_occupied(cube, coords, 2));
    
    printf(GREEN "test_is_place_occupied passed !\n" RESET);
} 

void test_fill_boxes(void){
    struct Cube *cube;
    int size = 4;
    cube = init_cube(cube, size);

    assert(cube->nb_boxes_left == 64);
    assert(fill_boxes(cube, 0, 0, 0, 0));
    assert(cube->nb_boxes_left == 63);
    assert(!fill_boxes(cube, 0, 0, 0, 0));
    assert(cube->boxes[(cube->size * 0) + (0 * cube->size * cube->size) + 0].id_piece != -1);
    assert(cube->nb_boxes_left == 63);

    printf(GREEN "test_fill_boxes passed !\n" RESET);
}

int main(void){
    test_init_cube();
    test_is_cube_full();
    test_is_place_occupied();
    test_fill_boxes();
    return EXIT_SUCCESS;
}