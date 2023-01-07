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

    int ascii = 0; // for easier debugging
    int aoc_val = 0;  // for easier debugging
    int total = 0;  // only one really neccesaryS


    fp = fopen(argv[1], "r");
    int found = 0; 
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    // All the total lenght of lines are even dicvisble by 2. Take strlen(line)
    while ((read = getline(&line, &len, fp)) != -1) {
        found = -1;
        int len = strlen(line)-2;
        for (int i = 0; i <= ((len/2)-1); i++) {
            for (int j = (len/2); j <= (len-1); j++){
                if (line[i] == line[j]  && found != 0) {
                    found = 0; 
                    printf("found MATCH!: %c %c, values of i and j: %d %d \n", line[i], line[j], i , j);
                    char c = line[i];
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
    fclose(fp);
    if (line){
        free(line);
    }
    printf("Total value of identical items is: %d \n", total);
    return 0; 
}
