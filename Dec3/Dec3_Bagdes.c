#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Give me a file to read from! Including .txt or other ending");
        return 0; 

    }
    // For reading from the file: 
    FILE* fp; 
    char* line = NULL; 
    size_t len = 0; 
    ssize_t read;


    fp = fopen(argv[1], "r");
    
    //getting num of lines: 
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int no_lines = 0; 
    char* str0 = malloc(sizeof(char)*100) ; 
    char* str1 = malloc(sizeof(char)*100); 
    char* str2 = malloc(sizeof(char)*100); 
    int ascii = 0; 
    int aoc_val = 0; 
    int total = 0; 
    int found = 0; 

    while ((read = getline(&line, &len, fp)) != -1) {
        found = -1; 
        if (no_lines % 3 == 0) {
            printf("module 0");
            strcpy(str0, line);
        }
        
        else if (no_lines %3 == 1) {
            printf("module 1");
            strcpy(str1, line);
        }

        else if (no_lines %3 == 2) {
            printf("module 2");

            strcpy(str2, line);
            for (int i = 0; i< strlen(str0)-2; i++){
                for(int j = 0; j < strlen(str1)-2; j++ ){
                    for (int k = 0; k < strlen(str2)-2; k++) {
                        if (str0[i] == str1[j] && str1[j] == str2[k] && found != 0) {
                            found = 0; 
                            char c = str0[i];
                            
                            ascii = (int)c;
                            printf("ascii val: %d \n", ascii);
                            if (ascii -96  > 0) { // if ascii -96 is positive val, then little a
                                aoc_val = ascii -96;  // DIFF BETWEEN ASCII VAL AND AOC_VAL
                            }
                            else {                 // if neg val, then capital A and only need to substract 20. 
                                aoc_val = ascii - 38; // DIFF BETWEEN ASCII VAL AND AOC_VAL
                            }
                            printf("aoc_val = %d \n", aoc_val);
                            total = total + aoc_val; 
                        }
                    }
                }
            }
        }
        no_lines ++;    
    }
    fclose(fp);


   

    if (line){
        free(line);
    }
    printf("Total value of identical items per chunks of 3 is: %d \n", total);
    return 0; 
}
