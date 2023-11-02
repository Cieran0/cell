#include "automaton_2d.h"

char apply_factor_rule_2ds(char neighbours_concat, char alive) {
    neighbours_concat = abs(neighbours_concat);
    return alive? !(neighbours_concat%rule_2d) : !!(neighbours_concat%rule_2d);
}

void factor_ruleset(){
    memcpy(next_board,board,sizeof(board));
    for_2d(x,cell_count_2d,y,cell_count_2d) {
        next_board[x][y]=apply_factor_rule_2ds(concat(get_neighbours_array(x,y),8),board[x][y]);
    }
    memcpy(board,next_board,sizeof(board));
}