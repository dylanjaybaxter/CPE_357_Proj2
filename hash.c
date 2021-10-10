#include <math.h>
#include <stdlib.h>
#include <string.h>
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

int hash(char * word, Hash_Table *table){
    int len = strlen(word);
    int i;
    int hash_value = 0;
    int p = 53;
    int p_pow = 1;
    for (i = 0; i < len; i++){
        hash_value += (word[i] * (p_pow)) % table.size;
        p_pow = (p_pow * p) % table.size;
    }
    return hash_value;
}

void rehash(Hash_Table *hash){
    hash.size *= 2;
    Node *temp = malloc(hash.size * sizeof(Node));
    int i;
    hash.table = 
       
}

Hash_Table* init(){
    Hash_Table hash;
    *hash.size = ISIZE;
    Node *table = malloc(*hash.size * sizeof(Node));
    int i;
    for (i = 0; i < size; i++){
        table[i] = NULL;
    }
    hash.items = 0; 
}  

void insert(Hash_Table hash, char * key, Node val){
    int load = get_load_factor(hash);
    if (load > 0.5){
        rehash(hash);
    }
    int hash_val = hash(val.word, hash);
    while (hash.table[hash_val] != NULL || hash.table[hahs].word != word.word){
        key = ++key % hash.size;
    }
    hash.table[hash_val] = val;
    hash.item++;
}

Node get(Hash_Table hash, int hash_value){
    while (hash.table[hash_val] != NULL || hash.table[hahs].word != word.word){
        key = ++key % hash.size;
    }
    return hash.table[hash_value]
}

double get_load_factor(Hash_Table hash){
    return (double) hash.items / hash.size;
}

Node popMax(){
}

