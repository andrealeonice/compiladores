#include "semantic.h"
int SemanticErrors = 0;

void check_and_set_declarations(AST*node)
{
    int i;
    if (node==0)
    return; 
 
    switch (node->type)
    {
       
        case AST_DEC_VAR: 
        if (node->symbol)
        {    
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
        node->symbol->type =  SYMBOL_VARIABLE; 
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_INT)
        node->symbol->datatype =  DATATYPE_INT;
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_BOOL)
        node->symbol->datatype =  DATATYPE_BOOL;
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_CHAR)
        node->symbol->datatype =  DATATYPE_CHAR;
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_POINTER)
        node->symbol->datatype =  DATATYPE_POINTER;
        }
        break;

        case AST_DEC_VECTOR:
        if (node->symbol)
        {    
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic ERROR: funcition %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
        node->symbol->type =  SYMBOL_FUNCTION; 
        }
        break;

        case AST_DEC_FUNCT:
        if (node->symbol)
        {
            if (node->symbol->type != SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic ERROR: vector %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
        node->symbol->type =  SYMBOL_VECTOR ; 
                if (node->son[0])
        if (node->son[0]-> type  == AST_KW_INT)
        node->symbol->datatype =  DATATYPE_INT;
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_BOOL)
        node->symbol->datatype =  DATATYPE_BOOL;
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_CHAR)
        node->symbol->datatype =  DATATYPE_CHAR;
        if (node->son[0])
        if (node->son[0]-> type  == AST_KW_POINTER)
        node->symbol->datatype =  DATATYPE_POINTER;
        }
        break; 
    }
   
    for (i=0; i<MAX_SONS; ++i)
   check_and_set_declarations(node->son[i]);

}

int is_number (AST*son)
{

           if (son->type == AST_ADD || 
            son->type == AST_SUB || 
            son->type == AST_DIV || 
            son->type == AST_MULT || 
            (son->type == AST_SYMBOL &&  
            ((son->symbol->type == SYMBOL_LITINT) ||
            (son->symbol->type == SYMBOL_VARIABLE &&
                son->symbol->datatype == DATATYPE_INT))) ||
                (son->type == AST_CALL_FUNCT && son->symbol->datatype == DATATYPE_INT))
        return 1; 
        else 
        return 0;

}
void check_operands(AST*node)
{
    int i; 
    if (node==0)
    return; 
 
    switch (node->type)
    {
       
        case AST_ADD: 
         if (! is_number (node->son[0]))
         {
            fprintf(stderr, "Semantic ERROR: invalid left operands for ADD\n");
            ++SemanticErrors;
         }
          if (! is_number (node->son[1]))
         {
            fprintf(stderr, "Semantic ERROR: invalid rigth operands for ADD\n");
            ++SemanticErrors;
         }
        break; 

    }
    for (i=0; i<MAX_SONS; ++i)
   check_operands(node->son[i]);
}


void check_undeclared()
{
   SemanticErrors += hash_check_undeclared();
}