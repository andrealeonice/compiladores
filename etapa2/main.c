int main(int argc, char ** argv)
{
   int tok; 

       if(argc < 2){
        fprintf(stderr, "Call: etapa1 fileName\n");
        exit(1);
    }
    
    yyin = fopen(argv[1], "r");

    if(yyin == 0){
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        exit(2);
    }

    initMe();

    while(isRunning())
   {
     
    tok = yylex();

    if (running==0)
    break; 

    switch (tok)
    { 
        case KW_CHAR: printf("L: %d\t Found KW_CHAR\n", getLineNumber()); break;
        case KW_INT: printf("L: %d\t Found KW_INT\n", getLineNumber());  break;
        case KW_BOOL: printf("L: %d\t Found KW_BOOL\n",getLineNumber());  break;
        case KW_POINTER: printf("L: %d\t Found KW_POINTER\n",getLineNumber());  break;
        case KW_IF: printf("L: %d\t Found KW_IF\n",getLineNumber());  break;
        case KW_THEN: printf("L: %d\t Found KW_THEN\n",getLineNumber());  break;
        case KW_ELSE: printf("L: %d\t Found KW_ELSE\n",getLineNumber());  break;
        case KW_WHILE: printf("L: %d\t Found KW_WHILE\n",getLineNumber());  break;
        case KW_READ: printf("L: %d\t Found KW_READ\n",getLineNumber());  break;
        case KW_PRINT: printf("L: %d\t Found KW_PRINT\n", getLineNumber());  break;
        case KW_RETURN: printf("L: %d\t Found KW_RETURN\n",getLineNumber());  break;
        case OPERATOR_LE: printf("L: %d\t Found OPERATOR_LE\n",getLineNumber());  break;
        case OPERATOR_GE: printf("L: %d\t Found OPERATOR_GE\n",getLineNumber());  break;
        case OPERATOR_EQ: printf("L: %d\t Found OPERATOR_EQ\n",getLineNumber());   break;
        case OPERATOR_DIF: printf("L: %d\t Found OPERATOR_DIF\n",getLineNumber());  break;
        case LEFT_ASSIGN: printf("L: %d\t Found LEFT_ASSIGN\n",getLineNumber());  break;
        case RIGHT_ASSIGN: printf("L: %d\t Found RIGHT_ASSIGN\n",getLineNumber());  break;
        case LIT_INTEGER: printf("L: %d\t Found LIT_INTEGER\n",getLineNumber());  break;
        case LIT_CHAR: printf("L: %d\t Found LIT_CHAR\n",getLineNumber());  break;
        case TK_IDENTIFIER: printf("L: %d\t Found TK_IDENTIFIER\n", getLineNumber());  break; 
        case LIT_STRING: printf("L: %d\t Found LIT_STRING\n",getLineNumber());   break;
        case LIT_TRUE: printf("L: %d\t Found LIT_TRUE\n",getLineNumber());  break;
        case LIT_FALSE: printf("L: %d\t Found LIT_FALSE\n",getLineNumber());  break;
        case TOKEN_ERROR: printf("L: %d\t Invalid TOKEN %d\n", getLineNumber(),tok);  break;
        default: printf("L: %d\t Found %c\n", getLineNumber(),yytext[0]);  break;


    }
  }
    hashPrint();
       exit(0);
}