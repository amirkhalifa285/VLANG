%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

extern int yylex();
void yyerror(const char *s);

#define YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
    int ival;
    char *sval;
    ast_node *node;
} YYSTYPE;

%}

%union {
    int ival;
    char *sval;
    ast_node *node;
}

%token <ival> SCL VEC IF LOOP PRINT
%token <sval> ID STRING_LITERAL
%token <ival> INT_LITERAL
%token AT ADD SUB MUL DIV ASSIGN
%token LBRACE RBRACE LPAREN RPAREN LBRACK RBRACK COLON SEMI COMMA

%type <node> program block statement_list statement declaration assignment conditional_statement loop_statement print_statement expression expression_list term factor vec_literal int_list

%right COLON
%left AT
%left MUL DIV
%left ADD SUB
%nonassoc ASSIGN

%%

program:
    block { $$ = $1; fprintf(stderr, "Parsed program successfully\n"); }
    ;

block:
    LBRACE statement_list RBRACE { $$ = $2; }
    | LBRACE RBRACE { $$ = NULL; }
    ;

statement_list:
    statement { $$ = $1; }
    | statement_list statement { $$ = new_node(SEMI_NODE, $1, $2); }
    ;

statement:
    declaration { $$ = $1; }
    | assignment { $$ = $1; }
    | conditional_statement { $$ = $1; }
    | loop_statement { $$ = $1; }
    | print_statement { $$ = $1; }
    ;

declaration:
    SCL ID SEMI { add_symbol($2, SCL_TYPE, 0); $$ = NULL; }
    | VEC ID LBRACE INT_LITERAL RBRACE SEMI { add_symbol($2, VEC_TYPE, $4); $$ = NULL; }
    ;

assignment:
    ID ASSIGN expression SEMI { $$ = new_node(ASSIGN_NODE, new_leaf(ID_NODE, $1), $3); }
    ;

conditional_statement:
    IF expression block { $$ = new_node(IF_NODE, $2, $3); }
    ;

loop_statement:
    LOOP expression block { $$ = new_node(LOOP_NODE, $2, $3); }
    ;

print_statement:
    PRINT STRING_LITERAL COLON expression_list SEMI { 
        $$ = new_node(PRINT_NODE, new_leaf(STRING_LITERAL_NODE, $2), $4); 
    }
    | PRINT STRING_LITERAL COLON expression SEMI { 
        $$ = new_node(PRINT_NODE, new_leaf(STRING_LITERAL_NODE, $2), $4); 
    }
    ;

expression_list:
    expression { $$ = $1; }
    | expression_list COMMA expression { $$ = new_node(COMMA_NODE, $1, $3); }
    ;

expression:
    term { $$ = $1; }
    | expression ADD term { $$ = new_node(ADD_NODE, $1, $3); }
    | expression SUB term { $$ = new_node(SUB_NODE, $1, $3); }
    ;

term:
    factor { $$ = $1; }
    | term MUL factor { $$ = new_node(MUL_NODE, $1, $3); }
    | term DIV factor { $$ = new_node(DIV_NODE, $1, $3); }
    | term AT factor { $$ = new_node(AT_NODE, $1, $3); }
    ;

factor:
    INT_LITERAL { $$ = new_leaf(INT_LITERAL_NODE, (char *)malloc(sizeof(char)*10)); sprintf($$->name, "%d", $1); }
    | vec_literal { $$ = $1; }
    | ID { $$ = new_leaf(ID_NODE, $1); }
    | ID COLON factor { $$ = new_node(COLON_NODE, new_leaf(ID_NODE, $1), $3); }
    | LPAREN expression RPAREN { $$ = $2; }
    ;



vec_literal:
    LBRACK INT_LITERAL RBRACK { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", $2); $$ = new_node(VEC_LITERAL_NODE, new_leaf(INT_LITERAL_NODE, s), NULL); }
    | LBRACK INT_LITERAL COMMA int_list RBRACK { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", $2); $$ = new_node(VEC_LITERAL_NODE, new_leaf(INT_LITERAL_NODE, s), $4); }
    ;

int_list:
    INT_LITERAL { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", $1); $$ = new_leaf(INT_LITERAL_NODE, s); }
    | int_list COMMA INT_LITERAL { char *s = (char *)malloc(sizeof(char)*10); sprintf(s, "%d", $3); $$ = new_node(COMMA_NODE, $1, new_leaf(INT_LITERAL_NODE, s)); }
    ;



%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
        extern FILE *yyin;
        yyin = file;
    }
    
    fprintf(stderr, "Starting parse...\n");
    int result = yyparse();
    fprintf(stderr, "Parse completed with result: %d\n", result);
    
    // TODO: Add code generation here
    
    return result;
}