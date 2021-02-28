


%token KW_CHAR       
%token KW_INT        
%token KW_BOOL       
%token KW_POINTER    

%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_WHILE      
%token KW_READ       
%token KW_PRINT      
%token KW_RETURN     

%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_DIF  
%token LEFT_ASSIGN   
%token RIGHT_ASSIGN  
%token TK_IDENTIFIER 

%token LIT_INTEGER   
%token LIT_TRUE      
%token LIT_FALSE     
%token LIT_CHAR      
%token LIT_STRING    
%token TOKEN_ERROR    


%%

programa: decl
    ;

decl: dec ';' decl
    |
    ;

dec: type def
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER init_v
    | type TK_IDENTIFIER '(' param ')'
    ;

type: KW_INT
    | KW_BOOL
    | KW_CHAR
    | KW_POINTER
    ;

def: TK_IDENTIFIER ':' lit_def
    ;

lit_def: LIT_CHAR
    | LIT_INTEGER
    | LIT_FALSE
    | LIT_TRUE
    ;
    
init_v: ':' values_v
    |
    ;

values_v: lit_def values_v
    |
    ;

param: values_p 
    |
    ;

values_p: type TK_IDENTIFIER ',' values_p
    | type TK_IDENTIFIER
    ;

 body: '{' lcmd '}'
    ;

lcmd: cmd lcmd
    |
    ;



cmd: TK_IDENTIFIER ':' expr
    ;

expr: LIT_INTEGER
    | LIT_CHAR
    | LIT_FALSE
    | LIT_TRUE
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '<' expr
    | expr '>' expr
    | expr '|' expr
    | expr '&' expr
    | expr '~' 
    | expr '$' 
    | expr '#'
    | expr OPERATOR_LE expr
    | expr OPERATOR_GE expr
    | expr OPERATOR_EQ expr
    | expr OPERATOR_DIF expr
    | expr LEFT_ASSIGN expr
    | expr RIGHT_ASSIGN expr
    | '(' expr ')'

%%

int yyerror ()
{
 fprintf(stderr, "Sysntax error at line %d. \n", getLineNumber()); 
 exit(3); 

}