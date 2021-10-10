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
    int key = 0;
    int p = 53;
    int p_pow = 1;
    for (i = 0; i != 0; i++){
        key += (word[i] * (p_pow)) % table.size;
        p_pow = (p_pow * p) % table.size;
    }
    table.items++;
    return key;
}

void rehash(Hash_Table *hash){
    hash.size *= 2;
    hash.table = realloc(hash.table, hash.size);   
}

Hash_Table* init(){
    Hash_Table hash;
    hash.size = ISIZE;
    Node *table = malloc(hash.size);
    int i;
    for (i = 0; i <= size; i++){
        table[i] = NULL;
    }
    hash.items = 0; 
}  

void insert(Hash_Table hash, Node word){
    int load = get_load_factor(hash);
    if (load < 0.5){
        rehash(hash);
    }
    int key = hash(word.word, hash);
    if (hash.table[key] == NULL || hash.table[key].word == word.word){
        hash.table[key] = word;
    }   
    else{
        while (hash.table[key] != NULL || hash.table[key].word == word.word){
            key = ++key % hash.size;
        }
        hash.table[key] = word;
    }
}

Node get(Hash_Table hash, int key){
    return hash.table[key]
}

double get_load_factor(Hash_Table hash){
    return (double) hash.itms / self.size;
}
