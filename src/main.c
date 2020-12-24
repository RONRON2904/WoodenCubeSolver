#include <stdio.h>
#include <stdlib.h>

#include "../headers/solver.h"
#include "../headers/file_handler.h"

void print_solution(struct Solution * solution){
    printf("Solution found in %d iterations\n", solution->nb_comb_tried);
    print_cube(solution->filled_cube);
}

int * get_solution_pids(struct Solution * solution, int cube_size){
    int * pids = malloc(cube_size * cube_size * cube_size * sizeof(int));
    int piece = 0;
    for (int i = 0; i < cube_size; ++i)
        for (int j = 0; j < cube_size; j++)
            for (int k = 0; k < cube_size; k++){
                pids[piece] = solution->filled_cube->boxes[(cube_size * i) + (j * cube_size * cube_size) + k].id_piece;
                piece++;
            }
    return pids;
}

int main(){
    int cube_size = 0;
    //printf("What is the cube size (SIZExSIZExSIZE) ?\n");
    //scanf("%d", &cube_size);
    cube_size = parse_cube_size("../pieces.txt");
    int nb_pieces = parse_nb_piece("../pieces.txt");
    printf("%d", cube_size);
    struct Piece ** input_pieces = read_pieces("../pieces.txt");
    struct Solution * solution = find_solution(input_pieces, nb_pieces, cube_size);
    
    //print_solution(solution);
    int * sol_pids = get_solution_pids(solution, cube_size);
    write_solution("../solution.txt", sol_pids, cube_size);

    for (int i = 0; i < nb_pieces; ++i)
        free(input_pieces[i]);
    
    free(input_pieces);
    free_solution(solution);
    free(sol_pids);

    return EXIT_SUCCESS;
}