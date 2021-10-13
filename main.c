/*
main.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description: This file contains the main functionality for fw, which takes
an argument from the command line in the form fw -n k file_1 file_2 ...
and outputs the k most common words in the files. If no files are provided
the function takes input from stdin and with no k specified k defaults to 10
*/
#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<getopt.h>
#include"hash.h"
#include"rlw.h"
#define INIT_K 10

int main(int argc, char* const argv[]){
  /* This function takes a number n and shows the top n most frequent
  words in the file */
  /*Iterate through options */
  int k = INIT_K;
  int opt;
  FILE *file;

  /*Search for option -n and assign k if it exsists*/
  while((opt = getopt(argc, argv,":n:")) != -1){
    /*assign k if -n is found*/
    if(opt == 'n'){
        /*check k is a positive integer*/
        if(isdigit(*optarg) && atoi(optarg) >= 0){
            k = atoi(optarg);
        }
        else{
            perror("usage: fw -n pos_integer input_1 input_2");
            exit(EXIT_FAILURE);
        }

    }
    /*check for missing number*/
    else if(opt == ':'){
        perror("usage: fw -n pos_integer input_1 input_2");
        exit(EXIT_FAILURE);
    }
  }

  /*Initialize hash and vars*/
  Hash_Table *hashTable = hash_init();
  int fileFlag = 0;
  Node node;

    char* word;
    /*Iterate through remaining items and test for files */
    for(;optind < argc; optind++){
        if((file = fopen(argv[optind],"r")) != NULL){
            fileFlag = 1;
            /*Check if word is stored*/
            while((word = rlword(file)) != NULL){
                /*If so, increment number*/
                node = get(hashTable, word);
                /* word is not an empty string '\0\0'*/
                if(*word != '!'){
                    if((node.word) != NULL){
                        /*printf("WordRead: %s \n", word);*/
                        insert(hashTable, word, node.freq+1);
                        free(node.word);
                    }
                    else{ /*If not, Initialize*/
                        /*printf("WordRead: %s \n", word);*/
                        insert(hashTable, word, 1);
                        free(node.word);
                    }
                }
                else{
                    free(word);
                }
            }
            fclose(file);
        }
        /*Check if word is stored*/
        else if(file == NULL){
            perror(argv[optind]);
            fileFlag = 1;
        }
    }


    /*If no files, check stdin*/
    if(!fileFlag){
        while((word = rlword(stdin)) != NULL){
            /*Check if word is stored*/
            /*If so, increment number*/
            node = get(hashTable, word);
            if((node.word) != NULL){
                insert(hashTable, word, node.freq+1);
                free(node.word);
            }
            /*If not, Initialize*/
            else{
                insert(hashTable, word, 1);
                free(node.word);
            }
        }
    }

    /*Find the max value k times and display each
    (Max value removed)*/
    Node currItem;
    int items = get_num_items(hashTable);
    printf("The top %d words (out of %d) are:\n",k, items);
    int i = 0;
    for(; i < k; i++){
        currItem = popMax(hashTable);
        if(currItem.word != NULL){
            printf("%*d %s\n",9,currItem.freq,currItem.word);
            free(currItem.word);
        }
    }
    /*Deconstruct Hash Table*/
    deconstruct(hashTable);
    return 0;

}
