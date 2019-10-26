#ifndef CUBE_H
#define CUBE_H

struct Box {
    int x;
    int y;
    int z;
    int id_piece; // -1 -> free box
};

struct Cube {
    int size;
    struct Box * boxes;
    int nb_boxes_left;
};

struct Cube * init_cube(struct Cube *cube, int size);
int is_cube_full(struct Cube *c);
int is_place_occupied(struct Cube *c, int *coords, int nb_elem);
int fill_boxes(struct Cube *c, int x, int y, int z, int id);
void free_boxes(struct Cube *c);
void print_cube(struct Cube *c);
void free_cube(struct Cube *c);

#endif