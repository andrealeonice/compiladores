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
    int son_type=0;
    AST*newnode;
    if (node->son[1]){
     // TESTE DE INICIALIZAÇÃO DE VETORES NÃO RECONHECE MAIS DE UMA ENTRADA
        if(node-> symbol-> type == SYMBOL_VECTOR)
            {   
              
        
            if ( node->son[1]->symbol->type != SYMBOL_LITINT && node->son[1]->symbol->type != SYMBOL_LITCHAR)
            {
            fprintf(stderr, "Semantic ERROR: Wrong vector index definition\n");    
             ++SemanticErrors;
            }
            if (node->son[2])
            if (node->son[2]->type == AST_VECT_VL)
            {
            newnode  = node->son[2];
            if (newnode->son[0])
            son_type = newnode->son[0]->symbol->type;
            else 
            son_type = 0;  
            }

         }
         
        else
        {
        son_type = node->son[1]->symbol->type;
        }

        if (son_type!=0)
        switch (node->symbol->datatype)
        { //    COMPATIBILIDADE ENTRE CHAR E INT?
            case DATATYPE_CHAR:  
            if (son_type != SYMBOL_LITCHAR)
        {
            fprintf(stderr, "Semantic ERROR: Wrong CHAR definition \n");    
             ++SemanticErrors;
        }
             break; 
        
            case DATATYPE_BOOL:  
            if (son_type != SYMBOL_BOOL)
        {
            fprintf(stderr, "Semantic ERROR: Wrong BOOL definition \n");  
             ++SemanticErrors;
        }
             break; 

            case DATATYPE_POINTER:  
            if (son_type != SYMBOL_LITCHAR && node->son[1]->symbol->type != SYMBOL_BOOL && node->son[1]->symbol->type != SYMBOL_LITINT)
        {
            fprintf(stderr, "Semantic ERROR: Wrong POINTER definition \n");    
             ++SemanticErrors;
        }
             break; 
            case DATATYPE_INT:  
            if (son_type != SYMBOL_LITINT)
        {
            fprintf(stderr, "Semantic ERROR: Wrong INTEGER definition \n");    
             ++SemanticErrors;
        }
             break; 
        
        }
       
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

int isBoolean (AST*son)
{


        if (son->type == AST_MINOR || 
            son->type == AST_BIGGER || 
            son->type == AST_OR || 
            son->type == AST_GE ||
            son->type == AST_AND ||
            son->type == AST_LE ||
            son->type == AST_EQ ||
            son->type == AST_DIF ||
             (son->type == AST_SYMBOL &&  
            ((son->symbol->type == SYMBOL_BOOL) ||
            (son->symbol->type == SYMBOL_VARIABLE &&
                son->symbol->datatype == DATATYPE_BOOL))) ||
                (son->type == AST_CALL_FUNCT && son->symbol->datatype == DATATYPE_BOOL))
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
 
        case AST_SUB:
        case AST_MULT:
        case AST_DIV:
        case AST_ADD:    
        case AST_MINOR:
        case AST_BIGGER:
        case AST_LE:
        case AST_GE:

         if (! is_number (node->son[0]))
         {
            fprintf(stderr, "Semantic ERROR: invalid left operands \n");
            ++SemanticErrors;
         }
          if (! is_number (node->son[1]))
         {
            fprintf(stderr, "Semantic ERROR: invalid rigth operands \n");
            ++SemanticErrors;
         }
        break; 
        
  
        case AST_OR:
        case AST_AND:
         if (! isBoolean (node->son[0]))
         {
            fprintf(stderr, "Semantic ERROR: invalid left operands\n");
            ++SemanticErrors;
         }
          if (! isBoolean (node->son[1]))
         {
            fprintf(stderr, "Semantic ERROR: invalid rigth operands \n");
            ++SemanticErrors;
         }
			
        break; 

        case AST_EQ:
        case AST_DIF:
        if (is_number(node->son[0]) && isBoolean(node->son[1]) ||( is_number(node->son[1]) && isBoolean(node->son[0])))
        {
        fprintf(stderr, "Semantic ERROR: Incompatible type left operand \n");
        ++SemanticErrors;
        }
        break;

        case AST_NOT: 
        if(!isBoolean(node->son[0])) 
        {
				
				printf("Semantic Error: invalid operand for boolean operator.\n");
				SemanticErrors++;
        }
        break; 
               

    }
    for (i=0; i<MAX_SONS; ++i)
   check_operands(node->son[i]);
}

void check_commands (AST*node)
{
int i; 

if (node == 0)
return; 
AST*newnode; 
switch (node->type)
{
    case AST_IF:
    case AST_IF_ELSE:
    case AST_WHILE:
    if (! isBoolean (node->son[0]))
    {
        fprintf (stderr, "Semantic ERROR: It's not a boolean condition\n");
        ++SemanticErrors;
    }
    break;
 
 
   case AST_LEFT_ASSGN: 
   case  AST_RIGHT_ASSGN: 
   //FALTA ASSINGMNT DO PONTEIRO
    if (node->symbol->datatype == DATATYPE_POINTER)
    {
        if (node->son[0]->type == AST_DOLLAR)
        {           
            newnode= node->son[0]; 
            if (newnode->son[0])
            if (newnode->son[0]->symbol->type != SYMBOL_VARIABLE)
             {
                 fprintf (stderr,"Semantic ERROR: Wrong pointer attribution\n");
                 ++SemanticErrors;
             }            
        
        }
        else 
         if (node->son[0]->type == AST_TAG)
        {   
            newnode= node->son[0]; 

            if (newnode->son[0])
            if (newnode->son[0]->symbol->datatype != DATATYPE_INT && newnode->son[0]->symbol->datatype != DATATYPE_CHAR && newnode->son[0]->symbol->type != SYMBOL_LITINT && newnode->son[0]->symbol->type != SYMBOL_LITCHAR)
             {
                 fprintf (stderr,"Semantic ERROR: Wrong pointer attribution\n");
                 ++SemanticErrors;
             }            
        
        }
    }
    else
   if (!((node->symbol->datatype == DATATYPE_INT || node->symbol->type == DATATYPE_CHAR) && is_number(node->son[0])) && !(node->symbol->datatype == DATATYPE_BOOL  && isBoolean(node->son[0])))
    {
        fprintf (stderr, "Semantic ERROR: WRONG ASSGINMENT\n");
        ++SemanticErrors;
    } 
   break;

}

for (i=0; i< MAX_SONS; ++i)
{
    check_commands(node->son[i]);
}

}

void check_undeclared()
{
   SemanticErrors += hash_check_undeclared();
}