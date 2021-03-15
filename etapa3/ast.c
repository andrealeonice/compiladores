#include <stdio.h>
#include <stdlib.h>
#include "ast.h"


AST *astCreate(int type, HASH_NODE *symbol, AST *s0, AST *s1, AST *s2, AST *s3)

{
    AST*newnode; 
    newnode = (AST*) calloc(1, sizeof(AST)); 
    newnode-> type = type; 
    newnode -> son[0]= s0; 
    newnode -> son[1]= s1; 
    newnode -> son[2]= s2; 
    newnode -> son[3]= s3; 
    newnode -> symbol = symbol; 
    return newnode; 
}

void astPrint(AST *node, int level)
{
    int i=0;
    if (!node)
    return;
    for (i=0; i<level; ++i)
    fprintf(stderr, "  ");

    fprintf(stderr, "AST("); 
    switch (node->type)
    {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL"); break;
        case AST_ADD: fprintf(stderr, "AST_ADD"); break;
        case AST_SUB: fprintf(stderr, "AST_SUB"); break;
        case AST_MULT: fprintf(stderr, "AST_MULT"); break;
        case AST_DIV: fprintf(stderr, "AST_DIV"); break;
        case AST_MINOR: fprintf(stderr, "AST_MINOR"); break;
        case AST_BIGGER: fprintf(stderr, "AST_BIGGER"); break;
        case AST_OR: fprintf(stderr, "AST_OR"); break;
        case AST_NOT: fprintf(stderr, "AST_NOT"); break;
        case AST_DOLLAR: fprintf(stderr, "AST_DOLLAR"); break;
        case AST_TAG: fprintf(stderr, "AST_TAG"); break;
        case AST_LE: fprintf(stderr, "AST_LE"); break;
        case AST_GE: fprintf(stderr, "AST_GE"); break;
        case AST_EQ: fprintf(stderr, "AST_EQ"); break;
        case AST_DIF: fprintf(stderr, "AST_DIF"); break;
        case AST_VECTOR: fprintf(stderr, "AST_VECTOR"); break;
        case AST_PARAMETER: fprintf(stderr, "AST_PARAMETER"); break;
        case AST_KW_INT: fprintf(stderr, "AST_KW_INT"); break;
        case AST_KW_BOOL: fprintf(stderr, "AST_KW_BOOL"); break;
        case AST_KW_CHAR: fprintf(stderr, "AST_KW_CHAR"); break;
        case AST_KW_POINTER: fprintf(stderr, "AST_KW_POINTER"); break;
        case AST_VECT_VL: fprintf(stderr, "AST_VECT_VL"); break;
        case AST_LCMMD: fprintf(stderr, "AST_LCMMD"); break;
        case AST_ASSGN: fprintf(stderr, "AST_ASSGN"); break;
        case AST_READ: fprintf(stderr, "AST_READ"); break;
        case AST_PRINT: fprintf(stderr, "AST_PRINT"); break;
        case AST_RETURN: fprintf(stderr, "AST_RETURN"); break;
        case AST_IF: fprintf(stderr, "AST_IF"); break;
        case AST_WHILE: fprintf(stderr, "AST_WHILE"); break;
        case AST_IF_ELSE: fprintf(stderr, "AST_IF_ELSE"); break;
        case AST_RIGHT_ASSGN: fprintf(stderr, "AST_RIGHT_ASSGN"); break;
        case AST_LEFT_ASSGN: fprintf(stderr, "AST_LEFT_ASSGN"); break;
        case AST_LEFT_ASSGN_V: fprintf(stderr, "AST_LEFT_ASSGN_V"); break;
        case AST_RIGHT_ASSGN_V: fprintf(stderr, "AST_RIGHT_ASSGN_V"); break;
        case AST_LPRNT: fprintf(stderr, "AST_LPRNT"); break;
        case AST_LARG: fprintf(stderr, "AST_LARG"); break;
        case AST_CALL_FUNCT: fprintf(stderr, "AST_CALL_FUNCT"); break;
        case AST_LIT_DEF: fprintf(stderr, "AST_LIT_DEF"); break;
        case AST_DEC_FUNCT: fprintf(stderr, "AST_DEC_FUNCT"); break;
        case AST_DEC_VECTOR: fprintf(stderr, "AST_DEC_VECTOR"); break;
        case AST_DEC_VAR: fprintf(stderr, "AST_DEC_VAR"); break;
        case AST_DECL: fprintf(stderr, "AST_DECL"); break;
        default: fprintf(stderr, "AST_UNKOWN");  break;
    }
    
    if (node-> symbol)
        fprintf (stderr, ",%s\n", node->symbol->text);
        else
        fprintf(stderr,",0\n"); 
    for (i=0; i<MAX_SONS; ++i)
    astPrint(node-> son[i], level+1); 

}