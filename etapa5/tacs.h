#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2
#define TAC_SUB 3
#define TAC_MULT 4
#define TAC_DIV 5
#define TAC_MINOR 6
#define TAC_BIGGER 7
#define TAC_OR 8
#define TAC_AND 9
#define TAC_NOT 10
#define TAC_DOLLAR 11
#define TAC_TAG 12
#define TAC_LE 13
#define TAC_GE 14
#define TAC_EQ 15
#define TAC_DIF 16


#define TAC_COPY 17
#define TAC_JFALSE 18
#define TAC_LABEL 19
#define TAC_IFZ 31
#define TAC_JUMP 32

#define TAC_LEFT 20
#define TAC_RIGHT 21
#define TAC_VEC_COPY 22
#define TAC_ELEM_COPY 23
#define TAC_FUNCT 24
#define TAC_BEGIN_FUNCTION 25
#define TAC_END_FUNCTION 30
#define TAC_CALL 33
#define TAC_ARG 34
#define TAC_LEFT_VEC 35
#define TAC_RIGHT_VEC 36

#define TAC_READ 26
#define TAC_PRINT 27
#define TAC_RETURN 28


typedef struct tac_node{
int type; 
HASH_NODE* res; 
HASH_NODE* op1; 
HASH_NODE* op2; 
struct tac_node*prev;
struct tac_node* next;
}TAC;

TAC* tacCreate (int type, HASH_NODE*res, HASH_NODE*op1, HASH_NODE*op2); 
void tacPrint (TAC*tac); 
void tacPrintBackwards (TAC*tac);
TAC* tacJoin (TAC *l1, TAC*l2); 

// CODE GENERATION 

TAC* generateCode(AST*node);
#endif