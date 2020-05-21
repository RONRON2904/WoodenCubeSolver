#ifndef SOLVER_H
#define SOLVER_H

#include "piece.h"
#include "cube.h"

struct Combinations {
    int nb_combinations;
    struct Piece ** piece_combinations;
};

struct Solution {
    int nb_comb_tried;
    struct Cube * filled_cube;
};

struct Combinations * comb_init(struct Combinations *comb);
void shift(struct Piece *piece, int axis, int dim_limit);
void rotate(struct Piece *piece, int axis, int dim_limit);
struct Combinations * insert_new_piece(struct Piece * piece, struct Combinations *comb);
int piece_exist(struct Combinations * comb, struct Piece * piece);
int place_available(struct Cube *cube, struct Piece *piece);
struct Combinations * find_all_rotated_combinations(struct Combinations * comb, struct Piece *piece, int dim_limit);
struct Combinations * find_all_shifted_combinations(struct Combinations * comb, struct Piece *piece, int dim_limit);
struct Combinations * find_all_combinations(struct Combinations *comb, struct Piece *piece, int dim_limit);
int * get_comb_indices(unsigned long long int global_index, struct Combinations ** combs, int nb_pieces);
unsigned long long int get_global_index(int * indices, struct Combinations ** combs, int nb_pieces);
unsigned long long find_next_index(int * indices, struct Combinations ** combs, int nb_pieces, int current_piece_number);
struct Solution * find_solution(struct Piece ** input_pieces, int nb_pieces, int cube_size);
void free_all_combinations(struct Combinations ** combs, int nb_pieces);
void free_solution(struct Solution * solution);

#endif