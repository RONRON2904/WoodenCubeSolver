#include <stdio.h>
#include <stdlib.h>

#include "../headers/solver.h"
#include "../headers/file_handler.h"

#define SIZE 4

void print_solution(struct Solution * solution){
    printf("Solution found in %d iterations\n", solution->nb_comb_tried);
    print_cube(solution->filled_cube);
}

int * get_solution_pids(struct Solution * solution){
    int * pids = malloc(SIZE * SIZE * SIZE * sizeof(int));
    int piece = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; j++)
            for (int k = 0; k < SIZE; k++){
                pids[piece] = solution->filled_cube->boxes[(SIZE * i) + (j * SIZE * SIZE) + k].id_piece;
                piece++;
            }
    return pids;
}

int main(){
    int nb_pieces = parse_nb_piece("../pieces.txt");
    struct Piece ** input_pieces = read_pieces("../pieces.txt");
    struct Solution * solution = find_solution(input_pieces, nb_pieces, SIZE);
    
    //print_solution(solution);
    int * sol_pids = get_solution_pids(solution);
    write_solution("../solution.txt", sol_pids);

    for (int i = 0; i < nb_pieces; ++i)
        free(input_pieces[i]);
    
    free(input_pieces);
    free_solution(solution);
    free(sol_pids);

    return EXIT_SUCCESS;
}