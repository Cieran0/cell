#include "automaton_2d.h"

char two_d_map[CELL_COUNT_2D][CELL_COUNT_2D]={0};
char next_2d_map[CELL_COUNT_2D][CELL_COUNT_2D]={0};
int rule_2d=0;

void gen_random_2d_map(){
    srand(time(NULL));

    for(int y = 0; y < CELL_COUNT_2D; y++){
        for(int x = 0; x < CELL_COUNT_2D; x++){
            two_d_map[x][y] = (rand()%4 == 0);
        }
    }
}

void draw_crosshair(){
    for (int i = 0; i < 3; i++)
    {
        two_d_map[5][i+1]=1;
        two_d_map[i+1][5]=1;
        two_d_map[9-i][5]=1;
        two_d_map[5][i+7]=1;
    }
    
}

int is_valid_cell(int x, int y) {
    return (x >= 0 && x < CELL_COUNT_2D && y >= 0 && y < CELL_COUNT_2D);
}

void display_generation(){
    printf("\e[1;1H\e[2J");
    printf("\n");
    for(int y = 0; y< CELL_COUNT_2D; y++){
        print_row(two_d_map[y],CELL_COUNT_2D);
    }
}

void display_cycles(int cycles, void (*ruleset)(void), int m_delay) {
    gen_random_2d_map();
    for(int i = 0; i < cycles;i++){
        printf("\e[1;1H\e[2J");
        display_generation();
        msleep(m_delay);
        ruleset();
    }
}