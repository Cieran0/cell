#include "stdio.h"
#include "stdlib.h"

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

int main() {
    gen_map(30);
    char in = 0b001;
    printf("In: %s, Out: %d\n",bit_rep[in & 0x0F],map[in]);
    return 0;
}