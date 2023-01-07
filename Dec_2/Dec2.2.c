#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        //What should I do? 
        switch(line[2]){
            case 'X': 
                // X = I lose
                my_score = 0; 
                break; 
            case 'Y':
                //Y = I need a draw
                my_score = 3; 
                break; 
            case 'Z':
                // Z = I win
                my_score = 6; 
                break; 
            default:
                printf("FAIL");
                exit(EXIT_FAILURE);
                
        }
        //Who won?
        //Edge case for scissors losing to rock: 
            // rock = 1
            // paper = 2
            // scissors = 3
        if (my_score == 6) {
            if (op_score == 3) { // edge case for rock winning over scissors
                round_score = my_score + 1; // 1 for scissor
            }
            else {
                round_score = op_score + 1 + my_score; // if opponent did not do scissors, then I just choose the option with 1 more point
            }
        }
        else if (my_score == 3) {
            round_score = my_score + op_score; // I choose the same as opp if I want a draw
        }
        else if (my_score == 0) {
            if(op_score == 1) { // edge case for rock winning over scissors
            //if op chose rock I need to choose scissors to lose: 
            round_score = my_score + 3; 
            }
            else {
                round_score = my_score + op_score -1; 
            }
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
