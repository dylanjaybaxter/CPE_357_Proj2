#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *rlw(FILE * file){
    char *word;
    int len;
    int lim = 256
    int c;
    if(!*(word = malloc(lim))){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (len = 0; isalpha((c = getc(file))); len++){
        if (len >= lim - 1){
            lim *= 2
            word = realloc(word, lim);
            if (!line){
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        word[len] = c;
    }
    word[len] = 0;
    if(c == EOF && len == 0){
        free(word)
        word = NULL;
    }
    else{
        word = realloc(word, len + 1);
        if(!line){
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
    return word;
}
