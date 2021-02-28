%{
 #include "y.tab.h"
 #include "hash.c"
int running = 1;
int lineNumber = 1;

int isRunning(void){
    return running;
}
  
  int getLineNumber(void){
        return lineNumber;
    }
  
  void initMe(void)
  {
    hashInit();
  }
%}

%x COMMENT

%%
[-,;:()\]\[{}+*/<>|&~$#]       {return yytext[0];}
char                           {return KW_CHAR;}
int                            {return KW_INT;}
bool                           {return KW_BOOL;}
pointer                        {return KW_POINTER;} 
if                             {return KW_IF;}
then                           {return KW_THEN;}
else                           {return KW_ELSE;}
while                          {return KW_WHILE;}
read                           {return KW_READ;}
print                          {return KW_PRINT;}
return                         {return KW_RETURN;}

"<="                           {return OPERATOR_LE;}
">="                           {return OPERATOR_GE;}
"=="                           {return OPERATOR_EQ;}
"!="                           {return OPERATOR_DIF;}
"<-"                           {return LEFT_ASSIGN;}
"->"                           {return RIGHT_ASSIGN;}

"\n"                           {++lineNumber;}
[ \t]
"//".*                          
"/*"                           {BEGIN (COMMENT);}
"true"                         {return LIT_TRUE;}
"false"                        {return LIT_FALSE;}
[a-zA-Z_]+[0-9a-zA-Z_]*        {hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER;}

<COMMENT>"*/"                  {BEGIN (INITIAL);}
<COMMENT>"\n"                  {++lineNumber;}
<COMMENT>.

[0-9]+                         {hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER;}
'[^\n']'                       {hashInsert(yytext, LIT_CHAR); return LIT_CHAR;}
 \"[^\n"]+\"                   {hashInsert(yytext, LIT_STRING); return LIT_STRING;}

.                              {return TOKEN_ERROR;}

%%
#include "y.tab.c"
#include "main.c"

int yywrap()
{
    running = 0;
    return 1; 
}