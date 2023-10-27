#include "automaton_2d.h"

int count_neighbours(int x, int y) {
    int neighbour_count=0;
    for(int i = -1; i<= 1;i++){
        for(int j = -1; j <= 1;j++){
            if(!is_valid_cell(x+i,y+j))  
                continue;
            neighbour_count += two_d_map[x+i][y+j];
        }
    }
    neighbour_count -= two_d_map[x][y];
    return neighbour_count;
}

int apply_life_rules(int neighbours, int alive) {
    if (alive && ((neighbours <  2) || (neighbours >  3))) 
        return 0;
    else if (!alive && (neighbours == 3)) 
        return 1;
    return alive;
}

void game_of_life_rules(){
    memcpy(next_2d_map,two_d_map,sizeof(two_d_map));
    for_2d(x,CELL_COUNT_2D,y,CELL_COUNT_2D) {
        next_2d_map[x][y]=apply_life_rules(count_neighbours(x,y),two_d_map[x][y]);
    }
    memcpy(two_d_map,next_2d_map,sizeof(two_d_map));
}