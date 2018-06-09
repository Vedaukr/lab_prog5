#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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

List* newListSL(){
    List * list = (List *)malloc(sizeof(List));
    list->head = NULL;
    list->length = 0;
    return list;
}

Node * newNodeSL(int number, int prefix, int last){
    Node* node = malloc(sizeof(Node));
    node->number = number;
    node->prefix = prefix;
    node->last = last;
    node->next = NULL;
    return node;
}

void addFirstSL(List* list, Node* node){
    node->next = list->head;
    list->head = node;
    list->length++;
}

void addEndSL(List* list, Node* node){
    if(list->head == NULL){
        list->head = node;
        list->length++;
        return;
    }
    Node* cur = list->head;
    while(cur->next != NULL) cur = cur->next;
    cur->next = node;
    list->length++;
}

Node* deleteNodeSL(List* list, int index){
    
    assert(index >= 0);
    
    Node* cur = list->head;
    if(cur == NULL) return NULL;

    if(index == 0){
        list->head = list->head->next;
        list->length--;
        return cur;
    }

    int i = 0;
    while(i < index - 1){
        i++;
        if(cur->next != NULL) cur = cur->next;
        else return NULL;
    }
    
    if(cur->next == NULL) return NULL;

    Node* deleted = cur->next;
    cur->next = deleted->next;
    list->length--; 
    return deleted;

}

void insertNodeSL(List* list, Node* node, int index){
    
    assert(index >= 0);
    if(index > list->length) return;

    int i = 0;

    if(index == 0){
        addFirstSL(list, node);
        return;
    }
    if(index == list->length){
        addEndSL(list, node);
        return;
    }


    Node* cur = list->head;
    while(i < index - 1){
        i++;
        if(cur->next != NULL) cur = cur->next;
        else return;
    }

    node->next = cur->next;
    cur->next = node;
    list->length++;

}

void printListSL(List* list , FILE* out){
    Node* cur = list->head;
    while(cur != NULL){
        fprintf(out, "%i: %c \n", cur->number, cur->last);
        cur = cur->next;
    }
}

void freeNodeSL(Node* node){
    free(node);
}

void freeListSL(List* list){
    if(list == NULL) return;
    
    Node* cur = list->head;
    if(cur == NULL){
        free(list);
        return;
    }
    
    Node* next = cur->next;
    
    while(next != NULL){
        freeNodeSL(cur);
        cur = next;
        next = next->next;
    }
    
    freeNodeSL(cur);
    free(list);
}

void initList(List * list){
    int i = 0;
    while(i < 256){
        addEndSL(list, newNodeSL(i, -1, i));
        i++;
    }
}

int searchList(List * list, int prefix, int last){
    Node * cur = list->head;
    while(cur != NULL){
        if(cur->last == last && cur->prefix == prefix) return cur->number;
        cur = cur->next;
    }
    return -1;
}

int prefixList(List * list, int number){
    Node * cur = list->head;
    while(cur != NULL){
        if(cur->number == number) return cur->prefix;
        cur = cur->next;
    }
    return -1;
}

int lastList(List * list, int number){
    Node * cur = list->head;
    while(cur != NULL){
        if(cur->number == number) return cur->last;
        cur = cur->next;
    }
    return -1;
}

