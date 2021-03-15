%{
    #include "hash.h"
    #include "ast.h"
int yyerror();
int getLineNumber(void);
int yylex();

%}

%union 
{
    HASH_NODE *symbol;
    AST *ast;
}

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
%token  <symbol> TK_IDENTIFIER 

%token <symbol> LIT_INTEGER   
%token <symbol> LIT_TRUE      
%token <symbol> LIT_FALSE     
%token <symbol> LIT_CHAR      
%token <symbol> LIT_STRING    
%token TOKEN_ERROR  

%type<ast> expr
%type<ast> lit_def
%type<ast> init_v
%type<ast> values_v
%type<ast> values_p
%type<ast> param
%type<ast> cmmd
%type<ast> lcmmd
%type<ast> add_arg
%type<ast> assign
%type<ast> flow_ctrl
%type<ast> body
%type<ast> programa
%type<ast> decl
%type<ast> dec
%type<ast> type
%type<ast> def
%type<ast> lprnt
%type<ast> call_funct
%type<ast> larg

%left '|' '&'
%left '<' '>' OPERATOR_EQ OPERATOR_DIF OPERATOR_GE OPERATOR_LE
%left '+' '-'
%left '*' '/'
%left '~' '#' '$'

%%

programa: decl   {astPrint($1, 0);}
    ;

decl: dec ';' decl   { $$ = astCreate(AST_DECL, 0, $1, $3, 0, 0); }
    |               {$$=0;}
    ;

dec: type def   {$$ = astCreate(AST_DEC_VAR, 0, $1, $2, 0, 0);}
    | type '[' LIT_INTEGER ']' TK_IDENTIFIER init_v   {$$= astCreate(AST_DEC_VECTOR, $5, $1, astCreate(AST_SYMBOL, $3, 0, 0, 0, 0), $6, 0);}
    | type TK_IDENTIFIER '(' param ')' body    {$$= astCreate(AST_DEC_FUNCT, $2, $1, $4, $6, 0);} 
    ;

type: KW_INT                         {$$ = astCreate(AST_KW_INT, 0, 0 ,0, 0, 0);}
    | KW_BOOL                        {$$ = astCreate(AST_KW_BOOL, 0, 0 ,0, 0, 0);}
    | KW_CHAR                        {$$ = astCreate(AST_KW_CHAR, 0, 0 ,0, 0, 0);}
    | KW_POINTER                     {$$ = astCreate(AST_KW_POINTER, 0, 0 ,0, 0, 0);}
    ;

def: TK_IDENTIFIER ':' lit_def      {$$ = astCreate(AST_SYMBOL, $1, $3, 0, 0, 0);}
    ;

lit_def: LIT_CHAR                   {$$ = astCreate(AST_SYMBOL, $1 ,0, 0, 0 , 0);}
    | LIT_INTEGER                   {$$ = astCreate(AST_SYMBOL, $1 ,0, 0, 0 , 0);}
    | LIT_FALSE                     {$$ = astCreate(AST_SYMBOL, $1 ,0, 0, 0 , 0);}
    | LIT_TRUE                      {$$ = astCreate(AST_SYMBOL, $1 ,0, 0, 0 , 0);}
    ;
    
init_v: ':' values_v                {$$ = $2;}
    |                               {$$=0;}
    ;

values_v: lit_def values_v          {$$ = astCreate(AST_VECT_VL, 0, $1, $2, 0 ,0);}
    |                               {$$=0;}
    ;

param: values_p                     {$$=$1;}
    |                               {$$=0;}
    ;

values_p: type TK_IDENTIFIER ',' values_p   {$$ = astCreate(AST_PARAMETER, $2, $1, $4, 0,0);}
    | type TK_IDENTIFIER            {$$=astCreate(AST_PARAMETER, $2, $1, 0,0,0);}
    ;

 body: '{' lcmmd '}'                {$$=$2;}
    ;

lcmmd: cmmd ';' lcmmd               {$$= astCreate(AST_LCMMD, 0, $1, $3, 0, 0);}
    |                               {$$=0;}
    ;

cmmd: assign                        {$$= $1;}
    | flow_ctrl                     {$$=$1;}
    | KW_READ TK_IDENTIFIER         {$$= astCreate(AST_READ, $2, 0,0,0,0);}
    | KW_PRINT lprnt                { $$ = astCreate(AST_PRINT, 0, $2, 0, 0, 0); }
    | KW_RETURN expr                { $$ = astCreate(AST_RETURN, 0, $2, 0, 0, 0); }
    | body                          {$$=$1;}
    |                               {$$=0;}
    ;

