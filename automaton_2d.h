#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <unistd.h>
#include "map.h"

#define CELL_COUNT_2D 12
#define for_2d(x_name, x_max, y_name, y_max) \
    for (int y_name = 0; y < y_max; y_name++) \
        for (int x_name = 0; x < x_max; x_name++)

extern int two_d_map[CELL_COUNT_2D][CELL_COUNT_2D];
extern int next_2d_map[CELL_COUNT_2D][CELL_COUNT_2D];

void gen_random_2d_map();
void draw_crosshair();
int is_valid_cell(int x, int y);
int apply_life_rules(int neighbours, int alive);
int count_neighbours(int x, int y);
void next_life_gen();
void display_generation();
void display_life_cycles(int cycles);
void display_odd_cycles(int cycles);