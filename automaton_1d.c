#include "automaton_1d.h"

char cells[MAX_CELL_COUNT] = {0};
char cells_back[MAX_CELL_COUNT] = {0};

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
        map[i] = ((rule >> i)  & 0x01);
}

void random_cells() {
    for (int i = 0; i < CELL_COUNT; i++)
        cells[i] = rand()%2;
}

void get_start_cells(){
    int valid = 0;
    char input[CELL_COUNT];
    while(!valid){
        printf("Enter the starting cells(length currently %d): ", CELL_COUNT);
        scanf("%s", input);
        if(strlen(input) != CELL_COUNT){
            printf("invalid size");
        }
        else{
            valid = 1;
        }
    }

    for(int i = 0; i < CELL_COUNT; i++){
        if(input[i] == '1')
            cells[i] = 1;
        else
            cells[i] = 0;
    }
}

int random_rule(){
    srand(time(NULL));
    return rand()%256;
}

void print_row(char* row, int count) {
    for (int i = 0; i < count; i++)
        if(row[i]){
            printf("\x1B[41m \x1B[0m");
        }
        else{
            printf(" ");
        }
    printf("\n");
}

char concat(char values[], int len) {
    char result=0;
    for (int i = 0; i < len; i++)
        result |= (values[i] << i);
    return result;
}

void do_generation_1d() {
    memcpy(cells_back,cells,CELL_COUNT);
    char values[3]={0};
    for (int i = 0; i < CELL_COUNT; i++) {
        values[0]=cells_back[i == CELL_COUNT-1 ? 0 : i+1];
        values[1]=cells_back[i];
        values[2]=cells_back[i == 0 ? CELL_COUNT-1 : i-1];
        cells[i]=map[concat(values,3)];
    }
    
}

void print_1d_to_file(int line_input){
    char* filename  = "1dCA.txt";
    FILE* f = fopen(filename, "w");

    if(f == NULL)
        printf("Error opening file %s", filename);

    for(int i = 0; i < line_input; i++) {
        for (int i = 0; i < CELL_COUNT; i++)
            if(cells[i])
                fprintf(f,"1");
            else
                fprintf(f," ");

        fprintf(f,"\n");
        do_generation_1d();
    }
    fclose(f);
}

void reset_cells(){
    memset(cells,0,CELL_COUNT);
}

void display_better(int line_input){
    for(int i = 0; i < line_input; i++) {
        print_row(cells,CELL_COUNT);
        do_generation_1d();
    }
}