#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//TODO: solution only works if input file has two empty lines at the bottom. 
// Solution to part 2. I wrote over my solution for part 1 to do solution 2. 



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
    
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    //Reading from the file. Doing what I need to do inside the loop
    int total = 0; 
    while ((read = getline(&line, &len, fp)) != -1) {
        int seq1_low = 0; //whereat = 0; 
        int seq1_high = 0;  //whereat = 1; 
        int seq2_low = 0;  //whereat = 2;
        int seq2_high = 0; //whereat = 3; 
        int whereAt = 0; 
        int dec_place = 0; 
        for (int i = 0; i <= (int)strlen(line)-2; i++ ) {            
            if (line[i] != '-' && line[i] != ',' && (int)line[i] != 13) {
                switch (whereAt)
                {
                case 0:  
                    seq1_low = (10*dec_place*seq1_low) + ((int)line[i]-48); 
                    dec_place ++; 
                    break;

                case 1: 
                    seq1_high = (10*dec_place*seq1_high) + ((int)line[i]-48);
                    dec_place ++; 
                    break;

                case 2:
                    seq2_low = (10*dec_place*seq2_low) + ((int)line[i]-48);
                    dec_place ++; 
                    break;

                case 3: 
                    seq2_high = (10*dec_place*seq2_high) + ((int)line[i]-48);
                    dec_place ++; 
                    break; 

                default:
                    break;
                }
            }
             // not at end of line and getting new number. 
            if (line[i] ==',' || line[i] == '-'){
                whereAt ++; 
                dec_place = 0; 
                
            }
            //at end of line. Do stuff to compare sequences: 13 is ascii carriage return
            if ((int)line[i] == 13 ){

                // checking if they DONT overlap: If they dont do nothing. If they do increment. 
                if ((seq1_high < seq2_low) || ( seq2_high < seq1_low) ) {
                   
                    printf("line: %s", line); 
                    //6-8,2-4
                }
                else {
                    total ++; 
                }
               
                // resetting values for next line
                whereAt = 0; 
                dec_place = 0; 
                seq1_high = 0; 
                seq1_low  =0; 
                seq2_high = 0; 
                seq2_low = 0;
            }
        }
    }

    // Last thing to do: 
    fclose(fp);
    if (line){
        free(line);
    }
    printf("Total num of lines where one seq overlaps the other: %d \n", total);
    return 0; 
}
