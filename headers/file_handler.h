#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdio.h>  
#include "piece.h"

int parse_nb_piece(char * input_filepath);
struct Piece * parse_piece(FILE * input_file, int piece_line);
struct Piece ** read_pieces(char * filepath);
void write_solution(char * filepath, int * p_ids);

#endif