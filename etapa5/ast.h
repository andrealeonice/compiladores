// AST - Abstract Syntax Tree
#include <stdio.h>
#include "hash.h"


#ifndef AST_HEADER
#define AST_HEADER


#define MAX_SONS 4
#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_MULT 4
#define AST_DIV 5
#define AST_MINOR 6
#define AST_BIGGER 7
#define AST_OR 8
#define AST_AND 9
#define AST_NOT 10
#define AST_DOLLAR 11
#define AST_TAG 12
#define AST_LE 13
#define AST_GE 14
#define AST_EQ 15
#define AST_DIF 16
#define AST_VECTOR 17
#define AST_PARAMETER 18
#define AST_KW_INT 19
#define AST_KW_BOOL 20
#define AST_KW_CHAR 21
#define AST_KW_POINTER 22
#define AST_VECT_VL 23
#define AST_LCMMD 24
#define AST_STRING 25
#define AST_READ 26
#define AST_PRINT 27
#define AST_RETURN 28
#define AST_IF 29
#define AST_IF_ELSE 30
#define AST_WHILE 31
#define AST_RIGHT_ASSGN 32
#define AST_LEFT_ASSGN 33
#define AST_LEFT_ASSGN_V 34
#define AST_RIGHT_ASSGN_V 35
#define AST_LPRNT 36
#define AST_LARG 37
#define AST_CALL_FUNCT  38
#define AST_LIT_DEF 39
#define AST_DEC_FUNCT 40
#define AST_DEC_VECTOR 41
#define AST_DEC_VAR 42
#define AST_DECL 43
#define AST_BODY 44
#define AST_PARENT 45

typedef struct astnode
{
    int type; 
    HASH_NODE *symbol;
    struct astnode * son[MAX_SONS];

} AST;

AST *astCreate(int type, HASH_NODE *symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST *node, int level);


#endif