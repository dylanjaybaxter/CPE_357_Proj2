#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

Hash_Table* hash_init(){
    Hash_Table* hash = (Hash_Table*)malloc(sizeof(Hash_Table));
    hash->size = ISIZE;
    Node *table = (Node*)malloc(hash->size * sizeof(Node));
    int i;
    for (i = 0; i < hash->size; i++){
        table[i].word = NULL;
        table[i].freq = 0;
    }
    hash->items = 0;
    return hash;
}

int genHash(char * word, Hash_Table *table){
    int len = strlen(word);
    int i;
    int hash_value = 0;
    int p = 53;
    int p_pow = 1;
    for (i = 0; i < len; i++){
        hash_value += (word[i] * (p_pow)) % table->size;
        p_pow = (p_pow * p) % table->size;
    }
    return hash_value;
}

void rehash(Hash_Table *hash){
    hash->size *= 2;
    Hash_Table *temp = hash_init();
    temp->size = hash->size;
    int i;
    for (i = 0; i < hash->size; i++){
        if (hash->table[i].word != NULL){
            insert(temp, hash->table[i].word, hash->table[i].freq);
        }
    }

}

void insert(Hash_Table *hash, char * key, int val){
    int load = get_load_factor(hash);
    if (load > 0.5){
        rehash(hash);
    }
    int hash_val = genHash(key, hash);
    while (hash->table[hash_val].word != NULL
        && hash->table[hash_val].word != key){
        hash_val++;
        hash_val = hash_val % hash->size;
    }
    hash->table[hash_val].word = key;
    hash->table[hash_val].freq = val;
    hash->items++;
}

Node get(Hash_Table *hash, char * key){
    int hash_val = genHash(key, hash);
    int count = 0;
    while (hash->table[hash_val].word != NULL
        && hash->table[hash_val].word != key
        && count != hash->size){
        hash_val++;
        hash_val = hash_val % hash->size;
    }
    return hash->table[hash_val];
}

double get_load_factor(Hash_Table hash){
    return (double) hash.items / hash.size;
}

Node popMax(Hash_Table *hash){
    Node max;
    max.freq = 0;
    max.word = '\0';
    int i;
    for (i = 0; i < hash->size; i++){
        if (hash->table[i].word != NULL){
            if (hash->table[i].freq == max.freq){
                int cmp = strcmp(hash->table[i].word, max.word);
                if (cmp > 0){
                    max = hash->table[i];
                }
            }
            else if (hash->table[i].freq > max.freq){
                max = hash->table[i];
            }
        }
    }
    Node out;
    out.freq = max.freq;
    out.word = max.word;
    hash->table[i].word = NULL;
    hash->table[i].freq = 0;
    return out;
}

void remove_node(int ind, Hash_Table *hash){
    free(hash->table[ind].word);
    hash->table[ind].word = NULL;
    hash->table[ind].freq = 0;
}

void deconstruct(Hash_Table *hash){
    int i;
    for (i = 0; i < hash->size; i++){
        if (hash->table[i].word != NULL){
            remove_node(i, hash);
        }
    }
    free(hash->table);
}
