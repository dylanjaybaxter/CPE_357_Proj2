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

int opt;
char *file;

int main(int argc, char* const argv[]){
  /* This function takes a number n and shows the top n most frequent
  words in the file */
  /*Iterate through options */
  int k = 10;

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

  /*Initialize hash */
  hash = hash_init();
  int fileFlag = 0;

    /*Iterate through remaining items and test for files */
    for(;optInd < argc; optInd++){
        if((file = fopen(argv[optInd])) != NULL){
            fileFlag = 1;
            while((word = rlw(file)) != NULL){
                /*Check if word is stored*/
                /*If so, increment number*/
                if(isKey(hash,word)){
                    insert(hash, word, get(hash, word)+1);
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
            if(isKey(hash,word)){
                insert(hash, word, get(hash, word)+1);
            }
            /*If not, Initialize*/
            else{
                insert(hash, word, 1);
            }
        }
    }

    /*Find the max value k times and display */

}
