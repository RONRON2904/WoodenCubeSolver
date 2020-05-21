#ifndef PIECE_H
#define PIECE_H

#define DIM_LIMIT 3

struct Piece {
    int id;
    int nb_elementary_cube;
    int * coords; // A piece is a set of elementary cube. Each cube has 3 coordinates (x, y, z) -> Example : p = [x0, y0, z0, x1, y1, z1, ..., xn, yn, zn]
    int is_free;
};

int is_piece_beyond_limit(struct Piece *p, int dim_limit);
struct Piece * piece_init(struct Piece *p, int id, int nb_elem, int * coords);
struct Piece * piece_copy(struct Piece *p);


void print_piece(struct Piece *p);

/* 
* shifts are of +/- 1 unit along the axis named in the the function
* Returns int : 1 if the shifted piece does not go beyond the cube limits
*/
int shift_x_axis(struct Piece *p, int towards, int dim_limit); // towards -> +1 along axis, <- -1 along axis
int shift_y_axis(struct Piece *p, int towards, int dim_limit);
int shift_z_axis(struct Piece *p, int towards, int dim_limit);

/* 
* Rotations are 90 degres clockwise around the axis named in the the function
* Returns int : 1 if the rotated piece does not go beyond the cube limits
*/
int rotation_x_axis(struct Piece *p, int dim_limit); 
int rotation_y_axis(struct Piece *p, int dim_limit);
int rotation_z_axis(struct Piece *p, int dim_limit);

/*
* In case a piece is not in the cube limits, bring_piece_back function uses shifts to bring the piece back in the cube limits
*/
void bring_piece_back(struct Piece *p, int dim_limit);

int get_piece_limit(struct Piece *p, int axis, char limit_type[3]); // limit_type -> max or min
int has_piece_element(struct Piece *p, int elem[3]);
int piece_compare(struct Piece *p1, struct Piece *p2);
#endif