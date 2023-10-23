#include "menu.h"

void print_menu(){
    printf("1. Display Cellular Automation\n");
    printf("2. Print Cellular Automation to txt\n");
    printf("3. urmum\n");
}

void process_menu(){
    print_menu();
    int menu_input;
    int second_menu_input;
    int rule;
    
    scanf("%d", &menu_input);

    switch(menu_input){
        case 1:{
            printf("Enter a rule: ");
            if(!scanf("%d", &second_menu_input)){
                rule=random_rule();
                gen_map(rule);
                printf("rule: %d\n",rule);
            }
            else {
                gen_map(second_menu_input);
            }
            while(getchar()!='\n');

            cells[CELL_COUNT/2] = 1;
            int line_input = 0;

            printf("Enter how many lines: ");
            scanf("%d", &line_input);
            resetCells();
            display_better(line_input);
            break;
        }
        case 2:{
            printf("Enter a rule: ");
            if(!scanf("%d", &second_menu_input)){
                rule=random_rule();
                gen_map(rule);
                printf("rule: %d\n",rule);
            }
            else {
                gen_map(second_menu_input);
            }
            while(getchar()!='\n');
            
            cells[CELL_COUNT/2] = 1;
            int line_input = 0;

            printf("Enter how many lines: ");
            scanf("%d", &line_input);
            resetCells();
            print_to_file(line_input);
            break;
        }
    }
}