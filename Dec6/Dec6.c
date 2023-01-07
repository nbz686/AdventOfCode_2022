#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Give me a file to read from! Including .txt or other ending \n");
        return 0; 

    }
    // For reading from the file: 
    FILE* fp; 
    char* buffer = NULL; 
    long numbytes; 

    fp = fopen(argv[1], "r");
    
    if (fp == NULL) {
        printf("opening file went wrong");
        exit(EXIT_FAILURE);
    }

    

    //Getting the number of bytes in file: 
    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);

    /* reset the file position indicator to 
        the beginning of the file */
    fseek(fp, 0L, SEEK_SET);

    /* grab sufficient memory for the 
    buffer to hold the text */
    buffer = (char*)calloc(numbytes, sizeof(char));		

    /* memory error */
    if(buffer == NULL) {
        return 1;
    }
 
    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, fp);
    fclose(fp);

    // working on the buffer; 
    int count = 13; 
    while (count < numbytes) {
        char temp[15]; 
        strncpy(temp, &buffer[count - 14-1], 14); 
        count ++; 

        int nomatch = 0;


        //Now check if items are unique
        for (size_t i = 0; i < 14; i++)
        {
            for (size_t j = 0; j < 14; j++)
            {
                if(temp[i] == temp[j] && i != j) {
                    nomatch = 1;
                    break;
                } else if (i == 14 - 1 && j == 14 - 1) {
                    printf("RESULT FOUND: [%s] at: %d\n", temp, count-2);
                    exit(0);
                }
            }
            if (nomatch == 1) {
                break;
            }
        }
    }
    free(buffer);

    return 0; 
}
