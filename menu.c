#include "menu.h"

int CELL_COUNT = 0;

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
    printf("4. Print 2D CA with x rules and y cycles\n");
    printf("0. Exit\n");
}

void get_cell_count(){
    int min_parameter = 0;
    int max_parameter = MAX_CELL_COUNT;

    printf("Enter number of cells: ");
    CELL_COUNT = validation(min_parameter, max_parameter);

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
            case 3:{
                display_cycles(get_number_cycles(),game_of_life_rules,500);
                break;
            }
            case 4:{
                rule_2d=get_rule();
                display_cycles(get_number_cycles(),factor_rules,500);
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