#include "automaton_2d.h"

char map_2d[256] = {0};

void gen_map_2d(char rule) {
    for (int i = 0; i < 8; i++)
        map_2d[i] = ((rule >> i)  & 0x01);

    memset(&map_2d[8],31,*((unsigned long*)map_2d));
}

void rule_2d_ruleset(){
    memcpy(next_board,board,sizeof(board));
    for_2d(x,cell_count_2d,y,cell_count_2d) {
        next_board[x][y]=map_2d[(concat(get_neighbours_array(x,y),8))];
    }
    memcpy(board,next_board,sizeof(board));
}