/*
main.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description:
*/

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ISIZE 1024

typedef struct{
    int freq;
    char *word;
}Node;

typedef struct{
    int size;
    Node *table;
    int items;
}Hash_Table;

int genHash(char *word, Hash_Table *table);

void rehash(Hash_Table *hash);

Hash_Table* hash_init();

void insert(Hash_Table *hash, char * key, int val);

Node get(Hash_Table *hash, char * key);

double get_load_factor(Hash_Table *hash);

Node popMax(Hash_Table *hash);

int get_num_items(Hash_Table *hash);

void remove_node(int ind, Hash_Table *hash);

void deconstruct(Hash_Table *hash);
