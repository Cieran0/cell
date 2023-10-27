#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <unistd.h>
#include "automaton_1d.h"

#define CELL_COUNT_2D 20
#define for_2d(x_name, x_max, y_name, y_max) \
    for (int y_name = 0; y < y_max; y_name++) \
        for (int x_name = 0; x < x_max; x_name++)
#define msleep(milliseconds) usleep(milliseconds*1000)

extern char two_d_map[CELL_COUNT_2D][CELL_COUNT_2D];
extern char next_2d_map[CELL_COUNT_2D][CELL_COUNT_2D];
extern int rule_2d;

void gen_random_2d_map();
void draw_crosshair();
int is_valid_cell(int x, int y);
int apply_life_rules(int neighbours, int alive);
int count_neighbours(int x, int y);
void display_generation();
void display_cycles(int cycles, void (*ruleset)(void), int m_delay);
void factor_rules();
void game_of_life_rules();