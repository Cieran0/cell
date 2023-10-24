#include "automation_2d.h"

int two_d_map[CELL_COUNT_2D][CELL_COUNT_2D]={0};
int next_2d_map[CELL_COUNT_2D][CELL_COUNT_2D]={0};

void gen_random_2d_map(){
    srand(time(NULL));

    for(int y = 0; y < CELL_COUNT_2D; y++){
        for(int x = 0; x < CELL_COUNT_2D; x++){
            two_d_map[x][y] = rand()%2;
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

int update_cell(int neighbours, int alive) {
    if (alive && ((neighbours <  2) || (neighbours >  3))) 
        return 0;
    else if (!alive && (neighbours == 3)) 
        return 1;
    return alive;
}

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

void gen_next_map(){
    memcpy(next_2d_map,two_d_map,sizeof(two_d_map));
    for_2d(x,CELL_COUNT_2D,y,CELL_COUNT_2D) {
            next_2d_map[x][y]=update_cell(count_neighbours(x,y),two_d_map[x][y]);
    }
    memcpy(two_d_map,next_2d_map,sizeof(two_d_map));
}

void display_1_cycle(){
    for(int y = 0; y< CELL_COUNT_2D; y++){
        for(int x=0; x< CELL_COUNT_2D; x++){
            printf("%d", two_d_map[x][y]);
        }
        printf("\n");
    }
}

void display_all_cycles(int cycles){
    draw_crosshair();
    display_1_cycle();
    printf("\n");

    for(int i = 0; i < cycles;i++){
        gen_next_map();
        display_1_cycle();
        usleep(500000);
        printf("\n");
    }
}