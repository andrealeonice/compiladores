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

    yyparse();
  
    hashPrint();
    fprintf(stderr, "Compilation successful! \n");

       exit(0);
}