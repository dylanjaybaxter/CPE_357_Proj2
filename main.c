/*
main.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description:
*/
#include<stdio.h>
#include<unistd.h>
#include"hash.h"
#include"rlw.h"
#DEFINE INIT_K 10

int main(int argc, char* const argv[]){
  /* This function takes a number n and shows the top n most frequent
  words in the file */
  /*Iterate through options */
  int k = INIT_K;
  int opt;
  char *file;

  while((opt = getopt(argc, argv,":n:")) != -1){
    if(opt == 'n'){
	    k = optArg;
    }
    else if(opt == ':'){
        printf("No Value!\n");
    }
    else{
	    printf("Invalid Option!\n");
	    return -1;
    }
  }

  /*Initialize hash and vars*/
  hash = hash_init();
  int fileFlag = 0;
  int val;

    /*Iterate through remaining items and test for files */
    for(;optInd < argc; optInd++){
        if((file = fopen(argv[optInd])) != NULL){
            fileFlag = 1;
            while((word = rlw(file)) != NULL){
                /*Check if word is stored*/
                /*If so, increment number*/
                if((val = get(hash, word)) != NULL){
                    insert(hash, word, val+1);
                }
                /*If not, Initialize*/
                else{
                    insert(hash, word, 1);
                }
            }
        }
    }

    /*If no files, check stdin*/
    if(!fileFlag){
        while((word = rlw(stdin)) != NULL){
            /*Check if word is stored*/
            /*If so, increment number*/
            if((val = get(hash, word)) != NULL){
                insert(hash, word, val+1);
            }
            /*If not, Initialize*/
            else{
                insert(hash, word, 1);
            }
        }
    }

    /*Find the max value k times and display*/
    Hash_Table* currTable;
    printf("The top 10 words (out of %d) are:\n", getNumKeys(hash));
    for(int i=0; i < k, i++){
        currTable = popMax(hash);
        printf("%*%d %s",8,currTable.freq,currTable.word);
    }

}
