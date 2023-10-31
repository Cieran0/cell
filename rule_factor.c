#include "automaton_2d.h"

char apply_factor_rule_2ds(char neighbours_concat, char alive) {
    neighbours_concat = abs(neighbours_concat);
    return alive? !(neighbours_concat%rule_2d) : !!(neighbours_concat%rule_2d);
}

void factor_rules(){
    memcpy(next_2d_map,two_d_map,sizeof(two_d_map));
    for_2d(x,CELL_COUNT_2D,y,CELL_COUNT_2D) {
        next_2d_map[x][y]=apply_factor_rule_2ds(concat(get_neighbours_array(x,y),8),two_d_map[x][y]);
    }
    memcpy(two_d_map,next_2d_map,sizeof(two_d_map));
}