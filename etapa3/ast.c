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
        default: fprintf(stderr, "AST_UNKOWN");  break;
    }
    
    if (node-> symbol)
        fprintf (stderr, ",%s\n", node->symbol->text);
        else
        fprintf(stderr,",0\n"); 
    for (i=0; i<MAX_SONS; ++i)
    astPrint(node-> son[i], level+1); 

}