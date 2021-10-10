/*
main.c
Project: CPE 357 Project 2
Author: Dylan Baxter, Van Park
Description:
*/

#include<string.h>
#include<stdlib.h>
#define ISIZE = 1024

struct Node{
    int freq
    char *word;
}

struct Hash_Table{
    int size;
    Node *table;
    int items;
}

int hash(char *word, Hash_Table *table);

void rehash(Hash_Table *hash);

Hash_Table* init();

void insert(Hash_Table *hash char * key, Node val);

Node get(Hash_Tabl *hash, int hash_value);

double get_load_factor(Hash_Table *hash);

Node popMax();

int get_num_items(Hash_Table *hash);

void remove();
