#include "automaton_2d.h"

int count_neighbours(int x, int y) {
    int neighbour_count=0;
    for(int i = -1; i<= 1;i++){
        for(int j = -1; j <= 1;j++){
            if(!is_valid_cell(x+i,y+j))  
                continue;
            neighbour_count += board[x+i][y+j];
        }
    }
    neighbour_count -= board[x][y];
    return neighbour_count;
}

int apply_life_rules(int neighbours, int alive) {
    if (alive && ((neighbours <  2) || (neighbours >  3))) 
        return 0;
    else if (!alive && (neighbours == 3)) 
        return 1;
    return alive;
}

void game_of_life_ruleset(){
    memcpy(next_board,board,sizeof(board));
    for_2d(x,cell_count_2d,y,cell_count_2d) {
        next_board[x][y]=apply_life_rules(count_neighbours(x,y),board[x][y]);
    }
    memcpy(board,next_board,sizeof(board));
}