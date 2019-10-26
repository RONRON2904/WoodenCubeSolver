#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/piece.h"

struct Piece * piece_init(struct Piece *p, int id, int nb_elem, int * coords){
    p = malloc(sizeof(struct Piece));
    p->id = id;
    p->nb_elementary_cube = nb_elem;
    p->coords = malloc(3 * p->nb_elementary_cube * sizeof(int));
    p->coords = coords;
    p->is_free = 1;
    return p;
}

struct Piece * piece_copy(struct Piece *p){
    struct Piece * new_piece = malloc(sizeof(struct Piece));
    new_piece->id = p->id;
    new_piece->nb_elementary_cube = p->nb_elementary_cube;
    new_piece->coords = malloc(3 * p->nb_elementary_cube * sizeof(int));
    new_piece->is_free = p->is_free;
    for (int i = 0; i < p->nb_elementary_cube; ++i){
        new_piece->coords[3 * i] = p->coords[3 * i];
        new_piece->coords[3 * i + 1] = p->coords[3 * i + 1];
        new_piece->coords[3 * i + 2] = p->coords[3 * i + 2];
    }
    return new_piece;
}

void print_piece(struct Piece *p){
    printf("\n");
    printf("Piece id: %d\n", p->id);
    for (int i = 0; i < p->nb_elementary_cube; ++i)
        printf("Elem %d: (i, j, k) = (%d, %d, %d)\n", i + 1, p->coords[3 * i], p->coords[3 * i + 1], p->coords[3 * i + 2]);
}

int is_piece_beyond_limit(struct Piece *p){
    for (int i = 0; i < 3 * p->nb_elementary_cube; i++)
        if (p->coords[i] > DIM_LIMIT | p->coords[i] < 0)
            return 1;
    return 0;
}

int shift_x_axis(struct Piece *p, int towards){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        if (towards == 1)
            p->coords[3*i]++;
        else
            p->coords[3*i]--;
    }
    return !is_piece_beyond_limit(p);
}

int shift_y_axis(struct Piece *p, int towards){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        if (towards == 1)
            p->coords[3*i + 1]++;
        else
            p->coords[3*i + 1]--;
    }
    return !is_piece_beyond_limit(p);
}
int shift_z_axis(struct Piece *p, int towards){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        if (towards == 1)
            p->coords[3*i + 2]++;
        else
            p->coords[3*i + 2]--;
    }
    return !is_piece_beyond_limit(p);
}

int rotation_x_axis(struct Piece *p){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        int y_tmp = p->coords[3 * i + 1];
        p->coords[3 * i + 1] = - p->coords[3 * i + 2];
        p->coords[3 * i + 2] = y_tmp;
    }
    return !is_piece_beyond_limit(p);
}

int rotation_y_axis(struct Piece *p){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        int x_tmp = p->coords[3 * i];
        p->coords[3 * i] =  p->coords[3 * i + 2];
        p->coords[3 * i + 2] = - x_tmp;
    }
    return !is_piece_beyond_limit(p);
}

int rotation_z_axis(struct Piece *p){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        int x_tmp = p->coords[3 * i];
        p->coords[3 * i] = - p->coords[3 * i + 1];
        p->coords[3 * i + 1] = x_tmp;
    }
    return !is_piece_beyond_limit(p);
}

void bring_piece_back(struct Piece *p){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        int x = p->coords[3 * i];
        int y = p->coords[3 * i + 1];
        int z = p->coords[3 * i + 2];
        if (x < 0)
            for (int ii = 0; ii < -x; ++ii)
                shift_x_axis(p, 1);
        if (x > DIM_LIMIT)
            for (int ii = 0; ii < x - DIM_LIMIT - 1; ++ii)
                shift_x_axis(p, -1);

        if (y < 0)
            for (int ii = 0; ii < -y; ++ii)
                shift_y_axis(p, 1);
        if (y > DIM_LIMIT)
            for (int ii = 0; ii < y - DIM_LIMIT - 1; ++ii)
                shift_y_axis(p, -1);

        if (z < 0)
            for (int ii = 0; ii < -z; ++ii)
                shift_z_axis(p, 1);
        if (z > DIM_LIMIT)
            for (int ii = 0; ii < z - DIM_LIMIT - 1; ++ii)
                shift_z_axis(p, -1);
    }
}

int get_piece_limit(struct Piece *p, int axis, char limit_type[3]){
    int limit = p->coords[axis];
    for(int i = 1; i < p->nb_elementary_cube; ++i){
        if (!strcmp(limit_type, "max"))
            if (p->coords[3 * i + axis] > limit)
                limit = p->coords[3 * i + axis];
        if (!strcmp(limit_type, "min"))
            if (p->coords[3 * i + axis] < limit)
                limit = p->coords[3 * i + axis];        
    }
    return limit;
}

int has_piece_element(struct Piece *p, int elem[3]){
    for(int i = 0; i < p->nb_elementary_cube; ++i){
        if (p->coords[3 * i] == elem[0] && 
            p->coords[3 * i + 1] == elem[1] && 
            p->coords[3 * i + 2] == elem[2])
            return 1;
    }
    return 0;
}

// returns 0 if p1 != p2
int piece_compare(struct Piece *p1, struct Piece *p2){ 
    if (p1->id == p2->id){
        for(int i = 0; i < p1->nb_elementary_cube; ++i){
            int elem[3] = {p2->coords[3 * i], p2->coords[3 * i + 1], p2->coords[3 * i + 2]};
            if (!has_piece_element(p1, elem))
                return 0;
        }
        return 1;
    }
    return 0;
}