flow_ctrl: KW_IF '(' expr ')' KW_THEN cmmd             {$$ = astCreate(AST_IF, 0, $3, $6, 0, 0); }
    | KW_IF '(' expr ')' KW_THEN cmmd KW_ELSE cmmd     {$$ = astCreate(AST_IF_ELSE, 0, $3, $6, $8, 0); }
    | KW_WHILE '(' expr')' cmmd                        {$$ = astCreate(AST_WHILE, 0, $3, $5, 0, 0); }

assign: expr RIGHT_ASSIGN TK_IDENTIFIER                {$$ = astCreate(AST_RIGHT_ASSGN, $3, $1, 0,0,0);}
    | TK_IDENTIFIER LEFT_ASSIGN expr                   {$$ = astCreate(AST_LEFT_ASSGN, $1, $3, 0,0,0);}
    | TK_IDENTIFIER '['expr']' LEFT_ASSIGN expr        {$$ = astCreate(AST_LEFT_ASSGN_V, $1, $3, $6,0,0);}
    | expr RIGHT_ASSIGN TK_IDENTIFIER '[' expr ']'     {$$ = astCreate(AST_RIGHT_ASSGN_V, $3, $1, $5,0,0);}
    ;

lprnt: LIT_STRING ',' lprnt        {$$= astCreate(AST_SYMBOL, $1, $3, 0, 0, 0);}
    | LIT_STRING                   {$$= astCreate(AST_SYMBOL, $1, 0, 0, 0, 0);}
    | expr ',' lprnt               {$$ = astCreate(AST_LPRNT,0, $1, $3, 0, 0 );}
    | expr                         {$$ = $1;}
    ;

expr: lit_def                       {$$= $1;}
    | TK_IDENTIFIER                 {$$= astCreate(AST_SYMBOL, $1 ,0, 0, 0 , 0);}
    | TK_IDENTIFIER '[' expr ']'    {$$ = astCreate(AST_VECTOR, $1, $3, 0, 0, 0); }
    | expr '+' expr                 {$$ = astCreate(AST_ADD,0, $1, $3, 0, 0);}
    | expr '-' expr                 {$$ = astCreate(AST_SUB,0, $1, $3, 0, 0);}
    | expr '*' expr                 {$$ = astCreate(AST_MULT,0, $1, $3, 0, 0);}
    | expr '/' expr                 {$$ = astCreate(AST_DIV,0, $1, $3, 0, 0);}
    | expr '<' expr                 {$$ = astCreate(AST_MINOR,0, $1, $3, 0, 0);}
    | expr '>' expr                 {$$ = astCreate(AST_BIGGER,0, $1, $3, 0, 0);}
    | expr '|' expr                 {$$ = astCreate(AST_OR,0, $1, $3, 0, 0);}
    | expr '&' expr                 {$$ = astCreate(AST_AND,0, $1, $3, 0, 0);}
    | '~' expr                      {$$ = astCreate(AST_NOT, 0, $2, 0, 0, 0);} 
    | '$' expr                      {$$ = astCreate(AST_DOLLAR, 0, $2, 0, 0, 0);} 
    | '#' expr                      {$$ = astCreate(AST_TAG, 0, $2, 0, 0, 0);}       
    | expr OPERATOR_LE expr         {$$ = astCreate(AST_LE,0, $1, $3, 0, 0);}
    | expr OPERATOR_GE expr         {$$ = astCreate(AST_GE,0, $1, $3, 0, 0);}
    | expr OPERATOR_EQ expr         {$$ = astCreate(AST_EQ,0, $1, $3, 0, 0);}
    | expr OPERATOR_DIF expr        {$$ = astCreate(AST_DIF,0, $1, $3, 0, 0);}
    | '(' expr ')'                  {$$ = $2;}
    | call_funct                    {$$ = astCreate(AST_CALL_FUNCT, 0, $1, 0,0,0);}
    ;

call_funct: TK_IDENTIFIER '(' larg ')' {$$= astCreate(AST_SYMBOL, $1 ,$3, 0, 0 , 0);}
    | TK_IDENTIFIER '('')'             {$$= astCreate(AST_SYMBOL, $1 ,0, 0, 0 , 0);}
    ;

larg: expr add_arg                  {$$ = astCreate(AST_LARG, 0, $1, $2, 0,0); }
    ;

add_arg: ',' larg                   {$$ = $2;}
    |                                {$$=0;}
    ;
%%

int yyerror ()
{
 fprintf(stderr, "Sysntax error at line %d. \n", getLineNumber()); 
 exit(3); 

}