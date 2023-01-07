#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(int argc, char** argv) {

    if (argc != 3) {
        printf("Give me a file to read from! Including .txt or other ending AND no of monkeys \n");
        return 0; 

    }
    // For reading from the file: 
    FILE* fp; 
    char* line = NULL; 
    size_t len = 0; 
    ssize_t read; 
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int num_of_monkeys = atoi(argv[2]);

    struct monkey
    {
        unsigned long long int items[100];
        int no_items; 

        char monkey_type_op; 
        char monkey_op_val[10];  // can be int or 'llu'

        int test_div_by; 

        int true_monkey;
        int false_monkey; 

        long int inspected_items; 
    };
   
    struct monkey* monkeys = malloc(sizeof(struct monkey)*num_of_monkeys);



    int line_no = 1; 
    int monkey_num = -1; 


    while ((read = getline(&line, &len, fp)) != -1) {
        if (line[0] == 'M') {
            line_no = 0; 
            monkey_num++;

        }
        else if (line[0] == '\n') {
           line_no =0; 
        }
        else {
            switch (line_no)
            {
            case 1:
            // monkey with most start with 8 items. 
            // sscanf returns the number of items it has read to
                monkeys[monkey_num].no_items = 
                    sscanf(line, "  Starting items: %llu, %llu, %llu, %llu, %llu, %llu, %llu, %llu", 
                        &monkeys[monkey_num].items[0], 
                        &monkeys[monkey_num].items[1],
                        &monkeys[monkey_num].items[2],
                        &monkeys[monkey_num].items[3],
                        &monkeys[monkey_num].items[4],
                        &monkeys[monkey_num].items[5],
                        &monkeys[monkey_num].items[6],
                        &monkeys[monkey_num].items[7]);                 
                monkeys[monkey_num].inspected_items = 0; 
                break;

            case 2:
                sscanf(line, "  Operation: new = old %c %s", &monkeys[monkey_num].monkey_type_op , monkeys[monkey_num].monkey_op_val); 
                break;
            case 3:
                sscanf(line, "  Test: divisible by %d", &monkeys[monkey_num].test_div_by ); 
                break;
            case 4:
                sscanf(line, "    If true: throw to monkey %d", &monkeys[monkey_num].true_monkey); 
                break;
            case 5:
                sscanf(line, "    If false: throw to monkey %d", &monkeys[monkey_num].false_monkey); 
                break;
            
            default:
                break;
            }
        }
        line_no++; 
    }

    // Handling overflow by finding a common denominator
    int modulo = 1; 
    for (int i = 0; i < num_of_monkeys; i ++) {
       modulo = modulo* (monkeys[i].test_div_by);
    }   
    printf("modulo %d \n", modulo ); 

        
    // I have now parsed the file. 
    // all monkeys throwing all their stuff is one round; 
    for (int num_rounds = 1; num_rounds <= 10000; num_rounds ++) {
        for (int i = 0; i < num_of_monkeys; i ++) {
            for (int j = 0; j < monkeys[i].no_items; j++) {
                unsigned long long int worry = monkeys[i].items[j];
                monkeys[i].inspected_items ++; 

                int op_val; 
                if (strcmp(monkeys[i].monkey_op_val, "old")==0) {
                    op_val = worry;
                }
                else {
                    op_val = atoi(monkeys[i].monkey_op_val);
                }

                if (monkeys[i].monkey_type_op == '*') {
                    worry = worry* op_val;
                }
                else {
                    worry = worry + op_val;
                }
                worry = worry%modulo;
               
                if ((worry % monkeys[i].test_div_by) == 0) {
                    int send_to =  monkeys[i].true_monkey;
                    monkeys[send_to].no_items ++; 
                    monkeys[send_to].items[monkeys[send_to].no_items-1] = worry; 

                }
                else {
                    int send_to =  monkeys[i].false_monkey;
                    monkeys[send_to].no_items ++; 
                    monkeys[send_to].items[monkeys[send_to].no_items-1] = worry; 
                }
            }
            monkeys[i].no_items = 0; 
        }
       
    }

    printf("\n"); 


    fclose(fp);
    if (line){
        free(line);
    }

    long best  = 0; 
    long snd_best = 0; 
    for (int i = 0; i < num_of_monkeys; i ++) {
        printf("Monkey %d inspected %ld items \n ", i, monkeys[i].inspected_items);    
        if (monkeys[i].inspected_items > best) {
            snd_best = best; 
            best = monkeys[i].inspected_items;
        }
        else if  (monkeys[i].inspected_items >snd_best ) {
           
            snd_best = monkeys[i].inspected_items;
        }
    }
    printf("best * %ld snd best %ld is %ld \n",best, snd_best, best*snd_best); 
    return 0; 
}
