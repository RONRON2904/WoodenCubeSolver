#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/piece_tests.h"

void test_piece_init(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(p->id == 0);
    assert(p->nb_elementary_cube == 3);
    assert(p->coords[0] == 0);
    assert(p->coords[7] == 1);
    assert(p->is_free);
    printf(GREEN "test_piece_init passed !\n" RESET);
    }

void test_is_piece_beyond_limit(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(!is_piece_beyond_limit(p));
    p->coords[0] = -1;
    assert(is_piece_beyond_limit(p));

    printf(GREEN "test_is_piece_beyond_limit passed !\n" RESET);
}

void test_shift_x_axis(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(shift_x_axis(p, 1));
    assert(p->coords[0] == 1);
    assert(p->coords[1] == 0);

    assert(shift_x_axis(p, -1));
    assert(!shift_x_axis(p, -1));
    assert(p->coords[0] == -1);
    assert(p->coords[1] == 0);

    printf(GREEN "test_shift_x_axis passed !\n" RESET);
}

void test_shift_y_axis(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(shift_y_axis(p, 1));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 1);

    assert(shift_y_axis(p, -1));
    assert(!shift_y_axis(p, -1));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == -1);

    printf(GREEN "test_shift_y_axis passed !\n" RESET);
}

void test_shift_z_axis(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(shift_z_axis(p, 1));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 1);

    assert(shift_z_axis(p, -1));
    assert(!shift_z_axis(p, -1));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == -1);

    printf(GREEN "test_shift_z_axis passed !\n" RESET);
}

void test_rotation_x_axis(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(rotation_x_axis(p));
    assert(p->coords[8] == 1);
    assert(p->coords[7] == 0);
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 1);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 1);

    assert(!rotation_x_axis(p));
    assert(!rotation_x_axis(p));
    assert(rotation_x_axis(p));
    assert(p->coords[8] == 0);
    assert(p->coords[7] == 1);
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 1);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 1);

    printf(GREEN "test_rotation_x_axis passed !\n" RESET);

}
void test_rotation_y_axis(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(!rotation_y_axis(p));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 0);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == -1);
    assert(p->coords[6] == 0);
    assert(p->coords[7] == 1);
    assert(p->coords[8] == -1);

    assert(!rotation_y_axis(p));
    assert(rotation_y_axis(p));
    assert(rotation_y_axis(p));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 1);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 1);
    assert(p->coords[7] == 1);
    assert(p->coords[8] == 0);

    printf(GREEN "test_rotation_y_axis passed !\n" RESET);

}
void test_rotation_z_axis(void){
    struct Piece *p;
    int coords[9] = {0, 0, 0, 1, 0, 0, 1, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    assert(!rotation_z_axis(p));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 0);
    assert(p->coords[4] == 1);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == -1);
    assert(p->coords[7] == 1);
    assert(p->coords[8] == 0);

    assert(!rotation_z_axis(p));
    assert(!rotation_z_axis(p));
    assert(rotation_z_axis(p));
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 1);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 1);
    assert(p->coords[7] == 1);
    assert(p->coords[8] == 0);

    printf(GREEN "test_rotation_z_axis passed !\n" RESET);
}

void test_bring_piece_back(void){
    struct Piece *p;
    int coords[9] = {-1, -2, -2, -2, -2, -2, -2, -2, -3}; 
    p = piece_init(p, 0, 3, coords);

    bring_piece_back(p);

    assert(p->coords[0] == 1);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 1);
    assert(p->coords[3] == 0);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 1);
    assert(p->coords[6] == 0);
    assert(p->coords[7] == 0);
    assert(p->coords[8] == 0);

    int coords2[9] = {1, 2, 2, 2, 2, 2, 2, 2, 3}; 
    p = piece_init(p, 0, 3, coords2);
    
    bring_piece_back(p);

    assert(p->coords[0] == 1);
    assert(p->coords[1] == 2);
    assert(p->coords[2] == 2);
    assert(p->coords[3] == 2);
    assert(p->coords[4] == 2);
    assert(p->coords[5] == 2);
    assert(p->coords[6] == 2);
    assert(p->coords[7] == 2);
    assert(p->coords[8] == 3);

    int coords3[9] = {1, 2, 3, 2, 2, 3, 2, 2, 4}; 
    p = piece_init(p, 0, 3, coords2);
    
    bring_piece_back(p);

    assert(p->coords[0] == 1);
    assert(p->coords[1] == 2);
    assert(p->coords[2] == 2);
    assert(p->coords[3] == 2);
    assert(p->coords[4] == 2);
    assert(p->coords[5] == 2);
    assert(p->coords[6] == 2);
    assert(p->coords[7] == 2);
    assert(p->coords[8] == 3);

    printf(GREEN "test_bring_back_piece passed !\n" RESET);
}

void test_get_piece_limit(void){
    struct Piece *p;
    int coords[9] = {-1, -2, -2, -2, -2, -2, -2, -2, -3}; 
    p = piece_init(p, 0, 3, coords);

    assert(get_piece_limit(p, 0, "max") == -1);
    assert(get_piece_limit(p, 0, "min") == -2);
    assert(get_piece_limit(p, 1, "max") == -2);
    assert(get_piece_limit(p, 1, "min") == -2);
    assert(get_piece_limit(p, 2, "max") == -2);
    assert(get_piece_limit(p, 2, "min") == -3);

    int coords2[9] = {1, 2, 2, 2, 2, 2, 2, 2, 3}; 
    p = piece_init(p, 0, 3, coords2);

    assert(get_piece_limit(p, 0, "max") == 2);
    assert(get_piece_limit(p, 0, "min") == 1);
    assert(get_piece_limit(p, 1, "max") == 2);
    assert(get_piece_limit(p, 1, "min") == 2);
    assert(get_piece_limit(p, 2, "max") == 3);
    assert(get_piece_limit(p, 2, "min") == 2);

    printf(GREEN "test_get_piece_limit passed !\n" RESET);
}

void test_piece_compare(void){
    struct Piece *p1;
    struct Piece *p2;
    struct Piece *p3;
    
    int coords1[9] = {-1, -2, -2, -2, -2, -2, -2, -2, -3}; 
    int coords2[9] = {0, -2, -2, -1, -2, -2, -1, -2, -3};
    int coords3[9] = {-1, -2, -2, -2, -2, -2, -2, -2, -3};
    
    p1 = piece_init(p1, 0, 3, coords1);
    p2 = piece_init(p2, 0, 3, coords2);
    p3 = piece_init(p3, 1, 3, coords3);
    
    assert(!piece_compare(p1, p2));
    assert(piece_compare(p1, p1));
    assert(!piece_compare(p1, p3));

    printf(GREEN "test_piece_compare passed !\n" RESET);
}

int main(){
    test_piece_init();
    test_is_piece_beyond_limit();
    test_shift_x_axis();
    test_shift_y_axis();
    test_shift_z_axis();
    test_rotation_x_axis();
    test_rotation_y_axis();
    test_rotation_z_axis();
    test_bring_piece_back();
    test_get_piece_limit();
    test_piece_compare();

    return EXIT_SUCCESS;
}