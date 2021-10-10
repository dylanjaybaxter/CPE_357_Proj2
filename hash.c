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
        hash_value += (word[i] * (p_pow)) % *table.size;
        p_pow = (p_pow * p) % *table.size;
    }
    return hash_value;
}

void rehash(Hash_Table *hash){
    *hash.size *= 2;
    Hash_Table *temp = hash_init();
    *temp.size = *hash.size;
    int i;
    for (i = 0; i < *hash.size; i++){
        if (*hash.table[i] != NULL){
            insert(temp, *hash.table[i].word, *hash.table[i]);
        }
    }
       
}

Hash_Table* hash_init(){
    Hash_Table hash;
    *hash.size = ISIZE;
    Node *table = malloc(*hash.size * sizeof(Node));
    int i;
    for (i = 0; i < size; i++){
        table[i] = NULL;
    }
    *hash.items = 0; 
}  

void insert(Hash_Table *hash, char * key, int val){
    int load = get_load_factor(hash);
    if (load > 0.5){
        rehash(hash);
    }
    int hash_val = hash(key, hash);
    while (*hash.table[hash_val] != NULL && *hash.table[hash].word != key){
        hash_val = ++hash_val % *hash.size;
    }
    *hash.table[hash_val].word = key;
    *hash.table[hash_val].freq = val;
    *hash.item++;
}

Node get(Hash_Table *hash, char * key){
    int hash_val = hash(key, hash);
    int count = 0;
    while (*hash.table[hash_val] != NULL && *hash.table[hash].word != key
            && count != *hash.size){
        hash_val = ++hash_val % *hash.size;
    }
    return *hash.table[hash_value]
}

double get_load_factor(Hash_Table hash){
    return (double) hash.items / hash.size;
}

Node popMax(Hash_Table *hash){
    Node max;
    max.freq = 0;
    max.word = "";
    int i;
    for (i = 0; i < *hash.size; i++){
        if (*hash.table[i] != NULL && *hash.table[i].freq > max.freq){
            max = hash.table[i];
        }
        remove_node(i, hash);
        return max;
    }
}

void remove_node(int ind, Hash_Table *hash){
    free(*hash.table[ind].word);
    *hash.table[ind] = NULL;
}

