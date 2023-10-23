#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define CELL_COUNT 100

char cells[CELL_COUNT] = {0};
char cells_back[CELL_COUNT] = {0};

const char *bit_rep[8] = {
    [0] = "000", [1] = "001", [2] = "010", [3] = "011",
    [4] = "100", [5] = "101", [6] = "110", [7] = "111",
};

char map[] = {
    [0b111] = 0, 
    [0b110] = 0, 
    [0b101] = 0, 
    [0b100] = 0, 
    [0b011] = 0, 
    [0b010] = 0, 
    [0b001] = 0, 
    [0b000] = 0, 
};

void gen_map(char rule) {
    for (char i = 0; i < 8; i++)
    {
        map[i] = ((rule >> i)  & 0x01);
    }
    
}

void random_cells() {
    for (int i = 0; i < CELL_COUNT; i++)
    {
        cells[i] = rand()%2;
    }
}

void print_cells() {
    for (int i = 0; i < CELL_COUNT; i++)
    {
        printf("%d",cells[i]);
    }
    printf("\n");
}

char concat(char values[]) {
    char result=0;
    for (int i = 0; i < 3; i++)
    {
        result |= (values[i] << i);
    }
    return result;
}

char* positions_to_values(char positions[]) {
    char* values = (char*)malloc(sizeof(char)*3);
    values[0] = cells[positions[0]];
    values[1] = cells[positions[1]];
    values[2] = cells[positions[2]];
    return values;
}

void do_generation() {
    char positions[3]={0};
    for (int i = 0; i < CELL_COUNT; i++)
    {
        positions[0]=i+1;
        positions[1]=i;
        positions[2]=i-1;
        for (int j = 0; j < 3; i++)
        {
            if(positions[j] >= CELL_COUNT)
                positions[j]=0;
            else if(positions[j]<0)
                positions[j]=CELL_COUNT-1;
        }
        cells[i]=map[concat(positions_to_values(positions))];
    }
    
}

int main() {
    srand(time(NULL));
    gen_map(30);
    char in = 0b001;
    printf("In: %s, Out: %d\n",bit_rep[in & 0x0F],map[in]);
    random_cells();
    print_cells();
    do_generation();
    print_cells();

    return 0;
}