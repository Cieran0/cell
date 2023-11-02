#pragma once

#include "automaton_1d.h"
#include "automaton_2d.h"

void display_main_menu();
void process_menu();
void get_rules_and_lines(int* rules, int* lines);
int get_number_cycles();
void get_cell_count();
void gen_cells_1d();
char* input_name();
int get_rule();
void get_cell_count_2d();