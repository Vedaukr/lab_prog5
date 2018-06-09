#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct Cell {
    int prefix;
    int last;
} Cell;

Cell ** init(void);

int searchDict(Cell ** dict, int prefix, int last);
int prefixDict(Cell ** dict, int number);
int lastDict(Cell ** dict, int number);
void add(Cell ** dict, int bit, int prefix, int current);
void freeDict(Cell ** dict);