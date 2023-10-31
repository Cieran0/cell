#include "automaton_2d.h"

char two_d_map[MAX_CELL_COUNT_2D][MAX_CELL_COUNT_2D]={0};
char next_2d_map[MAX_CELL_COUNT_2D][MAX_CELL_COUNT_2D]={0};
int rule_2d=0;
char neighbour_buffer[8] = {0};
int cell_count_2d = 20;

void gen_random_2d_map(){
    srand(time(NULL));

    for(int y = 0; y < cell_count_2d; y++){
        for(int x = 0; x < cell_count_2d; x++){
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
    return (x >= 0 && x < cell_count_2d && y >= 0 && y < cell_count_2d);
}

void display_generation(){
    printf("\e[1;1H\e[2J");
    printf("\n");
    for(int y = 0; y< cell_count_2d; y++){
        print_row(two_d_map[y],cell_count_2d);
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

char* get_neighbours_array(int x, int y) {
    int current_neighbour=0;
    for(int i = -1; i<= 1;i++){
        for(int j = -1; j <= 1;j++){
            if(i == 0 && j == 0)
                continue;
            int real_x = (x+i + cell_count_2d) % cell_count_2d;
            int real_y = (y+j + cell_count_2d) % cell_count_2d;
                neighbour_buffer[current_neighbour++]=two_d_map[real_x][real_y];
        }
    }
    return neighbour_buffer;
}