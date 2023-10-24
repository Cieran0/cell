#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <unistd.h>
#include "map.h"

extern int two_d_map[CELL_COUNT][CELL_COUNT];
extern int next_2d_map[CELL_COUNT][CELL_COUNT];
extern int neighbour_count;

void gen_random_2d_map();
void gen_next_map();
void display_1_cycle();
void display_all_cycles(int cycles);
void draw_crosshair();