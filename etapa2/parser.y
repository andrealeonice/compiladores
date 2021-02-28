


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

%left '|' '&'
%left '<' '>' OPERATOR_EQ OPERATOR_DIF OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'
%left '~' '#' '$'

%%

programa: decl
    ;

decl: dec ';' decl
    |
    ;

dec: type def
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER init_v
    | type TK_IDENTIFIER '(' param ')' body
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

 body: '{' lcmmd '}'
    ;

lcmmd: cmmd ';' lcmmd
    |
    ;

cmmd: assign
    | flow_ctrl
    | KW_READ TK_IDENTIFIER
    | KW_PRINT lprnt
    | KW_RETURN expr
    | body
    ;

flow_ctrl: KW_IF '(' expr ')' KW_THEN cmmd
    | KW_IF '(' expr ')' KW_THEN cmmd KW_ELSE cmmd
    | KW_WHILE '(' expr')' cmmd

assign: expr RIGHT_ASSIGN TK_IDENTIFIER
    | TK_IDENTIFIER LEFT_ASSIGN expr
    | TK_IDENTIFIER '['expr']' LEFT_ASSIGN expr
    | expr RIGHT_ASSIGN TK_IDENTIFIER '[' expr ']'
    ;

lprnt: LIT_STRING ',' lprnt
    | LIT_STRING
    | expr ',' lprnt
    | expr
    ;

expr: lit_def
    | TK_IDENTIFIER
    | TK_IDENTIFIER '[' expr ']'
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
    | '(' expr ')'
    | call_funct
    ;

call_funct: TK_IDENTIFIER '(' larg ')'
    | TK_IDENTIFIER '('')'
    ;

larg: expr add_arg
    ;

add_arg: ',' larg
    |
    ;
%%

int yyerror ()
{
 fprintf(stderr, "Sysntax error at line %d. \n", getLineNumber()); 
 exit(3); 

}