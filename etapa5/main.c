#include <stdio.h>
#include "ast.h"
#include "hash.h"
extern FILE *yyin; 
extern AST *finalAST;
int yyparse();
int initMe();

void decompile ( AST *node, FILE *out)
{
    if (!node)
    {
        return;
    }

    switch (node -> type)
    {
        case AST_SYMBOL: 
            fprintf(out, "%s", node->symbol->text); 
            if (node->son[0]!=0)
            {
            fprintf(out," : "); 
            decompile(node->son[0], out); 
            }
            break;
        case AST_ADD: 
            decompile(node->son[0],out);
            fprintf(out, " + "); 
            decompile(node->son[1],out);
            break;
        case AST_SUB: 
            decompile(node->son[0],out);
            fprintf(out, " - "); 
            decompile(node->son[1],out);
            break;
        case AST_MULT: 
            decompile(node->son[0],out);
            fprintf(out, " * "); 
            decompile(node->son[1],out);
            break;
        case AST_DIV: 
            decompile(node->son[0],out);
            fprintf(out, " / "); 
            decompile(node->son[1],out);
            break;
        case AST_MINOR: 
            decompile(node->son[0],out);
            fprintf(out, " < "); 
            decompile(node->son[1],out);
            break;
        case AST_BIGGER: 
            decompile(node->son[0],out);
            fprintf(out, " > "); 
            decompile(node->son[1],out);
            break;
        case AST_OR: 
            decompile(node->son[0],out);
            fprintf(out, " | "); 
            decompile(node->son[1],out);
            break;
        case AST_AND: 
            decompile(node->son[0],out);
            fprintf(out, " & "); 
            decompile(node->son[1],out); 
            break;
        case AST_NOT: 
            fprintf(out, " ~ "); 
            decompile(node->son[0],out); 
            break;
        case AST_DOLLAR: 
            fprintf(out, " $ "); 
            decompile(node->son[0],out); 
            break;
        case AST_TAG: 
            fprintf(out, " # "); 
            decompile(node->son[0],out); 
            break;
        case AST_LE: 
            decompile(node->son[0],out);
            fprintf(out, " <= "); 
            decompile(node->son[1],out); 
            break;
        case AST_GE: 
            decompile(node->son[0],out);
            fprintf(out, " >= "); 
            decompile(node->son[1],out); 
            break;
        case AST_EQ: 
            decompile(node->son[0],out);
            fprintf(out, " == "); 
            decompile(node->son[1],out); 
            break;
        case AST_DIF: 
            decompile(node->son[0],out);
            fprintf(out, " != "); 
            decompile(node->son[1],out); 
            break;
        case AST_VECTOR: 
            fprintf(out, "%s", node->symbol->text); 
            fprintf(out, "["); 
            decompile (node->son[0], out);
            fprintf(out, "]");
            break;
        case AST_PARAMETER: 
            decompile (node->son[0], out); 
            fprintf(out, "%s", node->symbol->text); 
            if (node->son[1]!=0)
            {
                fprintf(out, ", ");
                decompile (node->son[1], out); 
            }
            break;
        case AST_KW_INT: 
            fprintf(out, "int ");
            break;
        case AST_KW_BOOL: 
            fprintf(out, "bool ");
            break;
        case AST_KW_CHAR: 
            fprintf(out, "char ");
            break;
        case AST_KW_POINTER: 
            fprintf(out, "pointer ");
            break;
        case AST_VECT_VL: 
            decompile (node->son[0], out); 
            if (node->son[1]!=0)
            {
                fprintf(out, " "); 
                decompile (node->son[1], out);
            }
            break;
        case AST_LCMMD: 
            fprintf(out, "\n\t");
            decompile(node->son[0], out); 
            fprintf(out, ";");
            decompile(node->son[1], out); 
            break;
        case AST_READ: 
            fprintf(out, "read ");
            fprintf(out, "%s", node->symbol->text); 
            break;
        case AST_PRINT: 
            fprintf(out, "print "); 
            decompile(node->son[0], out); 
            break; 
        case AST_STRING: 
            fprintf(out, "%s", node->symbol->text); 
            if (node->son[0]!= 0)
            {  
            fprintf(out, ", ");
            decompile(node->son[0], out); 
            };
            break;
        case AST_RETURN: 
            fprintf(out, "return "); 
            decompile (node-> son[0], out);
            break;
        case AST_IF: 
            fprintf(out, "\n\nif ( "); 
            decompile (node->son [0], out); 
            fprintf(out, " ) then\n"); 
            decompile (node->son [1], out); 
            break;
        case AST_WHILE: 
            fprintf(out, "\n\nwhile ( "); 
            decompile (node->son[0], out);
            fprintf (out, ")\n"); 
            decompile (node->son[1], out);
            break;
        case AST_IF_ELSE: 
            fprintf(out, "\n\nif ( "); 
            decompile (node->son [0], out); 
            fprintf(out, " ) then\n"); 
            decompile (node->son [1], out); 
            fprintf (out, "\n\telse \n");
            decompile (node->son [2], out); 
            break;
        case AST_RIGHT_ASSGN: 
            decompile (node->son[0], out); 
            fprintf(out," -> ");
            fprintf(out, "%s", node->symbol->text); 
            break;
        case AST_LEFT_ASSGN: 
            fprintf(out, "%s", node->symbol->text);  
            fprintf(out," <- ");
            decompile (node->son[0], out); 
            break;

        case AST_LEFT_ASSGN_V: 
            fprintf(out, "%s", node->symbol->text); 
            fprintf(out, "["); 
            decompile (node -> son[0], out); 
            fprintf(out,"] <- ");
            decompile (node->son[1], out); 
            break;
        case AST_RIGHT_ASSGN_V: 
            decompile (node->son[0], out); 
             fprintf(out," -> " );
            fprintf(out, "%s", node->symbol->text); 
            fprintf(out, "["); 
            decompile (node -> son[1], out); 
            fprintf(out,"]");
            break;
        case AST_LPRNT:
            decompile(node->son[0], out);
            fprintf(out, ",");
            decompile(node->son[1], out); 
            break;
        
        case AST_LARG: 
            decompile(node->son[0],out);                 
			if(node->son[1]!=0)
            {
                fprintf(out,", ");   
                decompile(node->son[1],out); 
            }         
            break;
        
        case AST_CALL_FUNCT: 
            fprintf(out, " %s (", node->symbol->text); 
            if (node->son[0]!=0)
            {
                decompile(node->son[0],out); 
            }
            fprintf (out, ") ");
            break;
        case AST_LIT_DEF: 
            fprintf(out, " %s (", node->symbol->text); 
            break;
        case AST_DEC_FUNCT: 
            fprintf(out, "\n\n");
            decompile(node->son[0], out);
            fprintf(out, " %s (", node->symbol->text); 
            decompile(node->son[1], out); 
            fprintf(out, " ) ");
            decompile(node->son[2], out); 
            break;
        case AST_DEC_VECTOR: 
            
            decompile(node->son[0],out);                 
            fprintf(out,"["); 
            decompile(node->son[1],out); 
            fprintf(out,"]");	
            fprintf(out," %s", node->symbol->text);
			if(node->son[2]!=0)
            {
                fprintf(out,": ");   
                decompile(node->son[2],out); 
            }         
            break;
        
        case AST_DEC_VAR: 
            decompile(node->son[0], out);
            fprintf(out, " ");
            decompile(node->son[1], out); 
            break;
        case AST_DECL: 
            decompile(node->son[0], out);
            fprintf(out, ";\n");
            decompile(node->son[1], out); 
            break;
        case AST_BODY: 
            fprintf(out, "\n{");
            decompile(node->son[0], out);
            fprintf(out, "\n}");
             break;
        case AST_PARENT: 
            fprintf(out, "("); 
            decompile (node->son[0], out);
            fprintf(out, ")");
            break;
        default: fprintf(out, "UNKOWN");  break;
    }
}


int main(int argc, char ** argv)
{
   int tok; 
    FILE *outfile;
       if(argc < 3){
        fprintf(stderr, "Call: etapa3 fileName\n");
        exit(1);
    }
    
    yyin = fopen(argv[1], "r");

    if(yyin == 0){
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(2);
    }
      
    outfile = fopen(argv[2], "w");
    
    if (yyin == NULL){
        fprintf(stderr, "Cannot open output file %s\n", argv[2]);
        exit(2);
    }
    initMe();

    yyparse();

    decompile(finalAST, outfile);

    hashPrint();
    fprintf(stderr, "Compilation successful! \n");

       exit(0);
}
