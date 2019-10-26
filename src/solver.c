#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/solver.h"

struct Combinations * comb_init(struct Combinations *comb){
    comb = malloc(sizeof(struct Combinations));
    comb->nb_combinations = 0;
    comb->piece_combinations = NULL;
    return comb;
}

void shift(struct Piece *piece, int axis){
    switch (axis){
        case 0:
            shift_x_axis(piece, 1);
            if (is_piece_beyond_limit(piece)){
                int min = get_piece_limit(piece, 0, "min");
                for (int i = 0; i < min; ++i)
                    shift_x_axis(piece, -1);
            }
            break;
        case 1:
            shift_y_axis(piece, 1);
            if (is_piece_beyond_limit(piece)){
                int min = get_piece_limit(piece, 1, "min"); 
                for (int i = 0; i < min; ++i)
                    shift_y_axis(piece, -1);
            }
            break;
        case 2:
            shift_z_axis(piece, 1);
            if (is_piece_beyond_limit(piece)){
                int min = get_piece_limit(piece, 2, "min");
                for (int i = 0; i < min; ++i)
                    shift_z_axis(piece, -1);
            }
            break;
        default:
            break;
    }
}

void rotate(struct Piece *piece, int axis){
    switch (axis){
        case 0:
            rotation_x_axis(piece);
            break;
        case 1:
            rotation_y_axis(piece);
            break;
        case 2:
            rotation_z_axis(piece);
            break;
        default:
            break;
    }
    bring_piece_back(piece);
}

struct Combinations * insert_new_piece(struct Piece * piece, struct Combinations *comb){
    comb->nb_combinations++;
    comb->piece_combinations = realloc(comb->piece_combinations, comb->nb_combinations * sizeof(struct Piece *));
    comb->piece_combinations[comb->nb_combinations - 1] = piece_copy(piece);
    return comb;
}

int insert_piece(struct Piece * piece, struct Cube * cube){
    for (int i = 0; i < piece->nb_elementary_cube; ++i)
        if (!fill_boxes(cube, piece->coords[3 * i], piece->coords[3 * i + 1], piece->coords[3 * i + 2], piece->id))
            return 0;
    return 1;
}

int piece_exist(struct Combinations * comb, struct Piece * piece){
    for (int i = 0; i < comb->nb_combinations; ++i)
        if (piece_compare(piece, comb->piece_combinations[i]))
            return 1;
    return 0;
}

int place_available(struct Cube *cube, struct Piece *piece){
    return !is_place_occupied(cube, piece->coords, piece->nb_elementary_cube);
}

struct Combinations * find_all_rotated_combinations(struct Combinations * comb, struct Piece *piece){
    if (!piece_exist(comb, piece))
        comb = insert_new_piece(piece, comb); 

    for (int x_rot = 0; x_rot < 4; x_rot++){
        for (int y_rot = 0; y_rot < 4; y_rot++){
            for (int z_rot = 0; z_rot < 4; z_rot++){
                rotate(piece, 2);
                if (!piece_exist(comb, piece)){
                    comb = insert_new_piece(piece, comb);
                } 
            }
            rotate(piece, 1);
            if (!piece_exist(comb, piece)){
                comb = insert_new_piece(piece, comb);
            } 
        }
        rotate(piece, 0);
        if (!piece_exist(comb, piece)){
            comb = insert_new_piece(piece, comb);
        } 
    }
    return comb;
}

struct Combinations * find_all_shifted_combinations(struct Combinations * comb, struct Piece *piece){
    if (!piece_exist(comb, piece))
        comb = insert_new_piece(piece, comb);   
    
    for (int x_tslt = 0; x_tslt < 4; ++x_tslt){
        for (int y_tslt = 0; y_tslt < 4; ++y_tslt){
            for (int z_tslt = 0; z_tslt < 4; ++z_tslt){
                shift(piece, 2);
                if (!piece_exist(comb, piece))
                    comb = insert_new_piece(piece, comb);
            }
            shift(piece, 1);
            if (!piece_exist(comb, piece))
                comb = insert_new_piece(piece, comb);  
        }
        shift(piece, 0);
        if (!piece_exist(comb, piece))
            comb = insert_new_piece(piece, comb);  
    }
    return comb;
}

