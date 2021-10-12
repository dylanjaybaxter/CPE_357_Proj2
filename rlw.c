#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
char *rlword(FILE * file){
    char *word;
    int len;
    int lim = 256;
    int c;
    if(!(word = (char*)malloc(lim))){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while(!isalpha(c = getc(file)) && (c!=-1) && (c!=0)){
        /* Do Nothing */
    }
    ungetc(c, file);
    for (len = 0; isalpha((c = getc(file))); len++){
        if (len >= lim - 1){
            lim *= 2;
            word = (char*)realloc(word, lim);
            if (!word){
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        if(c == 1){
            printf("Why do you do this\n");
        }
        word[len] = tolower(c);
    }
    word[len] = '\0';
    if(c == EOF && len == 0){
        free(word);
        word = NULL;
    }
    else{
        word = (char*)realloc(word, len + 1);
        if(!word){
            perror("realloc");
            exit(EXIT_FAILURE);
        }
    }
    return word;
}
