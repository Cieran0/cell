#include "map.h"

char cells[CELL_COUNT] = {0};
char cells_back[CELL_COUNT] = {0};

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
    values[0] = cells_back[positions[0]];
    values[1] = cells_back[positions[1]];
    values[2] = cells_back[positions[2]];
    return values;
}

void do_generation() {
    memcpy(cells_back,cells,CELL_COUNT);
    char positions[3]={0};
    for (int i = 0; i < CELL_COUNT; i++)
    {
        positions[0]=i+1;
        positions[1]=i;
        positions[2]=i-1;
        for (int j = 0; j < 3; j++)
        {
            if(positions[j] >= CELL_COUNT)
                positions[j]=0;
            else if(positions[j]<0)
                positions[j]=CELL_COUNT-1;
        }
        cells[i]=map[concat(positions_to_values(positions))];
    }
    
}

void print_to_file(int line_input){

    char* filename  = "1dCA.txt";
    FILE* f = fopen(filename, "w");

    if(f == NULL){
        printf("Error opening file %s", filename);
    }

    for(int i = 0; i < line_input; i++){
        do_generation();
        for (int i = 0; i < CELL_COUNT; i++){
        fprintf(f,"%d",cells[i]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

void resetCells(){
    memset(cells,0,CELL_COUNT);
    cells[50] = 1;
}

int main() {
    srand(time(NULL));
    gen_map(30);
    char in = 0b001;
    printf("In: %s, Out: %d\n",bit_rep[in],map[in]);
    cells[50] = 1;
    //random_cells();
    print_cells();

    int line_input = 0;

    printf("Enter how many lines: ");
    scanf("%d", &line_input);

    print_to_file(line_input);

    resetCells();
    for(int i = 0; i < 49; i++){
        do_generation();
        print_cells();
    }
    return 0;
}