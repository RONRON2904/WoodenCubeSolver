#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "../headers/file_handler.h"

int parse_nb_piece(char * input_filepath){
    FILE *fptr;

    if ((fptr = fopen(input_filepath, "r")) == NULL){
        printf("Error! opening file");
        exit(1);         
    }
    assert(fseek(fptr, 0, SEEK_SET) == 0);
    int nb_piece = 1;
    for (int c = getc(fptr); c != EOF; c = getc(fptr)) 
        if (c == '\n')  
            nb_piece++;
    assert(fseek(fptr, 0, SEEK_SET) == 0);
    fclose(fptr);
    return nb_piece;
}

int parse_cube_size(char * input_filepath){
    FILE *fptr;

    if ((fptr = fopen(input_filepath, "r")) == NULL){
        printf("Error! opening file");
        exit(1);         
    }
    assert(fseek(fptr, 0, SEEK_SET) == 0);
    int max_coord = 0;
    for (int c = getc(fptr); c != EOF; c = getc(fptr)){
        if (c != '\n' && !isspace(c))
            if ((int) c - 48 > max_coord)
                max_coord = (int) c - 48;
    }
    assert(fseek(fptr, 0, SEEK_SET) == 0);
    fclose(fptr);
    return max_coord + 1;
}

struct Piece * parse_piece(FILE * input_file, int piece_line){
    char piece[1000];
    
    for (int i = 0; i < piece_line; ++i)
        fscanf(input_file,"%*[^\n]\n");
    
    fscanf(input_file, "%[^\n]", piece);

    int nb_coords = 0;
    int piece_len = strlen(piece);
    for (int i = 0; i < piece_len; ++i)
        if (piece[i] != ' ')
            nb_coords++;
    
    assert(nb_coords % 3 == 0);

    int coords[nb_coords];
    int coord = 0;
    for (int i = 0; i < piece_len; ++i)
        if (piece[i] != ' '){
            coords[coord] = atoi(&piece[i]);
            coord++;
        }

    struct Piece *p = malloc(sizeof(struct Piece));
    
    p = piece_init(p, piece_line, (int) (nb_coords/3), coords);
    assert(fseek(input_file, 0, SEEK_SET) == 0);
    
    return piece_copy(p);
}


struct Piece ** read_pieces(char * filepath){
    FILE *fptr;

    if ((fptr = fopen(filepath, "r")) == NULL){
        printf("Error! opening file");
        exit(1);         
    }
    int nb_piece = parse_nb_piece(filepath);
    struct Piece ** input_pieces = malloc(nb_piece * sizeof(struct Piece *));
    for (int i = 0; i < nb_piece; ++i){
        struct Piece *p = malloc(sizeof(*p));
        p = parse_piece(fptr, i);
        input_pieces[i] = p;
    }
    fclose(fptr);    

    return input_pieces;
}

void write_solution(char * filepath, int * p_ids, int cube_size){
    FILE *f = fopen(filepath, "w");
    assert(f != NULL);

    assert(fprintf(f, "x y z p_id\n") > 0);
    int piece = 0;
    for (int x = 0; x < cube_size; ++x)
        for (int y = 0; y < cube_size; ++y)
            for (int z = 0; z < cube_size; ++z){
                assert(fprintf(f, "%d %d %d %d\n", x, y, z, p_ids[piece]) > 0);
                piece++;
            }
    fclose(f);  
}