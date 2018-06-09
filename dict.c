#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int size = 0;

typedef struct Cell {
    int prefix;
    int last;
} Cell;

Cell ** init(){
    Cell ** dict = malloc(4096*sizeof(Cell *));
    for(int i = 0; i < 4096; i++) dict[i] = malloc(sizeof(Cell));
    for(int i = 0; i < 256; i++){
        dict[i]->prefix = -1;
        dict[i]->last = i;
    }
    size = 256;
    return dict;
}

int searchDict(Cell ** dict, int prefix, int last){
    for(int i = 0; i < 4096; i++){
        if(dict[i]->prefix == prefix && dict[i]->last == last) return i;
    }
    return -1;
}

int prefixDict(Cell ** dict, int number){
    if(number >= size) return -1;
    else return dict[number]->prefix;
}

int lastDict(Cell ** dict, int number){
    if(number >= size) return -1;
    else return dict[number]->last;
}

void add(Cell ** dict, int bit, int prefix, int current){
    dict[bit]->prefix = prefix;
    dict[bit]->last = current;
    size++;
}

void freeDict(Cell ** dict){
    for(int i = 0; i < 4096; i++) free(dict[i]);
    free(dict); 
}