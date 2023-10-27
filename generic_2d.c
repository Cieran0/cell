#include "automaton_2d.h"

int two_d_map[CELL_COUNT_2D][CELL_COUNT_2D]={0};
int next_2d_map[CELL_COUNT_2D][CELL_COUNT_2D]={0};

void gen_random_2d_map(){
    srand(time(NULL));

    for(int y = 0; y < CELL_COUNT_2D; y++){
        for(int x = 0; x < CELL_COUNT_2D; x++){
            two_d_map[x][y] = rand()%2 && rand()%2 && rand()%2;
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
    for(int y = 0; y< CELL_COUNT_2D; y++){
        for(int x=0; x< CELL_COUNT_2D; x++){
            if(two_d_map[x][y]){
                printf("\x1B[41m \x1B[0m");
            }
            else{
                printf(" ");
            }
            //printf("%d", two_d_map[x][y]);
        }
        printf("\n");
    }
}