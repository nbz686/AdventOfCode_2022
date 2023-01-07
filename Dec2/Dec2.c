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
    int total_score = 0; 
    int op_score = 0; 
    int my_score = 0; 
    int round_score = 0; 
    while ((read = getline(&line, &len, fp)) != -1) {
        //Not very safe, but I can get what I need from line[0] and line[2]
        op_score = 0; 
        my_score = 0;
        
        //What does my opponent do?
        switch(line[0]) {
            case 'A': 
                //Rock
                op_score = 1; 
                break; 
            case 'B':
                //Paper
                op_score = 2;
                break; 
            case 'C':
                //Scissors
                op_score = 3; 
                break; 
            default:
                printf("FAIL");
                exit(EXIT_FAILURE);
        }
        //What do I do? 
        switch(line[2]){
            case 'X': 
                //Rock
                my_score = 1; 
                break; 
            case 'Y':
                //Paper
                my_score = 2; 
                break; 
            case 'Z':
                //Scissors
                my_score = 3; 
                break; 
            default:
                printf("FAIL");
                exit(EXIT_FAILURE);
        }
        //Who won?
        //Edge case for scissors losing to rock: 
        if (my_score == 1 && op_score == 3) {
            round_score = 6 + my_score; 
        }
        else if (op_score == 1 && my_score == 3) {
            round_score = 0 + my_score; 
        }
        // I won: 
        else if (my_score > op_score) {
           round_score =  6 + my_score; 
        }
        //Op won: 
        else if (my_score < op_score) {
            round_score = 0 + my_score;
        }
        //Draw: 
        else if(my_score == op_score) {
            round_score = 3 + my_score; 
        }
        total_score = round_score + total_score; 
    }
    fclose(fp);
    
    if (line){
        free(line);
    }
    printf("Total score: %d \n", total_score );
    return 0; 
}
