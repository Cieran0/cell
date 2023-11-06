#include "automaton_2d.h"

int count_neighbours(int x, int y) {
    int neighbour_count=0;
    for(int i = -1; i<= 1;i++){
        for(int j = -1; j <= 1;j++){
            //checks for  valid cell
            if(!is_valid_cell(x+i,y+j))  
                continue;
            //increment neighbourcount
            neighbour_count += board[x+i][y+j];
        }
    }
    //take away center from neighbour count if 1
    neighbour_count -= board[x][y];
    return neighbour_count;
}

//rules for game of life
int apply_life_rules(int neighbours, int alive) {
    if (alive && ((neighbours <  2) || (neighbours >  3))) 
        return 0;
    else if (!alive && (neighbours == 3)) 
        return 1;
    return alive;
}

void game_of_life_ruleset(){
    //get copy of board
    memcpy(next_board,board,sizeof(board));
    for_2d(x,cell_count_2d,y,cell_count_2d) {
        //get the next board
        next_board[x][y]=apply_life_rules(count_neighbours(x,y),board[x][y]);
    }
    //copy the new board into the original variable
    memcpy(board,next_board,sizeof(board));
}