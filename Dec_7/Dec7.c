#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct directory {
    struct directory* subdirs[1000];
    struct file* files[1000];
    struct directory* parent_dir; 
    char dir_name[100];
    int dir_size; 
    int num_dirs;
    int done; 
};

void* rec_tree_walk (struct directory* dir, long* best_sofar, int needatleast) {
    if (dir->num_dirs == 0){

        // at a leaf
        int tmp = dir->dir_size - needatleast;
        if (tmp> 0 && dir->dir_size < *best_sofar ) {
            *best_sofar = dir->dir_size;
        }
        dir->done = 1; 
        return rec_tree_walk(dir->parent_dir, best_sofar, needatleast);
    }

    //if not at leaf, we get here: 
    for (int i = 0; i < dir->num_dirs; i ++) {
        if (dir->subdirs[i]->done != 1) {
            return rec_tree_walk(dir->subdirs[i], best_sofar, needatleast);
        }
    }
    // if we get here, then all of the dir unders are done and we can set this to done and go one up:
    int tmp = dir->dir_size - needatleast;
    dir->done = 1; 
    if (tmp> 0 && dir->dir_size < *best_sofar) {
            *best_sofar = dir->dir_size;
        }
    if (dir->parent_dir == NULL ) {
        return NULL; 
    }
    else {
        return rec_tree_walk(dir->parent_dir, best_sofar, needatleast); 
    }
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
        exit(EXIT_FAILURE);
    }

    int ls_ongoing = 0; // only for sanity check. Techincally not needed. 
    struct directory* current_dir = malloc(sizeof(struct directory)); 
   
    current_dir->parent_dir = NULL; 
    current_dir->dir_size = 0; 
    current_dir->num_dirs = 0; 
    current_dir->dir_name[0] = '/'; 
    current_dir->dir_name[1] = '\0';
    int total = 0; 

    //part two; 
    int total_disk_space = 70000000;
    int need_at_least = 30000000; 


    // First I need to create a tree-like data structure from the input. 
    while ((read = getline(&line, &len, fp)) != -1) {
        char tmp_dir_name[100];
        if (line[0] == '$'){

            ls_ongoing = 0; 
            // There are three commands: cd dir, cd .., ls

            // ls
            if (line[2] == 'l') {
                ls_ongoing = 1; 
            }
            else { 
                // we want to go up one level. 
                if (line[5] == '.') {
                    if (current_dir->parent_dir != NULL) {
                        current_dir->parent_dir->dir_size+= current_dir->dir_size;
                        if (current_dir->dir_size < 100000) {
                            total = total + current_dir->dir_size; 
                        } 
                        current_dir = current_dir->parent_dir;
                    }
                }   

                //or go down a dir
                // expecting it to read the dir. 
                else if (sscanf(line, "$ cd %s", tmp_dir_name ) == 1 ) { 
                    //go to that dir inside current dir. 
                    for (int i = 0; i < current_dir->num_dirs; i ++) {
                        if (strcmp(current_dir->subdirs[i]->dir_name,tmp_dir_name) == 0) {
                            current_dir = current_dir->subdirs[i];
                        }
                    }
                }
            }
        }
        else if (ls_ongoing == 1) {
            // we are seing the insides of current dir.  We want to read it into current dir. 
            char name[100];  
            char filesize_c[100];

            // a file always starts by displaying it size. So I check that the first char on line is an int. 
            if ( line[0] >= '0' && line[0] <= '9' ) {

                // Getting file name and file size. 
                sscanf(line, "%s %s", filesize_c, name);  
                int file_size = atoi(filesize_c);
                // adding file size to dirs total size. 
                current_dir->dir_size= file_size + current_dir->dir_size; 
            }

            // file is a dir
            else {
                //initialising dir
                sscanf(line, "dir %s", name);
                current_dir->num_dirs++; 
                current_dir->subdirs[current_dir->num_dirs-1] =  malloc(sizeof(struct directory)); 

                current_dir->subdirs[current_dir->num_dirs-1]->parent_dir = current_dir; 
                current_dir->subdirs[current_dir->num_dirs-1]->dir_size = 0; 
                *current_dir->subdirs[current_dir->num_dirs-1]->subdirs = NULL; 
                current_dir->subdirs[current_dir->num_dirs-1]->done = 0; 
                
                //adding dir to tree
                strcpy(current_dir->subdirs[current_dir->num_dirs-1]->dir_name, name);

            }
        } 
    }
    
    fclose(fp);
    if (line){
        free(line);
    }
    // part one answer:
    printf("Total for part 1: %d \n", total);


    /////////////////// PART TWO ///////////////////////////////
    // going straight up if we don't end at top, and make sure to update dir size on the way. 
    while(current_dir->parent_dir != NULL) {
        current_dir->parent_dir->dir_size = current_dir->parent_dir->dir_size + current_dir->dir_size;
        current_dir = current_dir->parent_dir;
    }
    int need_to_free = total_disk_space -  need_at_least - current_dir->dir_size;
    
    // now I  know how much space I am missing. but this is a neg number. Bc i refuse to use library we do the following stupid thing: 
    need_to_free = need_to_free*-1;

    // I now want to go down the tree and check size of all dirs. Dir closest to 'need to free' will be chosen. 
    long* best_so_far = malloc(sizeof(long));
    *best_so_far = 100000000000; 
    rec_tree_walk(current_dir, best_so_far, need_to_free); 

    printf("part two, free = %ld \n", *best_so_far); 
    
  

    return 0; 
}


