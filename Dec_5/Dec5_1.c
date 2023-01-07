#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    int numElem; 
    char stackarr[1000];
    char* reverse; 
};


int stacknum(int lineIndex) {
    int retval; 
    switch (lineIndex)
    {
    case 1:
        retval = 0; 
        break;
    case 5:
        retval = 1; 
        break;
    case 9:
        retval = 2; 
        break;
    case 13:
        retval = 3; 
        break;
    case 17:
        retval = 4; 
        break;
    case 21:
        retval = 5; 
        break;
    case 25:
        retval = 6; 
        break;
    case 29:
        retval = 7; 
        break;
    case 33: 
        retval = 8;
        break;
     
    default:
        retval = -1;
        break;
    }
    return retval; 
}
int stackstuff(struct stack* fromStack, struct stack* toStack, int NoToMove) {
    // I need to take the topmost element from fromStack and add
    // it on top of tostack. 
    // BAD implementation  bec it "runs" and uses to much space..
    char tomove[NoToMove+1]; 
    printf("no to move: %d \n", NoToMove); 
    tomove[NoToMove] = '\0';

    for (int i = 0; i < NoToMove; i++) {
        tomove[i] = fromStack->reverse[fromStack->numElem-1];
        fromStack->numElem --; 

    }

    for (int i = 0; i< NoToMove; i++) {
        toStack->numElem ++; 
        toStack->reverse[toStack->numElem-1] = tomove[NoToMove-1-i];
    }
    return 0; 
}

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
        printf("opening file went wrong");
        exit(EXIT_FAILURE);
    }

    //Reading from the file. Doing what I need to do inside the loop
    int nextpart = -1; 
    int noStacks = 9; 
    struct stack* stackstruct[noStacks];
    for (int i =noStacks-1; i >= 0; i --) {
        stackstruct[i] = malloc(sizeof(struct stack)); 
        stackstruct[i]->numElem = 0; 
    }

    while ((read = getline(&line, &len, fp)) != -1) {        
        if (*line == '\r') {
            nextpart = 0; 
            printf("first part goes well \n"); 

            // reversing the strings. 
            for (int i = 0; i < noStacks; i++) {
                int len = stackstruct[i]->numElem; 
                stackstruct[i]->reverse = malloc(sizeof(char)*100);
                for (int j = 0; j < len; j++) {
                    stackstruct[i]->reverse[j] = stackstruct[i]->stackarr[len-1-j];
                }
            }
        }

       // datastruct for original stack: 
        if (nextpart == -1) {
            for(int i = 0; i < (int)strlen(line)-2; i++) {
                // we have a char
                if ((int)line[i] >= 65 && (int)line[i] <=90) {
                    int stackno; 
                    stackno = stacknum(i);
                    stackstruct[stackno]->stackarr[stackstruct[stackno]->numElem] = line[i];
                    stackstruct[stackno]->numElem ++; 

                }
            }
        }

        // Here we do what we need to do with the stacks: 
        if (line[0] == 'm' && nextpart == 0) {
            int noToMove; 
            int fromStack; 
            int toStack; 
            sscanf(line, "move %d from %d to %d \n", &noToMove, &fromStack, &toStack);
            stackstuff(stackstruct[fromStack-1], stackstruct[toStack-1], noToMove);
        }   
    }

    // Last thing to do: 
    fclose(fp);
    if (line){
        free(line);
    }
    printf("top of stacks: \n");
    for (int i = 0; i < noStacks; i++) {
        printf("%c", stackstruct[i]->reverse[stackstruct[i]->numElem-1]); 
        //free(stackstruct[i]->reverse);
        //free(stackstruct[i]);

    }
    printf("\n");
  
    return 0; 
}
