#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>

#define CELL_COUNT 100

const char *bit_rep[8] = {
    [0] = "000", [1] = "001", [2] = "010", [3] = "011",
    [4] = "100", [5] = "101", [6] = "110", [7] = "111",
};

void gen_map(char rule);
void random_cells();
void print_cells();
char concat(char values[]);
char* positions_to_values(char positions[]);
void do_generation();
void print_to_file(int line_input);
void resetCells();