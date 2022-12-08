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
    char* line = NULL; 
    size_t len = 0; 
    ssize_t read; 
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int no_lines = 0; 
    int line_len = 0; 
    while ((read = getline(&line, &len, fp)) != -1) {
        no_lines++; 
        line_len = strlen(line);
    }
    
    fclose(fp);
    
    
    // making space for the grid: 
    char** arr_2d = malloc(sizeof(char*)*no_lines);

    // reading the file into the 2d array: 
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
   
    int line_num = 0; 
    while ((read = getline(&line, &len, fp)) != -1) {
        arr_2d[line_num] = malloc(sizeof(char)*strlen(line));
        strcpy(arr_2d[line_num], line);
        line_num++;
    }
    
    fclose(fp);
    
    // I now have my structure. 

    // I now that the outer trees are visible. 
    int vis_trees = (line_len)*2 + (no_lines-2)*2;
    int ii = 1; 
    int ij = 1; 
    int visible = 0; 
    int lessthan_me = 0; 
    // 
    while (ii <= no_lines-2) {
        while (ij <= line_len-2){
        //printf("checking ii  ij %d %d\n", ii, ij); 
        // checking if tree is visible on the horizontal on my left:
        lessthan_me = 0; 
            for (int j = 0; j <= ij-1; j++) {
                if ((int)arr_2d[ii][ij] > (int)arr_2d[ii][j]) {   
                    lessthan_me++; 
                }   
            }
           // printf("less than me = %d and ij = %d \n", lessthan_me, ij); 
            if (lessthan_me ==ij) {
                visible = 1; 
            }
        lessthan_me = 0; 
        // checking if three is visible on the horizontal on my rigth: 
        for (int j = ij+1; j <= line_len-1; j++) {
                if ((int)arr_2d[ii][ij] > (int)arr_2d[ii][j]) {   
                    lessthan_me++; 
            }   
        }
        //printf("less than me = %d and lne_len - ij -1= %d \n", lessthan_me, line_len-ij-1); 
        if (lessthan_me == line_len-(ij)-1) {
                visible = 1; 
            }

        lessthan_me=0; 
        // cheking if tree is visible on the vertical upwards: 
            for (int i = 0; i <= ii-1; i ++) {
                if ((int)arr_2d[ii][ij] > (int)arr_2d[i][ij]) {  
                    lessthan_me++; 
                } 
            }
            if (lessthan_me == ii) {
                visible = 1; 
            }
       // printf("less than me = %d AND ii = %d \n", lessthan_me, ii); 
        lessthan_me = 0; 
        // checking if three is visible on the vertical downwards: 
            for (int i = ii+1; i <= no_lines-1; i ++) {
                if ((int)arr_2d[ii][ij] > (int)arr_2d[i][ij]) {  
                    lessthan_me++; 
                } 
                
            }
            //printf("less than me %d and no_line-ii %d \n", lessthan_me, no_lines-ii-1); 
            if (lessthan_me == no_lines-ii-1) {
                visible = 1; 
            }

            if (visible == 1){
                //printf("adding %c from ii %d, ij %d \n", arr_2d[ii][ij], ii, ij);
                vis_trees++;
            }
            visible = 0; 
            ij++;
        }
        ii++; 
        ij=1; 
    }
    



    

    // part one answer:
    printf("Total num of visible tress for part 1: %d \n", vis_trees);


    /// /////////// part two: 
    int scenicscore = 0; 
    int h1 = 0; 
    int h2 = 0; 
    int v1 = 0; 
    int v2 = 0; 
    
    ii = 1; 
    ij = 1; 
    while (ii <= no_lines-2) {
        while (ij <= line_len-2){

        // checking how far you can see from tree on the horizontal to the  left:
            for (int j =ij-1; j >=0; j--) {
                if ((int)arr_2d[ii][ij] <= (int)arr_2d[ii][j] && h1 == 0) {   
                    h1 = ij-j; //trying to account for off by one. 
                }   
            }
            // If I am not blocked before edge
            if (h1 == 0) {
                h1 = ij ;
            }

 
            // checking how far you can see from tree on the horizontal to the  right:
            for (int j = ij+1; j <= line_len-1; j++) {
                    if ((int)arr_2d[ii][ij] <= (int)arr_2d[ii][j] && h2== 0 ) { 
                        h2 = j-ij;
                }   
            }
            // If I am not blocked before edge
            if (h2 == 0) {
                h2 = line_len-ij-1; 
            }


            // cheking how far one can see from tree on the vertical upwards: 
            for (int i =ii-1; i >=0; i --) {
                if ((int)arr_2d[ii][ij] <= (int)arr_2d[i][ij] && v1 == 0) {  
                    v1 = ii-i; 
                } 
            }
            // If I am not blocked before edge
            if (v1 == 0) {
                v1 = ii; 
            }
            
            // cheking how far one can see from tree on the vertical down: 
            for (int i = ii+1; i <= no_lines-1; i ++) {
                if ((int)arr_2d[ii][ij] <= (int)arr_2d[i][ij] && v2 == 0) {  
                    v2 = i-ii; 
                } 
                
            }
            // If I am not blocked before edge
            if (v2 == 0) {
                v2 = no_lines-ii-1; 
            }
            int tmp = h1*h2*v1*v2; 
            if (tmp > scenicscore) {
                scenicscore = tmp; 
            }

            ij++;
            h1 = 0; 
            h2 = 0; 
            v1 = 0; 
            v2 = 0; 
        }
        ii++; 
        ij=1; 
    }
    


    printf("Highest scenic score available is: %d \n", scenicscore); 

    if (line){
        free(line);
    }
    return 0; 
}


