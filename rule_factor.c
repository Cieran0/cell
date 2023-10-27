#include "automaton_2d.h"

char buff[8] = {0};
char* get_neighbours_array(int x, int y) {
    int current_neighbour=0;
    for(int i = -1; i<= 1;i++){
        for(int j = -1; j <= 1;j++){
            if(i == 0 && j == 0)
                continue;
            int real_x = (x+i + CELL_COUNT_2D) % CELL_COUNT_2D;
            int real_y = (y+j + CELL_COUNT_2D) % CELL_COUNT_2D;
                buff[current_neighbour++]=two_d_map[real_x][real_y];
        }
    }
    return buff;
}   

char apply_factor_rules(int rule, char neighbours_concat, char alive) {
    neighbours_concat = abs(neighbours_concat);
    return alive? !(neighbours_concat%rule) : !!(neighbours_concat%rule);
}

void next_factor_gen(int rule){
    memcpy(next_2d_map,two_d_map,sizeof(two_d_map));
    for_2d(x,CELL_COUNT_2D,y,CELL_COUNT_2D) {
        next_2d_map[x][y]=apply_factor_rules(rule, concat(get_neighbours_array(x,y),8),two_d_map[x][y]);
    }
    memcpy(two_d_map,next_2d_map,sizeof(two_d_map));
}

void display_factor_cycles(int cycles, int rule){
    gen_random_2d_map();
    display_generation();
    printf("\n");

    for(int i = 0; i < cycles;i++){
        next_factor_gen(rule);
        display_generation();
        msleep(100);
        printf("\n");
    }
}