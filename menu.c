#include "menu.h"

int CELL_COUNT = 0;

void print_menu(){
    printf("1. Display 1D Cellular Automaton\n");
    printf("2. Print 1D Cellular Automaton to txt\n");
    printf("3. Display 2D CA rule of life for x cycles\n");
    printf("4. Display 2D CA with x rules and y cycles\n");
    printf("5. Export 2D CA rule of life for x cycles to video\n");
    printf("0. Exit\n");
}

void get_cell_count(){
    printf("Enter number of cells: ");
    scanf("%d", &CELL_COUNT);
    printf("\n");
}

void get_rules_and_lines(int* rules, int* lines) {
    printf("Enter a rule: ");
    if(!scanf("%d", rules)){
        *rules=random_rule();
        gen_map(*rules);
        printf("rule: %d\n",*rules);
    }
    else {
        gen_map(*rules);
    }
    while(getchar()!='\n');
    printf("Enter how many lines: ");
    scanf("%d", lines);
    reset_cells();
}

int get_rule(){
    int rule = 0;

    printf("\nEnter rule: ");
    scanf("%d", &rule);
    printf("\n");

    return rule;
}

void gen_cells_1d(){
    int choice = -1;
    printf("\nWould you like to choose first generation or get random: ");
    printf("\n1. Random Generation");
    printf("\n2. Enter Generation\n");

    scanf("%d", &choice);

    switch(choice){
        case 1:{
            random_cells();
            break;
        }
        case 2:{
            get_start_cells();
            break;
        }
    }
}

int get_number_cycles(){
    int cycles = 0;

    printf("Enter number of cycles: ");
    scanf("%d", &cycles);
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
                display_better(lines);
                break;
            }
            case 2:{
                get_cell_count();
                get_rules_and_lines(&rules,&lines);
                gen_cells_1d();
                print_1d_to_file(lines);
                break;
            }
            //TODO: select size for 2d automaton
            case 3:{
                display_cycles(get_number_cycles(),game_of_life_rules,500);
                break;
            }
            case 4:{
                rule_2d=get_rule();
                display_cycles(get_number_cycles(),factor_rules,500);
                break;
            }
            case 5: {
                gen_random_2d_map();
                //TODO: set name for output video file
                export_to_video("test.y4m",CELL_COUNT_2D,get_number_cycles(),game_of_life_rules);
                break;
            }
            case 0:{
                return;
            }
        }
    }
}