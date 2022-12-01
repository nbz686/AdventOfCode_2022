#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: solution only works if input file has two empty lines at the bottom. 

struct TopPlaces{
    int First; 
    int Second; 
    int Third; 
    int totalKcal; 
};

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

    struct TopPlaces Top; 
    Top.First = 0; 
    Top.Second = 0; 
    Top.Third = 0; 
    Top.totalKcal = 0; 
    int currentKcal = 0; 

    while ((read = getline(&line, &len, fp)) != -1) {
        //If the line is a blank line we have a new elf:  
        if(*line == '\n' || *line == '\r') {
            int tmp  = -1; 
            //To get fewer comparison I only check if current Kcal makes it into top three. 
            if (Top.Third < currentKcal) {
                    if (Top.First < currentKcal && tmp == -1) {
                        Top.Third = Top.Second; 
                        Top.Second = Top.First;
                        Top.First = currentKcal;
                        tmp = 0; 
                    }
                    if (Top.Second < currentKcal && tmp == -1) {
                        Top.Third = Top.Second; 
                        Top.Second = currentKcal;
                        tmp = 0; 
                    }
                    if (Top.Third < currentKcal && tmp == -1) {
                        Top.Third = currentKcal;
                        tmp = 0; 
                    }
                }                
            currentKcal = 0; 
            //printf("New elf, current top three: %d %d %d \n", Top.First, Top.Second, Top.Third);
            }

        currentKcal += atoi(line);    
    }
    fclose(fp);
    if (line){
        free(line);
    }
    printf("Top three elves have %d kcal with them in total \n ", Top.First + Top.Second + Top.Third);
    return 0; 
}
