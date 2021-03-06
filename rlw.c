/*
rlw.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description: This file contiains a function that takes a file pointer and reads
1 word from it into dynamically allocated memory. If the end of the file is
reached, it returns NULL, and if it should return anything other than a string
of alphanumeric characters, it returns '!'
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
char *rlword(FILE * file){
    char *word;
    int len;
    int lim = 256;
    int c;
    int wordFlag = 0;
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
        wordFlag = 1;
    }
    if(wordFlag){
        word[len] = '\0';
    }
    else{
        word[0] = '!';
        word[1] = '\0';
    }
    if((c == EOF && len == 0)){
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
