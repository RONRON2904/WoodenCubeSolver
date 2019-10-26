#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/solver_tests.h"

void test_comb_init(void){
    struct Combinations * comb;
    comb = comb_init(comb);
    assert(comb->nb_combinations == 0);
    assert(comb != NULL);
    assert(comb->piece_combinations == NULL);

    printf(GREEN "test_comb_init passed !\n" RESET);
}

void test_shift(void){
    struct Piece *p;
    int coords[9] = {2, 0, 0, 3, 0, 0, 3, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    shift(p, 0);
    assert(p->coords[0] == 0);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 1);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 1);
    assert(p->coords[7] == 1);
    assert(p->coords[8] == 0);

    shift(p, 0);
    assert(p->coords[0] == 1);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 2);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 2);
    assert(p->coords[7] == 1);
    assert(p->coords[8] == 0);

    shift(p, 1);
    assert(p->coords[0] == 1);
    assert(p->coords[1] == 1);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 2);
    assert(p->coords[4] == 1);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 2);
    assert(p->coords[7] == 2);
    assert(p->coords[8] == 0);

    shift(p, 1);
    assert(p->coords[0] == 1);
    assert(p->coords[1] == 2);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 2);
    assert(p->coords[4] == 2);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 2);
    assert(p->coords[7] == 3);
    assert(p->coords[8] == 0);

    printf(GREEN "test_shift passed !\n" RESET);
}

void test_rotate(void){
    struct Piece *p;
    int coords[9] = {2, 0, 0, 3, 0, 0, 3, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    rotate(p, 0);
    assert(p->coords[0] == 2);
    assert(p->coords[1] == 0);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 3);
    assert(p->coords[4] == 0);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 3);
    assert(p->coords[7] == 0);
    assert(p->coords[8] == 1);

    rotate(p, 0);
    assert(p->coords[0] == 2);
    assert(p->coords[1] == 1);
    assert(p->coords[2] == 0);
    assert(p->coords[3] == 3);
    assert(p->coords[4] == 1);
    assert(p->coords[5] == 0);
    assert(p->coords[6] == 3);
    assert(p->coords[7] == 0);
    assert(p->coords[8] == 0);

    printf(GREEN "test_rotate passed !\n" RESET);
}

