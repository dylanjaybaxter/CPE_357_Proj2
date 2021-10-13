
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "hash.h"

Hash_Table* hash_init(){
    /* Initializes the hash table with NULL words and 0 frequencies */
    Hash_Table* hash = (Hash_Table*)malloc(sizeof(Hash_Table));
    hash->size = ISIZE;
    Node *table = (Node*)malloc(hash->size * sizeof(Node));
    int i;
    for (i = 0; i < hash->size; i++){
        table[i].word = NULL;
        table[i].freq = 0;
    }
    hash->items = 0;
    hash->table = table;
    return hash;
}

int genHash(char * word, Hash_Table *table){
    /* Generates the hash value from the given key */
    int len = strlen(word);
    int i;
    int hash_value = 0;
    int p = 53;
    int p_pow = 1;
    for (i = 0; i < len; i++){
        hash_value += ((word[i] * (p_pow))) % (table->size);
        p_pow = (p_pow * p) % (table->size);
    }
    return abs(hash_value % (table->size));
}

void rehash(Hash_Table *hash){
    /* Recreates the hash table with a larger size
     * As well as reinserting the nodes with updated hash values */
    int oldSize = hash->size;
    int newSize = hash->size * 2;
    Node* oldTable = hash->table;
    hash->table = (Node*)malloc(newSize * sizeof(Node));
    if(!(hash->table)){
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int i;
    for (i = 0; i < hash->size; i++){
        hash->table[i].word = NULL;
        hash->table[i].freq = 0;
    }
    hash->size = newSize;
    hash->items = 0;
    for (i = 0; i < oldSize; i++){
        if (oldTable[i].word != NULL){
            insert(hash, oldTable[i].word, oldTable[i].freq);
        }
    }
    free(oldTable);
}

void insert(Hash_Table *hash, char * key, int val){
    /* Inserts the given key and value into the repective value
     * of its hash. Checks the load factor and if its too low the hash table
     * is rehashed. If it runs into a collision linear probing
     * is used to prevent the collision. */
    double load = get_load_factor(hash);
    if (load > 0.5){
        rehash(hash);
    }
    int hash_val = genHash(key, hash);
    while (hash->table[hash_val].word != NULL
        && strcmp(hash->table[hash_val].word, key)!=0){
        hash_val++;
        hash_val = hash_val % hash->size;
    }
    if(hash->table[hash_val].word == NULL){
        hash->items++;
    }
    hash->table[hash_val].word = key;
    hash->table[hash_val].freq = val;
}

Node get(Hash_Table *hash, char * key){
    /* Returns the node from the hash table from the given key */
    int hash_val = genHash(key, hash);
    int count = 0;
    while (hash->table[hash_val].word != NULL
        && strcmp(hash->table[hash_val].word, key) != 0
        && count < hash->size){
        hash_val++;
        hash_val = hash_val % hash->size;
        count++;
    }
    if(count != hash->size){
        return hash->table[hash_val];
    }
    else{
        Node bad;
        bad.word = NULL;
        bad.freq = 0;
        return bad;
    }
}

double get_load_factor(Hash_Table *hash){
    /* Returns the load factor of the hash table
     * This is used for the insert method */
    return (double) hash->items / hash->size;
}

Node popMax(Hash_Table *hash){
    /* Pop outs the node that contains the highest freq */
    Node max;
    max.freq = 0;
    max.word = NULL;
    int i;
    int ind = -1;
    if(hash->items > 0){
        for (i = 0; i < hash->size; i++){
            if (hash->table[i].word != NULL){
                if (hash->table[i].freq == max.freq){
                    int cmp = strcmp(hash->table[i].word, max.word);
                    if (cmp > 0){
                        max = hash->table[i];
                        ind = i;
                    }
                }
                else if (hash->table[i].freq > max.freq){
                    max = hash->table[i];
                    ind = i;
                }
            }
        }
    }
    if(ind != -1){
        hash->table[ind].word = NULL;
        hash->table[ind].freq = 0;
    }
    return max;
}

void remove_node(int ind, Hash_Table *hash){
    /* Removes a node at the given index from the hash table.
     * While also freeing the data within the previous node */
    free(hash->table[ind].word);
    hash->table[ind].word = NULL;
    hash->table[ind].freq = 0;
}

void deconstruct(Hash_Table *hash){
    /* Deconstructs the hash table, freeing all of its data */
    int i = 0;
    for (i = 0; i < hash->size; i++){
        if (hash->table[i].word != NULL){
            remove_node(i, hash);
        }
    }
    free(hash->table);
    free(hash);
}

int get_num_items(Hash_Table *hash){
    /* Returns the number of items from the given hash table */
    int items = 0;
    int i;
    for (i = 0; i < hash->size; i++){
        if(hash->table[i].word != NULL){
            items++;
        }
    }
    return items;
}
