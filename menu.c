#include "menu.h"

int cell_count = 0;

int validation(int min_parameter, int max_parameter){
    int number;

    while(!scanf("%d", &number) || number < min_parameter || number > max_parameter){
            printf("invalid input. try again. \n");
            while(getchar()!='\n');
            }

    return number;
}

void print_menu(){
    printf("1. Display 1D Cellular Automaton\n");
    printf("2. Print 1D Cellular Automaton to txt\n");
    printf("3. Display 2D CA rule of life for x cycles\n");
    printf("4. Display 2D CA with x rules and y cycles\n");
    printf("5. Export 2D CA rule of life for x cycles to video\n");
    printf("0. Exit\n");
}

void get_cell_count(){
    int min_parameter = 1;
    int max_parameter = MAX_CELL_COUNT;

    printf("Enter number of cells: ");
    cell_count = validation(min_parameter, max_parameter);
    printf("\n");
}

void get_cell_count_2d(){
    int min_parameter = 1;
    int max_parameter = MAX_CELL_COUNT_2D;

    printf("Enter number of cells: ");
    cell_count_2d = validation(min_parameter, max_parameter);
    printf("\n");
}

void get_rules_and_lines(int* rules, int* lines) {

    int min_rule_number = 0;
    int max_rule_number = 255;

    int min_line_number = 1;
    int max_line_number = 1000;

    printf("Enter a rule: ");
    *rules = validation(min_rule_number, max_rule_number);
    printf("Rule: %d\n",*rules);

    printf("Enter how many lines: ");
    *lines = validation(min_line_number, max_line_number);

    reset_cells();
}

int get_rule(){
    int rule = 0;

    printf("\nEnter rule: ");
    rule = validation(0,255);
    printf("\n");

    return rule;
}

void gen_cells_1d(){
    
  
    printf("\nWould you like to choose first generation or get random: ");
    printf("\n1. Random Generation");
    printf("\n2. Enter Generation\n");

    

    switch(validation(1,2)){

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
    cycles = validation(1,10000);
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
        print_menu();
        int menu_input;
        int lines;
        int rules;
    
        scanf("%d", &menu_input);

        switch(menu_input){
            case 1:{
                get_cell_count();
                get_rules_and_lines(&rules,&lines);
                gen_cells_1d();
                gen_map(rules);
                display_better(lines);
                break;
            }
            case 2:{
                get_cell_count();
                get_rules_and_lines(&rules,&lines);
                gen_cells_1d();
                gen_map(rules);
                print_1d_to_file(lines);
                break;
            }
            //TODO: select size for 2d automaton
            case 3:{
                get_cell_count_2d();
                display_cycles(get_number_cycles(),game_of_life_ruleset,500);
                break;
            }
            case 4:{
                get_cell_count_2d();
                rule_2d=get_rule();
                display_cycles(get_number_cycles(),factor_ruleset,500);
                break;
            }
            case 5: {
                get_cell_count_2d();
                gen_random_board();
                export_to_video(input_name(),cell_count_2d,get_number_cycles(),game_of_life_ruleset);
                break;
            }
            case 0:{
                return;
            }
            default:{
                printf("\nInvalid input, please enter a valid choice. \n");
                break;
            }
        }
    }
}