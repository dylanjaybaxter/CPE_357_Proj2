/*
main.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description:
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

  while((opt = getopt(argc, argv,":n:")) != -1){
    if(opt == 'n'){
        if(isdigit(*optarg)){
            k = *optarg;
        }

    }
    else if(opt == ':'){
        printf("No Value!\n");
        return -1;
    }
    else{
	    printf("Invalid Option!\n");
	    return -1;
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
            while((word = rlword(file)) != NULL){
                /*Check if word is stored*/
                /*If so, increment number*/
                node = get(hashTable, word);
                if((node.word) != NULL){
                    printf("Duplicate: %s\n", word);
                    insert(hashTable, word, node.freq+1);
                }
                else{ /*If not, Initialize*/
                    printf("Unique: %s\n", word);
                    insert(hashTable, word, 1);
                }
            }
            fclose(file);
        }
    }


    /*If no files, check stdin*/
    if(!fileFlag){
        while((word = rlword(stdin)) != NULL){
            /*Check if word is stored*/
            /*If so, increment number*/
            node = get(hashTable, word);
            if((node.word) != NULL){
                printf("Duplicate: %s\n", word);
                insert(hashTable, word, node.freq+1);
            }
            /*If not, Initialize*/
            else{
                printf("Unique: %s\n", word);
                insert(hashTable, word, 1);
            }
        }
    }

    /*Find the max value k times and display*/
    Node currItem;
    int items = get_num_items(hashTable);
    printf("The top %d words (out of %d) are:\n",k, items);
    int i = 0;
    for(; i < k; i++){
        currItem = popMax(hashTable);
        printf("%*d %s\n",8,currItem.freq,currItem.word);
    }
    deconstruct(hashTable);
    return 0;

}
