#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// solution inspired from https://github.com/brandonchinn178/advent-of-code/blob/main/2022/Day10.c


int main(int argc, char** argv) {

    if (argc != 2) {
        printf("Give me a file to read from! Including .txt or other ending \n");
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


    // register x starts at 1: 
    int reg_x = 1; 

    // for part 1: 
    int total = 0; 

    // cycle_numbers. 
    int cycle_num = 1; 
    

    while ((read = getline(&line, &len, fp)) != -1) {
        int cycles, val; 

       if (line[0] == 'n'){
        // it takes one cycle for noop to execute and it adds 0 to the register. 
            cycles = 1; 
            val = 0; 
       }

       else {
        // it takes two cycles for addx to execute and it adds val to the register after these two cycles.
            cycles = 2; 
            val = atoi(line + 4);

        }

        for (int i = 0; i < cycles; i ++) {
            // checking if cycle num is one of those of interest. 
            if (cycle_num %40 == 20) {
                total += cycle_num*reg_x;
            }

////////// PART TWO ///////////////////////////// 

            if (cycle_num%40 == reg_x || cycle_num%40== reg_x +1 || cycle_num%40 == reg_x+2) {
                printf("#");
            }
            else {
                printf(".");
            }
            if((cycle_num%40 ==0)) {
                printf("\n");
            }

            /// incrementing counter until we can beging reading next instruction   
            cycle_num++;
        }
        reg_x +=val; 
    }

    printf("\n"); 

    
    fclose(fp);
    if (line){
        free(line);
    }

    printf("Finished. Total: %d \n ", total );
    

    return 0; 
}
