#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
    int numElem; 
    char stackarr[100];
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
int stackstuff(struct stack* fromStack, struct stack* toStack) {
    // I need to take the topmost element from fromStack and add
    // it on top of tostack. 
    // BAD implementation  bec it "runs" and uses to much space..
    char toMove = fromStack->reverse[fromStack->numElem-1];
    fromStack->numElem--;

    toStack->numElem ++;
    toStack->reverse[toStack->numElem-1]  = toMove;
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
    struct stack* stackstruct[9];
    for (int i =8; i >= 0; i --) {
        stackstruct[i] = malloc(sizeof(struct stack)); 
        stackstruct[i]->numElem = 0; 
    }

    while ((read = getline(&line, &len, fp)) != -1) {        
        if (*line == '\r') {
            nextpart = 0; 
            printf("first part goes well \n"); 
            printf("top of stack 0 and 8:  %c, %c\n", stackstruct[0]->stackarr[stackstruct[0]->numElem-1],  stackstruct[8]->stackarr[stackstruct[8]->numElem-1]);
            // reversing the strings. 
            for (int i = 0; i < 9; i++) {
                stackstruct[i]->reverse = malloc(sizeof(char)*(int)strlen(stackstruct[i]->stackarr));
                for (int j = 0; j < (stackstruct[i]->numElem); j++) {
                    stackstruct[i]->reverse[j] = stackstruct[i]->stackarr[stackstruct[i]->numElem-1-j];
                }
            }
            printf("top of rev stack 0 and 8:  %c, %c\n", stackstruct[0]->reverse[stackstruct[0]->numElem-1],  stackstruct[8]->reverse[stackstruct[8]->numElem-1]);
        }

       // datastruct for original stack: 
        if (nextpart == -1) {
          printf("first part");
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
            sscanf(line, "move %d from %d to %d", &noToMove, &fromStack, &toStack);
            if (noToMove != 0) {
                for (int i = 0; i< noToMove; i++ ) {
                    stackstuff(stackstruct[fromStack-1], stackstruct[toStack-1]);
                }
            }
        }   
    }

    // Last thing to do: 
    fclose(fp);
    if (line){
        free(line);
    }
    printf("top of stacks: \n");
    for (int i = 0; i < 9; i++) {
        printf("%c", stackstruct[i]->reverse[stackstruct[i]->numElem-1]); 
        //free(stackstruct[i]->reverse);
        //free(stackstruct[i]);

    }
    printf("\n");
  
    return 0; 
}
