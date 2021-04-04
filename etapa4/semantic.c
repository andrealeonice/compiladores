#include "semantic.h"
int SemanticErrors = 0;

void check_and_set_declarations(AST*node)
{
    int i;
    if (node==0)
    return; 
    if (node->symbol)
        {    
         if (node->symbol->type != SYMBOL_IDENTIFIER && 
            (node->type == AST_DEC_VAR || node->type == AST_DEC_VECTOR || node->type == AST_DEC_FUNCT))
            {
                fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
                ++SemanticErrors;
            }
    switch (node->type)
    {
        case AST_DEC_VAR: 
        node->symbol->type =  SYMBOL_VARIABLE; 
        verify (node); 
        break;

        case AST_DEC_VECTOR:
        node->symbol->type =  SYMBOL_VECTOR; 
        verify(node);
        break;

        case AST_DEC_FUNCT:
        node->symbol->type =  SYMBOL_FUNCTION ;
       verify (node);   
        break; 
    }
 }
    for (i=0; i<MAX_SONS; ++i)
   check_and_set_declarations(node->son[i]);

}

void verify(AST*node)
{       
    if (node->son[0])
        switch (node->son[0]-> type ) {
        case AST_KW_INT:
        node->symbol->datatype =  DATATYPE_INT;
        break;
        case AST_KW_BOOL:
        node->symbol->datatype =  DATATYPE_BOOL;
        break;
        case AST_KW_CHAR: 
        node->symbol->datatype =  DATATYPE_CHAR;
        break;
        case AST_KW_POINTER:
        node->symbol->datatype =  DATATYPE_POINTER;
        break;
        }
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
         if  ((son->type == AST_SYMBOL &&  
            ((son->symbol->type == SYMBOL_LITCHAR) ||
            (son->symbol->type == SYMBOL_VARIABLE &&
                son->symbol->datatype == DATATYPE_CHAR))) ||
                (son->type == AST_CALL_FUNCT && son->symbol->datatype == DATATYPE_CHAR))
        return 1; 
        else 
        return 0;

}

int isBoolean (AST*node)
{
    switch (node-> type)
    {
        case AST_MINOR:
        case AST_BIGGER:
        case AST_OR:
        case AST_AND:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
            return 1;
            break; 
        case AST_SYMBOL: 
        if (node->symbol->type == SYMBOL_TRUE || node->symbol->type == SYMBOL_FALSE)
         return 1; 
        
        if ((node->symbol->type == SYMBOL_VARIABLE ||node->symbol->type == SYMBOL_FUNCTION || node->symbol->type ==SYMBOL_VECTOR)
        && node->symbol->datatype == DATATYPE_BOOL)
        return 1; 
        
    }
}


void check_operands(AST*node)
{
    int i; 
    if (node==0)
    return; 
 
    switch (node->type)
    {
       
        case AST_SUB:
        case AST_MULT:
        case AST_DIV:
        case AST_ADD: 
        case AST_MINOR:
        case AST_BIGGER:
        case AST_OR:
        case AST_AND:
        case AST_LE:
        case AST_GE:
        case AST_EQ:
        case AST_DIF:
         if (! is_number (node->son[0]))
         {
            fprintf(stderr, "Semantic ERROR: invalid left operands\n");
            ++SemanticErrors;
         }
          if (! is_number (node->son[1]))
         {
            fprintf(stderr, "Semantic ERROR: invalid rigth operands \n");
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