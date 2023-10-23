#include "menu.h"

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

int random_rule(){
    srand(time(NULL));
    int r = rand()%256;

    return r;
}

void print_cells() {
    for (int i = 0; i < CELL_COUNT; i++)
    {
        printf("%d",cells[i]);
    }
    printf("\n");
}

char concat(char values[], int len) {
    char result=0;
    for (int i = 0; i < len; i++)
    {
        result |= (values[i] << i);
    }
    return result;
}

void do_generation() {
    memcpy(cells_back,cells,CELL_COUNT);
    char values[3]={0};
    for (int i = 0; i < CELL_COUNT; i++)
    {
        values[0]=cells_back[i == CELL_COUNT-1 ? 0 : i+1];
        values[1]=cells_back[i];
        values[2]=cells_back[i == 0 ? CELL_COUNT-1 : i-1];
        cells[i]=map[concat(values,3)];
    }
    
}

void print_to_file(int line_input){

    char* filename  = "1dCA.txt";
    FILE* f = fopen(filename, "w");

    if(f == NULL){
        printf("Error opening file %s", filename);
    }

    for(int i = 0; i < line_input; i++){
        for (int i = 0; i < CELL_COUNT; i++){
        fprintf(f,"%d",cells[i]);
        }
        fprintf(f,"\n");
        do_generation();
    }
    fclose(f);
}

void resetCells(){
    memset(cells,0,CELL_COUNT);
    cells[50] = 1;
}

void display_better(int line_input){
    for(int i = 0; i < line_input; i++){
        print_cells();
        do_generation();
    }
}

int main() {

    process_menu();

    return 0;
}