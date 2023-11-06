#include "automaton_1d.h"

char cells[MAX_CELL_COUNT] = {0};
char cells_back[MAX_CELL_COUNT] = {0};

//used for testing
const char *bit_rep[8] = {
    [0] = "000", [1] = "001", [2] = "010", [3] = "011",
    [4] = "100", [5] = "101", [6] = "110", [7] = "111",
};

//map init
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

//get map from rule
void gen_map(char rule) {
    for (int i = 0; i < 8; i++)
        map[i] = ((rule >> i)  & 0x01);
}

//generate first row randomly
void random_cells() {
    for (int i = 0; i < cell_count; i++)
        cells[i] = rand()%2;
}

//get starting cells from user instead of randomly
void get_start_cells(){
    int attempts = 3;
    int valid = 0;
    char input[cell_count];
    while(!valid && attempts >= 0){
        printf("Enter the starting cells(length currently %d):\n", cell_count);
        scanf("%s", input);
        if(strlen(input) == cell_count)
            valid = 1;
        else {
            //gives 3 attempts 
            printf("Invalid size try again (%d attempts left):\n",attempts);
            attempts--;
        }
    }

    if(!valid) {
        printf("Ran out of attemps generating random cells instead\n");
        //gen random row if no more attempts
        random_cells();
        return;
    }

    for(int i = 0; i < cell_count; i++){
        if(input[i] == '1' || input[i] == '0')
            cells[i] = input[i] - 48;
        else {
            printf("Invalid input detected, generating random cells instead\n");
            random_cells();
            break;
        }
    }
}

//get random rule
int random_rule(){
    srand(time(NULL));
    return rand()%256;
}

void print_row(char* row, int count) {
    for (int i = 0; i < count; i++)
        if(row[i]){
            //output colour to background white
            printf("\x1B[47m \x1B[0m");
        }
        else{
            //blank space if row[i] = 0
            printf(" ");
        }
    printf("\n");
}

int concat(char values[], int len) {
    int result=0;
    for (int i = 0; i < len; i++)
        result |= (values[i] << i);
    return result;
}

void do_generation_1d() {
    memcpy(cells_back,cells,cell_count);
    char values[3]={0};
    for (int i = 0; i < cell_count; i++) {
        values[0]=cells_back[i == cell_count-1 ? 0 : i+1];
        values[1]=cells_back[i];
        values[2]=cells_back[i == 0 ? cell_count-1 : i-1];
        cells[i]=map[concat(values,3)];
    }
    
}

//print 1d gen to text file
void print_1d_to_file(int line_input){
    char* filename  = "1dCA.txt";
    FILE* f = fopen(filename, "w");

    if(f == NULL)
        printf("Error opening file %s", filename);

    for(int i = 0; i < line_input; i++) {
        for (int i = 0; i < cell_count; i++)
            if(cells[i])
                fprintf(f,"1");
            else
                fprintf(f," ");

        fprintf(f,"\n");
        do_generation_1d();
    }
    fclose(f);
}

//reset
void reset_cells(){
    memset(cells,0,cell_count);
}

//print whole generation
void display_1d_automaton(int line_input){
    for(int i = 0; i < line_input; i++) {
        print_row(cells,cell_count);
        do_generation_1d();
    }
}