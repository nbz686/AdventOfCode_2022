#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: solution only works if input file has two empty lines at the bottom. 
// Solution to part 2. I wrote over my solution for part 1 to do solution 2. 


int main() {
    // For reading from the file: 
    FILE* fp; 
    char* line = NULL; 
    size_t len = 0; 
    ssize_t read; 
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int First = 0; 
    int Second = 0; 
    int Third = 0; 
    int currentKcal = 0; 

    while ((read = getline(&line, &len, fp)) != -1) {
        //If the line is a blank line we have a new elf:  
        if(*line == '\n' || *line == '\r') {
            int tmp  = -1; 
            //To get fewer comparison I only check if current Kcal makes it into top three. 
            if (Third < currentKcal) {
                    if (First < currentKcal && tmp == -1) {
                        Third = Second; 
                        Second = First;
                        First = currentKcal;
                        tmp = 0; 
                    }
                    if (Second < currentKcal && tmp == -1) {
                        Third = Second; 
                        Second = currentKcal;
                        tmp = 0; 
                    }
                    if (Third < currentKcal && tmp == -1) {
                        Third = currentKcal;
                        tmp = 0; 
                    }
                }                
            currentKcal = 0; 
            //printf("New elf, current top three: %d %d %d \n", First, Second, Third);
            }

        currentKcal += atoi(line);    
    }
    fclose(fp);
    if (line){
        free(line);
    }
    printf("Top three elves have %d kcal with them in total \n ", First + Second + Third);
    return 0; 
}
