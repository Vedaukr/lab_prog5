#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "slist.h"
#include <math.h>
#include <assert.h>


typedef struct Dictionary Dictionary;

struct Dictionary{
    int size;
    int capacity;
    List ** cells;
};



void freeCells(List ** cells, int capacity){
    for(int i = 0; i < capacity; i++){
        if(cells[i]) freeListSL(cells[i]); 
    }
}

void freeDictionary(Dictionary * dict){
    freeCells(dict->cells, dict->capacity);
    free(dict->cells);
    free(dict);
}


Dictionary * newDictionary (int capacity){
    assert(capacity > 0);
    Dictionary * dict = malloc(sizeof(Dictionary));
    dict->capacity = capacity;
    dict->size = 0;
    dict->cells = malloc(capacity*sizeof(List *));
    for(int i = 0; i < capacity; i++) dict->cells[i] = NULL;
    return dict;
}

int hashFunction(Node * node){
    return (2003 * node->last * node->prefix + 2048) % 2048;
}

void addDict(Dictionary * dict, Node * node){
    int index = hashFunction(node);
    if(index < 0) index += 2048;
    if(dict->cells[index]) addFirstSL(dict->cells[index], node);
    else{
        dict->cells[index] = newListSL();
        addFirstSL(dict->cells[index], node);
    }
    dict->size++;
}

void initDict(Dictionary * dict){
    for(int i = 0; i < 256; i++){
        addDict(dict, newNodeSL(i, -1, i));
    }
    dict->size = 256;
}

int dictSearch(Dictionary * dict, int prefix, int current){
    Node * node = newNodeSL(0, prefix, current);
    int index = hashFunction(node);
    free(node);
    if(dict->cells[index] != NULL){
        Node * temp = dict->cells[index]->head;
        while(temp != NULL){
            if(temp->last == current && temp->prefix == prefix) return temp->number;
            temp = temp->next;
        }
    }
    return -1;
}

