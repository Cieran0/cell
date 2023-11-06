#include "automaton_2d.h"

//initialise map
char map_2d[256] = {0};

//gets rule
void gen_map_2d(char rule) {
    for (int i = 0; i < 8; i++)
        map_2d[i] = ((rule >> i)  & 0x01);

    for (int i = 8; i < 256; i++)
        map_2d[i]=map_2d[i%8];
}

//applies rule
void rule_2d_ruleset(){
    //gets copy of board
    memcpy(next_board,board,sizeof(board));
    for_2d(x,cell_count_2d,y,cell_count_2d) {
        //generates new board
        next_board[x][y]=map_2d[(concat(get_neighbours_array(x,y),8))];
    }
    //copies new board into the old board
    memcpy(board,next_board,sizeof(board));
}