struct Combinations * find_all_combinations(struct Combinations *comb, struct Piece *piece){
    struct Combinations * rot_comb; 
    rot_comb = comb_init(rot_comb);
    rot_comb = find_all_rotated_combinations(rot_comb, piece);

    for (int rot = 0; rot < rot_comb->nb_combinations; ++rot)
        comb = find_all_shifted_combinations(comb, rot_comb->piece_combinations[rot]);

    return comb;
}

int * get_comb_indices(unsigned long long int global_index, struct Combinations ** combs, int nb_pieces){
    int * indices = malloc(nb_pieces * sizeof(int));
    unsigned long long int nb_combs = 1;
    for (int i = 0; i < nb_pieces; ++i){
        indices[nb_pieces - (i + 1)] = (int) ((global_index / nb_combs) % combs[nb_pieces - (i + 1)]->nb_combinations);
        nb_combs *= combs[nb_pieces - (i + 1)]->nb_combinations;
    }
    return indices;
}

unsigned long long int get_global_index(int * indices, struct Combinations ** combs, int nb_pieces){
    unsigned long long global_idx = 0;
    unsigned long long int nb_combs = 1;
    for (int i = 0; i < nb_pieces; ++i){
        global_idx += indices[nb_pieces - (i + 1)] * nb_combs;
        nb_combs *= combs[nb_pieces - (i + 1)]->nb_combinations;
    }
    return global_idx;
}

unsigned long long find_next_index(int * indices, struct Combinations ** combs, int nb_pieces, int current_piece_number){
    int ind_tmp[nb_pieces];
    for (int i = 0; i < nb_pieces; ++i)
        ind_tmp[i] = indices[i];

    if (current_piece_number < nb_pieces - 1){
        for (int ii = current_piece_number; ii >= 0; --ii){
            if (combs[ii]->nb_combinations > ind_tmp[ii] + 1){
                ind_tmp[ii]++;
                break;
            }
            else
                ind_tmp[ii] = 0;
        }
        for (int jj = current_piece_number + 1; jj < nb_pieces; ++jj)
            ind_tmp[jj] = 0;

        assert(get_global_index(ind_tmp, combs, nb_pieces) > get_global_index(indices, combs, nb_pieces));
    }
    return get_global_index(ind_tmp, combs, nb_pieces);
}

struct Solution * find_solution(struct Piece ** input_pieces, int nb_pieces){
    struct Combinations ** combs = malloc(nb_pieces * sizeof(struct Combinations *));
    struct Cube *cube;
    cube = init_cube(cube, 4);

    int nb_box_left = 64;

    unsigned long long int max_iter = 1;
    unsigned long long nb_iter = 0;
    for (int i = 0; i < nb_pieces; ++i){
        combs[i] = comb_init(combs[i]);
        combs[i] = find_all_combinations(combs[i], input_pieces[i]);
        max_iter *= combs[i]->nb_combinations;
    }
    
    unsigned long long int i; 
    printf("Let's brute force for maximum %llu iterations!\n", max_iter);
    for (i = 0; i < max_iter; ++i){
        int * indices = get_comb_indices(i, combs, nb_pieces);
        for (int p = 0; p < nb_pieces; ++p){
            nb_iter++;
            struct Piece *piece = combs[p]->piece_combinations[indices[p]];
            if (!insert_piece(piece, cube)){
                i = find_next_index(indices, combs, nb_pieces, p);
                assert(i <= max_iter);
                break;
            }
        }  
        free(indices);        
        if (cube->nb_boxes_left < nb_box_left){
            nb_box_left = cube->nb_boxes_left;
        }

        if (is_cube_full(cube)){
            printf("Solution Found in %llu iterations!\n", nb_iter);
            break;
        }
        else
            free_boxes(cube);         
    }
    free_all_combinations(combs, nb_pieces);
    struct Solution * solution = malloc(sizeof(struct Solution));
    solution->filled_cube = cube;
    solution->nb_comb_tried = nb_iter;
    return solution;
}

void free_all_combinations(struct Combinations ** combs, int nb_pieces){
    for (int i = 0; i < nb_pieces; ++i){
        for (int p = 0; p < combs[i]->nb_combinations; ++p)
            free(combs[i]->piece_combinations[p]);
        free(combs[i]);
    }
    free(combs);
}

void free_solution(struct Solution * solution){
    free_cube(solution->filled_cube);
    free(solution);
}