void test_insert_new_piece(void){
    struct Combinations * comb;
    comb = comb_init(comb);

    struct Piece *p;
    int coords[9] = {2, 0, 0, 3, 0, 0, 3, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    comb = insert_new_piece(p, comb);

    assert(comb->nb_combinations == 1);
    assert(piece_compare(p, comb->piece_combinations[0]));

    int coords2[9] = {1, 1, 0, 1, 0, 0, 2, 0, 0}; 
    p = piece_init(p, 0, 3, coords2);
    comb = insert_new_piece(p, comb);

    assert(comb->nb_combinations == 2);
    assert(piece_compare(p, comb->piece_combinations[1]));

    printf(GREEN "test_insert_new_piece passed !\n" RESET);
}

void test_piece_exist(void){
    struct Combinations * comb;
    comb = comb_init(comb);

    struct Piece *p;
    int coords[9] = {2, 0, 0, 3, 0, 0, 3, 1, 0}; 
    p = piece_init(p, 0, 3, coords);

    comb = insert_new_piece(p, comb);

    assert(piece_exist(comb, p));

    int coords2[9] = {1, 1, 0, 1, 0, 0, 2, 0, 0}; 
    p = piece_init(p, 0, 3, coords2);

    assert(!piece_exist(comb, p));

    printf(GREEN "test_piece_exist passed !\n" RESET);
}

void test_place_available(void){
    struct Cube *cube; 
    cube = init_cube(cube, 4);

    struct Piece *p;
    int coords[9] = {2, 0, 0, 3, 0, 0, 3, 1, 0}; 
    p = piece_init(p, 0, 3, coords);
    assert(place_available(cube, p));

    cube->boxes[(cube->size * 3) + (1 * cube->size * cube->size) + 0].id_piece = 1;
    assert(!place_available(cube, p));

    printf(GREEN "test_place_available passed !\n" RESET);
}

void test_find_all_rotated_combinations(void){
    struct Combinations * comb;
    comb = comb_init(comb);

    struct Piece *p;

    int coords[6] = {0, 0, 0, 1, 0, 0};
    p = piece_init(p, 0, 2, coords);

    comb = find_all_rotated_combinations(comb, p);
    assert(comb->nb_combinations == 3);

    comb = comb_init(comb);
    int coords3[9] = {0, 0, 0, 1, 0, 0, 1, 0, 1};
    p = piece_init(p, 0, 3, coords3);

    comb = find_all_rotated_combinations(comb, p);
    assert(comb->nb_combinations == 12);

    printf(GREEN "test_find_all_shifted_combinations passed !\n" RESET);
}

void test_find_all_shifted_combinations(void){
    struct Combinations * comb;
    comb = comb_init(comb);

    struct Piece *p;
    
    int coords1[3] = {0, 0, 0}; 
    p = piece_init(p, 0, 1, coords1);

    comb = find_all_shifted_combinations(comb, p);
    assert(comb->nb_combinations == 64);
    
    comb = comb_init(comb);
    int coords2[6] = {0, 0, 0, 1, 0, 0};
    p = piece_init(p, 0, 2, coords2);
    
    comb = find_all_shifted_combinations(comb, p);
    assert(comb->nb_combinations == 48);

    comb = comb_init(comb);
    int coords3[9] = {0, 0, 0, 1, 0, 0, 1, 0, 1};
    p = piece_init(p, 0, 3, coords3);
    
    comb = find_all_shifted_combinations(comb, p);
    assert(comb->nb_combinations == 36);

    int coords4[6] = {0, 0, 0, 0, 0, 1};
    p = piece_init(p, 0, 2, coords4);
    
    comb = find_all_shifted_combinations(comb, p);
    assert(comb->nb_combinations == 84);

    printf(GREEN "test_find_all_shifted_combinations passed !\n" RESET);
}

void test_get_comb_indices(void){
    int nb_pieces = 3;
    struct Combinations ** combs = malloc(nb_pieces * sizeof(struct Combinations *));

    struct Piece *p1;
    struct Piece *p2;
    struct Piece *p3;

    int coords1[6] = {0, 0, 0, 1, 0, 0};  // 144 combinations 
    p1 = piece_init(p1, 0, 2, coords1);

    int coords2[3] = {0, 0, 0};           // 64 combinations 
    p2 = piece_init(p2, 1, 1, coords2);

    int coords3[6] = {0, 0, 0, 0, 0, 1}; // 144 combinations 
    p3 = piece_init(p3, 2, 2, coords3);

    struct Piece * input_pieces[3] = {p1, p2, p3};
    for (int i = 0; i < nb_pieces; ++i){
        combs[i] = comb_init(combs[i]);
        combs[i] = find_all_combinations(combs[i], input_pieces[i]);
    }

    int * indices = get_comb_indices(0, combs, nb_pieces);
    assert(indices[0] == 0);
    assert(indices[1] == 0);
    assert(indices[2] == 0);
    free(indices);

    indices = get_comb_indices(1, combs, nb_pieces);
    assert(indices[0] == 0);
    assert(indices[1] == 0);
    assert(indices[2] == 1);
    free(indices);

    indices = get_comb_indices(143, combs, nb_pieces);
    assert(indices[0] == 0);
    assert(indices[1] == 0);
    assert(indices[2] == 143);
    free(indices);

    indices = get_comb_indices(144, combs, nb_pieces);
    assert(indices[0] == 0);
    assert(indices[1] == 1);
    assert(indices[2] == 0);
    free(indices);

    indices = get_comb_indices(144 * 64, combs, nb_pieces);
    assert(indices[0] == 1);
    assert(indices[1] == 0);
    assert(indices[2] == 0);
    free(indices);

    indices = get_comb_indices(144 * 64 + 1, combs, nb_pieces);
    assert(indices[0] == 1);
    assert(indices[1] == 0);
    assert(indices[2] == 1);
    free(indices);

    indices = get_comb_indices(144 * 128 + 145, combs, nb_pieces);
    assert(indices[0] == 2);
    assert(indices[1] == 1);
    assert(indices[2] == 1);
    free(indices);

    printf(GREEN "test_get_comb_indices passed !\n" RESET);
}

void test_get_global_index(void){
    int nb_pieces = 3;
    struct Combinations ** combs = malloc(nb_pieces * sizeof(struct Combinations *));

    struct Piece *p1;
    struct Piece *p2;
    struct Piece *p3;

    int coords1[6] = {0, 0, 0, 1, 0, 0};  // 144 combinations 
    p1 = piece_init(p1, 0, 2, coords1);

    int coords2[3] = {0, 0, 0};           // 64 combinations 
    p2 = piece_init(p2, 1, 1, coords2);

    int coords3[6] = {0, 0, 0, 0, 0, 1}; // 144 combinations 
    p3 = piece_init(p3, 2, 2, coords3);

    struct Piece * input_pieces[3] = {p1, p2, p3};
    for (int i = 0; i < nb_pieces; ++i){
        combs[i] = comb_init(combs[i]);
        combs[i] = find_all_combinations(combs[i], input_pieces[i]);
    }

    
    int indices[3] = {0, 0, 0};
    assert(get_global_index(indices, combs, 3) == 0);

    int indices2[3] = {2, 1, 1};
    assert(get_global_index(indices2, combs, 3) == 144 * 128 + 145);

    int indices3[3] = {1, 0, 1};
    assert(get_global_index(indices3, combs, 3) == 144 * 64 + 1);

    int indices4[3] = {1, 63, 0};
    assert(get_global_index(indices4, combs, 3) == (144 * 64) + (63 * 144));

    int indices5[3] = {143, 63, 143};
    assert(get_global_index(indices5, combs, 3) == 144 * 64 * 144 - 1);


    printf(GREEN "test_get_global_index passed !\n" RESET);
}

void test_find_next_index(void){
    int nb_pieces = 3;
    struct Combinations ** combs = malloc(nb_pieces * sizeof(struct Combinations *));

    struct Piece *p1;
    struct Piece *p2;
    struct Piece *p3;

    int coords1[6] = {0, 0, 0, 1, 0, 0};  // 144 combinations 
    p1 = piece_init(p1, 0, 2, coords1);

    int coords2[3] = {0, 0, 0};           // 64 combinations 
    p2 = piece_init(p2, 1, 1, coords2);

    int coords3[6] = {0, 0, 0, 0, 0, 1}; // 144 combinations 
    p3 = piece_init(p3, 2, 2, coords3);

    struct Piece * input_pieces[3] = {p1, p2, p3};
    for (int i = 0; i < nb_pieces; ++i){
        combs[i] = comb_init(combs[i]);
        combs[i] = find_all_combinations(combs[i], input_pieces[i]);
    }
    int indices[3] = {0, 0, 0};
    assert(find_next_index(indices, combs, nb_pieces, 1) == 144);

    int indices2[3] = {0, 63, 0};
    assert(find_next_index(indices2, combs, nb_pieces, 1) == 144 * 64);

    int indices3[3] = {0, 62, 0};
    assert(find_next_index(indices3, combs, nb_pieces, 1) == 144 * 63);

    int indices4[3] = {14, 63, 0};
    assert(find_next_index(indices4, combs, nb_pieces, 1) == 15 * 144 * 64);

    printf(GREEN "test_find_next_index passed !\n" RESET);
}

void test_find_all_combinations(void){
    struct Combinations * comb;
    comb = comb_init(comb);

    struct Piece *p;
    
    int coords1[3] = {0, 0, 0}; 
    p = piece_init(p, 0, 1, coords1);

    comb = find_all_combinations(comb, p);
    assert(comb->nb_combinations == 64);

    comb = comb_init(comb);
    int coords2[6] = {0, 0, 0, 1, 0, 0};
    p = piece_init(p, 0, 2, coords2);
    
    comb = find_all_combinations(comb, p);
    assert(comb->nb_combinations == 144);

    printf(GREEN "test_find_all_combinations passed !\n" RESET);
}

int main(void){
    test_comb_init();
    test_shift();
    test_rotate();
    test_insert_new_piece();
    test_piece_exist();
    test_place_available();
    test_find_all_rotated_combinations();
    test_find_all_shifted_combinations();
    test_get_comb_indices();
    test_get_global_index();
    test_find_next_index();
    test_find_all_combinations();

    return EXIT_SUCCESS;
}