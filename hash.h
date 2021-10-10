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
    int freq;
    char *word;
}

struct Hash_Table{
    int size;
    Node *table;
    int items;
}

int hash(char *word, Hash_Table *table);

void rehash(Hash_Table *hash);

Hash_Table* hash_init();

void insert(Hash_Table *hash, char * key, int val);

Node get(Hash_Table *hash, char * key);

double get_load_factor(Hash_Table *hash);

Node popMax(Hash_Table *hash);

int get_num_items(Hash_Table *hash);

void remove_node(int ind, Hash_Table *hash);

void deconstruct(Hash_Table *hash);
