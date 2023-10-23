#include "menu.h"

void print_menu(){
    printf("1. Display Cellular Automation\n");
    printf("2. Print Cellular Automation to txt\n");
    printf("3. urmum\n");
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
    }
}