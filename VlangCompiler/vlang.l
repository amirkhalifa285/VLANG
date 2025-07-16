



%{
#include <stdio.h>
#include <string.h>
#include "symTab.h"
#include "y.tab.h"
extern void yyerror(const char *s);
%}





%%

"scl"       { return SCL; }
"vec"       { return VEC; }
"if"        { return IF; }
"loop"      { return LOOP; }
"print"     { return PRINT; }

"@"         { return AT; }
"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }

"="         { return ASSIGN; }

"{"         { return LBRACE; }
"}"         { return RBRACE; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"["         { return LBRACK; }
"]"         { return RBRACK; }
":"         { return COLON; }
";"         { return SEMI; }
","         { return COMMA; }

\"[^\"]*\" { 
    yytext[strlen(yytext)-1] = '\0';
    yylval.sval = strdup(yytext+1); 
    return STRING_LITERAL; 
}

[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return ID; }
[0-9]+      { yylval.ival = atoi(yytext); return INT_LITERAL; }


[ \t\n]+   ; /* skip whitespace */
.           { yyerror("Unknown character"); }

%%

int yywrap(void) {
    return 1;
}