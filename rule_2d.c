#include "automaton_2d.h"

char map_2d[256] = {0};

void gen_map_2d(char rule) {
    for (int i = 0; i < 8; i++)
        map_2d[i] = ((rule >> i)  & 0x01);

    memset(&map_2d[8],31,*((unsigned long*)map_2d));
}

void rule_2d_rules(){
    memcpy(next_2d_map,two_d_map,sizeof(two_d_map));
    for_2d(x,CELL_COUNT_2D,y,CELL_COUNT_2D) {
        next_2d_map[x][y]=map_2d[(concat(get_neighbours_array(x,y),8))];
    }
    memcpy(two_d_map,next_2d_map,sizeof(two_d_map));
}