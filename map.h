#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>

#define CELL_COUNT 100

extern char cells[CELL_COUNT];

void gen_map(char rule);
void random_cells();
void print_cells();
char concat(char values[], int len);
char* positions_to_values(char positions[]);
void do_generation();
void print_to_file(int line_input);
void resetCells();
void display_better(int line_input);
int random_rule();