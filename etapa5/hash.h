
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifndef HASH_HEADER
#define HASH_HEADER

#define HASH_SIZE 997
#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LITINT 2
#define SYMBOL_STRING 3
#define SYMBOL_BOOL 4
#define SYMBOL_LITCHAR 5
#define SYMBOL_POINTER 6
#define SYMBOL_VARIABLE 7
#define SYMBOL_FUNCTION 8
#define SYMBOL_VECTOR 9
#define SYMBOL_LABEL 10

#define DATATYPE_INT 1
#define DATATYPE_BOOL 2
#define DATATYPE_CHAR 3
#define DATATYPE_POINTER 4

typedef struct hash_node{
    int type;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE *hashFind(char *text);
HASH_NODE *hashInsert(char *text, int type);
void hashPrint(void);
HASH_NODE* makeTemp();
HASH_NODE* makeLabel();
#endif