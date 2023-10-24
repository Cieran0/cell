#include "menu.h"

void print_menu(){
    printf("1. Display Cellular Automation\n");
    printf("2. Print Cellular Automation to txt\n");
    printf("3. Print 2D CA for x cycles\n");
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
    resetCells();
}

int get_number_cycles(){
    int cycles = 0;

    printf("Enter number of cycles: ");
    scanf("%d", &cycles);
    printf("\n");

    return cycles;
}

void process_menu(){
    print_menu();
    int menu_input;
    int lines;
    int rules;
    
    scanf("%d", &menu_input);

    switch(menu_input){
        case 1:{
            get_rules_and_lines(&rules,&lines);
            display_better(lines);
            break;
        }
        case 2:{
            get_rules_and_lines(&rules,&lines);
            print_to_file(lines);
            break;
        }
        case 3:{
            display_life_cycles(get_number_cycles());
            break;
        }
    }
}