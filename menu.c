#include "menu.h"

int cell_count = 0;

int get_valid_number(int min_parameter, int max_parameter){
    int number;

    while(!scanf("%d", &number) || number < min_parameter || number > max_parameter){
            printf("invalid input. try again. \n");
            while(getchar()!='\n');
            }

    return number;
}

void display_main_menu(){
    printf("Select An Option\n");
    printf("1. 1D Cellular Automaton\n");
    printf("2. 2D Cellular Automaton\n");
    printf("0. Exit\n");
}

void display_1d_menu() {
    printf("\nSelect An Option\n");
    printf("1. Display 1D Cellular Automaton on the console\n");
    printf("2. Output 1D Cellular Automaton to file\n");
    printf("0. Main menu\n");
}

void process_1d_menu() {
    get_cell_count();
    int rule = get_rule();
    gen_map(rule);
    int cycles = get_number_cycles();
    reset_cells();
    gen_cells_1d();
    display_1d_menu();
    switch (get_valid_number(0,2))
    {
        case 1: {
            display_1d_automaton(cycles);
            break;
        }
        case 2: {
            print_1d_to_file(cycles);
            break;
        }
        case 0:
            return;
    }
}

void display_2d_menu() {
    printf("\nSelect A Ruleset\n");
    printf("1. Game of life\n");
    printf("2. Factor\n");
    printf("3. Rule 2D\n");
    printf("0. Main menu\n");
}

void* process_2d_menu() {
    display_2d_menu();
    switch (get_valid_number(0,3))
    {
        case 1:
            return game_of_life_ruleset;
        case 2:
            return factor_ruleset;
        case 3:
            return rule_2d_ruleset;
        case 0:
            break;
    }
    return NULL;
}

void display_2d_sub_menu() {
    printf("\nSelect An Option\n");
    printf("1. Display on the console\n");
    printf("2. Export to video file\n");
    printf("0. Main menu\n");
}

void process_2d_sub_menu(void* ruleset) {
    get_cell_count_2d();
    int rule = 0;
    if(ruleset == NULL) 
        return;
    if(ruleset != game_of_life_ruleset)
        rule = get_rule();
    rule_2d=rule;
    printf("HERE:1\n");
    gen_map_2d(rule_2d);
    printf("HERE:2\n");
    int cycles = get_number_cycles();
    printf("HERE:3\n");
    gen_random_board();
    printf("HERE:4\n");
    display_2d_sub_menu();
    switch (get_valid_number(0,2))
    {
    case 1:
        display_cycles(cycles,ruleset,500);
        break;
    case 2:
        export_to_video(input_name(),cell_count_2d,cycles,ruleset);
        break;
    case 0:
        return;
    }
}

void get_cell_count(){
    int min_parameter = 1;
    int max_parameter = MAX_CELL_COUNT;

    printf("Enter number of cells: ");
    cell_count = get_valid_number(min_parameter, max_parameter);
    printf("\n");
}

void get_cell_count_2d(){
    int min_parameter = 1;
    int max_parameter = MAX_CELL_COUNT_2D;

    printf("Enter number of cells: ");
    cell_count_2d = get_valid_number(min_parameter, max_parameter);
    printf("\n");
}

int get_rule(){
    int rule = 0;

    printf("\nEnter rule: ");
    rule = get_valid_number(0,255);
    printf("\n");

    return rule;
}

void gen_cells_1d(){

    printf("\nWould you like to choose first generation or get random: ");
    printf("\n1. Random Generation");
    printf("\n2. Enter Generation\n");
    switch(get_valid_number(1,2)){

        case 1:{
            random_cells();
            break;
        }
        case 2:{
            get_start_cells();
            break;
        }
        default:{
            printf("\nInvalid input, please enter a valid choice. \n");
        }
    }  
}

int get_number_cycles(){
    int cycles = 0;

    printf("Enter number of cycles: ");
    cycles = get_valid_number(1,10000);
    printf("\n");

    return cycles;
}

char name_buffer[255] = {0};
char* input_name(){
    memset(name_buffer, 0, 255);
    printf("enter the file name: \n");
    scanf("%s", name_buffer);

    return name_buffer;
}

void process_menu(){
    while(1){
        display_main_menu();

        switch(get_valid_number(0,2)){
            case 1: {
                process_1d_menu();
                break;
            }
            case 2: {
                process_2d_sub_menu(process_2d_menu());
                break;
            }
            case 0:
                return;
        }
    }
}