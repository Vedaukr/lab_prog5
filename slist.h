#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    int number;
    int prefix;
    int last;
    struct Node *next;
} Node;

typedef struct List {
    Node * head;
    size_t length;
} List;

void addFirstSL(List* list, Node* node);
void addEndSL(List* list, Node* node);

Node * newNodeSL(int number, int prefix, int last);
List* newListSL();

Node* deleteNodeSL(List* list, int index);
void insertNodeSL(List* list, Node* node, int index);

void freeListSL(List* list);
void freeNodeSL(Node* node);

void printListSL(List* list, FILE * out);
void initList(List * list);

int searchList(List * list, int prefix, int last);
int prefixList(List * list, int number);
int lastList(List * list, int number);
