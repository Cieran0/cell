#include "automation_2d.h"

int two_d_map[CELL_COUNT][CELL_COUNT]={0};
int next_2d_map[CELL_COUNT][CELL_COUNT]={0};
int neighbour_count =0;

void gen_random_2d_map(){
    srand(time(NULL));

    for(int y = 0; y < CELL_COUNT; y++){
        for(int x = 0; x < CELL_COUNT; x++){
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

void gen_next_map(){
    memcpy(next_2d_map,two_d_map,sizeof(two_d_map));
    for(int y = 0; y< CELL_COUNT; y++){
        for(int x= 0; x< CELL_COUNT; x++){
            neighbour_count=0;
            for(int i = -1; i<= 1;i++){
                for(int j = -1; j <= 1;j++){
                    if(x+i==CELL_COUNT||y+j==CELL_COUNT||x+i==-1||y+j==-1)  
                        continue;
                    neighbour_count += two_d_map[x+i][y+j];
                }
            }
            neighbour_count -= two_d_map[x][y];

            if      ((two_d_map[x][y] == 1) && (neighbour_count <  2)) next_2d_map[x][y] = 0;
            else if ((two_d_map[x][y] == 1) && (neighbour_count >  3)) next_2d_map[x][y] = 0;
            else if ((two_d_map[x][y] == 0) && (neighbour_count == 3)) next_2d_map[x][y] = 1;
        }
    }
    memcpy(two_d_map,next_2d_map,sizeof(two_d_map));
}

void display_1_cycle(){
    for(int y = 0; y< CELL_COUNT; y++){
        for(int x=0; x< CELL_COUNT; x++){
            printf("%d", two_d_map[x][y]);
        }
        printf("\n");
    }
}

void display_all_cycles(int cycles){
    gen_random_2d_map();
    display_1_cycle();
    printf("\n");

    for(int i = 0; i < cycles;i++){
        gen_next_map();
        display_1_cycle();
        usleep(500000);
        printf("\n");
    }
}