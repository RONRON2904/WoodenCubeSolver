#include <stdio.h>
#include <stdlib.h>

#include "../headers/cube.h"

struct Cube * init_cube(struct Cube *cube, int size){
    cube = malloc(sizeof(struct Cube));
    struct Box * boxes = malloc(size * size * size * sizeof(struct Box));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; j++)
            for (int k = 0; k < size; k++){
                boxes[(size * i) + (j * size * size) + k].x = i;
                boxes[(size * i) + (j * size * size) + k].y = j;
                boxes[(size * i) + (j * size * size) + k].z = k;
                boxes[(size * i) + (j * size * size) + k].id_piece = -1;
            }
    
    cube->boxes = boxes;
    cube->size = size;
    cube->nb_boxes_left = size * size * size;
    return cube;
}

int is_cube_full(struct Cube *c){
    return c->nb_boxes_left == 1;       // Normally cube is full when  c->nb_boxes_left == 0 but I have lost one element from a piece    
}

int is_place_occupied(struct Cube *c, int * coords, int nb_elem){
    int i, j, k;
    for (int n = 0; n < nb_elem; ++n){
        i = coords[3 * n];
        j = coords[3 * n + 1];
        k = coords[3 * n + 2];
        if (c->boxes[(c->size * i) + (j * c->size * c->size) + k].id_piece != -1)
            return 1;
    }
    return 0;
}

void print_cube(struct Cube *c){
    for (int i = 0; i < c->size; ++i)
        for (int j = 0; j < c->size; j++)
            for (int k = 0; k < c->size; k++)
                printf("Box (%d, %d, %d): %d\n", i, j, k, c->boxes[(c->size * i) + (j * c->size * c->size) + k].id_piece);
    printf("Nb pieces left : %d\n", c->nb_boxes_left);
}

int fill_boxes(struct Cube *c, int x, int y, int z, int id){
    if (c->boxes[(c->size * x) + (y * c->size * c->size) + z].id_piece == -1) {
        c->boxes[(c->size * x) + (y * c->size * c->size) + z].id_piece = id;
        c->nb_boxes_left--;
        return 1;
    }
    return 0;
}

void free_boxes(struct Cube *c){
    for (int i = 0; i < c->size; ++i)
        for (int j = 0; j < c->size; j++)
            for (int k = 0; k < c->size; k++)
                (c->boxes[(c->size * i) + (j * c->size * c->size) + k].id_piece = -1);
    c->nb_boxes_left = c->size * c->size * c->size;
}

void free_cube(struct Cube *c){
    free_boxes(c);
    free(c);
}