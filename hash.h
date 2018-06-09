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



void freeCells(List ** cells, int capacity);

void freeDictionary(Dictionary * dict);

Dictionary * newDictionary (int capacity);
int hashFunction(Node * node);
void addDict(Dictionary * dict, Node * node);

void initDict(Dictionary * dict);

int dictSearch(Dictionary * dict, int prefix, int current);
