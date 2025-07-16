%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

extern int yylex();
void yyerror(const char *s);

// Code generation functions
void generate_code(ast_node *node);
void generate_declaration(ast_node *node);
void generate_assignment(ast_node *node);
void generate_expression(ast_node *node);
void generate_print(ast_node *node);
void generate_if(ast_node *node);
void generate_loop(ast_node *node);
void generate_vec_literal(ast_node *node);
void generate_vec_assignment(char *var_name, ast_node *vec_node, int size);
void generate_vec_assignment_with_declaration(char *var_name, ast_node *vec_node, int size);
void generate_scalar_assignment_with_declaration(char *var_name, ast_node *expr_node);
void generate_code_with_declarations(ast_node *node);
void declare_variable_if_needed(char *var_name);

static int temp_var_count = 0;
static int label_count = 0;
static int declared_vars[100] = {0}; // Track which variables have been declared

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
    block { $$ = $1; root_node = $1; }
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
    | ID COLON factor ASSIGN expression SEMI { $$ = new_node(ASSIGN_NODE, new_node(COLON_NODE, new_leaf(ID_NODE, $1), $3), $5); }
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
    fprintf(stderr, "error: %s\n", s);
}

int main(int argc, char *argv[]) {
    extern FILE *yyin;
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            fprintf(stderr, "Cannot open file: %s\n", argv[1]);
            return 1;
        }
        yyin = file;
    }
    
    int result = yyparse();
    if (result == 0) {
        printf("#include <stdio.h>\n");
        printf("#include <stdlib.h>\n");
        printf("#include <string.h>\n\n");
        
        printf("int main() {\n");
        
        // Generate code from AST with smart declaration handling
        if (root_node) {
            generate_code_with_declarations(root_node);
        }
        
        printf("    return 0;\n");
        printf("}\n");
    }
    return result;
}

// Code generation functions implementation
void generate_code(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case SEMI_NODE:
            generate_code(node->left);
            generate_code(node->right);
            break;
        case ASSIGN_NODE:
            generate_assignment(node);
            break;
        case IF_NODE:
            generate_if(node);
            break;
        case LOOP_NODE:
            generate_loop(node);
            break;
        case PRINT_NODE:
            generate_print(node);
            break;
        default:
            break;
    }
}

void generate_assignment(ast_node *node) {
    if (node->left->type == ID_NODE) {
        // Check if it's a vector assignment
        symbol *sym = get_symbol(node->left->name);
        if (sym && sym->type == VEC_TYPE && node->right->type == VEC_LITERAL_NODE) {
            // Vector literal assignment: v = [1,2,3,4,5]
            generate_vec_assignment_with_declaration(node->left->name, node->right, sym->size);
        } else if (sym && sym->type == VEC_TYPE && node->right->type == INT_LITERAL_NODE) {
            // Scalar to vector assignment: v = 5 (assigns 5 to all elements)
            printf("    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            printf(";\n");
        } else {
            // Simple scalar assignment: x = expression
            generate_scalar_assignment_with_declaration(node->left->name, node->right);
        }
    } else if (node->left->type == COLON_NODE) {
        // Vector indexing assignment: v:i = expression
        printf("    %s[", node->left->left->name);
        generate_expression(node->left->right);
        printf("] = ");
        generate_expression(node->right);
        printf(";\n");
    }
}

void generate_expression(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case INT_LITERAL_NODE:
            printf("%s", node->name);
            break;
        case ID_NODE:
            printf("%s", node->name);
            break;
        case ADD_NODE:
            printf("(");
            generate_expression(node->left);
            printf(" + ");
            generate_expression(node->right);
            printf(")");
            break;
        case SUB_NODE:
            printf("(");
            generate_expression(node->left);
            printf(" - ");
            generate_expression(node->right);
            printf(")");
            break;
        case MUL_NODE:
            printf("(");
            generate_expression(node->left);
            printf(" * ");
            generate_expression(node->right);
            printf(")");
            break;
        case DIV_NODE:
            printf("(");
            generate_expression(node->left);
            printf(" / ");
            generate_expression(node->right);
            printf(")");
            break;
        case VEC_LITERAL_NODE:
            generate_vec_literal(node);
            break;
        case COLON_NODE:
            // Vector indexing: v:i
            printf("%s[", node->left->name);
            generate_expression(node->right);
            printf("]");
            break;
        case AT_NODE:
            // Dot product - need to generate a loop
            printf("dot_product_%d", temp_var_count++);
            break;
        default:
            break;
    }
}

void generate_vec_literal(ast_node *node) {
    // For vector literals like [1,2,3], we need to assign each element
    // This is a simplified version - in practice you'd need to handle the target variable
    printf("/* vector literal */");
}

void generate_print(ast_node *node) {
    printf("    printf(\"%s: ", node->left->name);
    
    // Handle expression list - check if it's a vector or scalar
    ast_node *expr = node->right;
    if (expr->type == ID_NODE) {
        symbol *sym = get_symbol(expr->name);
        if (sym && sym->type == VEC_TYPE) {
            // Print vector
            printf("[");
            for (int i = 0; i < sym->size; i++) {
                if (i > 0) printf(", ");
                printf("%%d");
            }
            printf("]\\n\"");
            for (int i = 0; i < sym->size; i++) {
                printf(", %s[%d]", expr->name, i);
            }
            printf(");\n");
        } else {
            // Print scalar
            printf("%%d\\n\", ");
            generate_expression(expr);
            printf(");\n");
        }
    } else {
        // Print expression result
        printf("%%d\\n\", ");
        generate_expression(expr);
        printf(");\n");
    }
}

void generate_if(ast_node *node) {
    printf("    if (");
    generate_expression(node->left);
    printf(") {\n");
    generate_code(node->right);
    printf("    }\n");
}

void generate_loop(ast_node *node) {
    int loop_label = label_count++;
    printf("    for (int loop_var_%d = 0; loop_var_%d < ", loop_label, loop_label);
    generate_expression(node->left);
    printf("; loop_var_%d++) {\n", loop_label);
    generate_code(node->right);
    printf("    }\n");
}

void generate_vec_assignment(char *var_name, ast_node *vec_node, int size) {
    // Generate assignment for vector literal like v = [1,2,3,4,5]
    int index = 0;
    ast_node *current = vec_node->left; // First element
    
    // Assign first element
    printf("    %s[%d] = %s;\n", var_name, index++, current->name);
    
    // Assign remaining elements from the list
    current = vec_node->right; // The int_list part
    while (current && index < size) {
        if (current->type == COMMA_NODE) {
            printf("    %s[%d] = %s;\n", var_name, index++, current->right->name);
            current = current->left;
        } else {
            printf("    %s[%d] = %s;\n", var_name, index++, current->name);
            break;
        }
    }
}

void declare_variable_if_needed(char *var_name) {
    symbol *sym = get_symbol(var_name);
    if (!sym) return;
    
    // Find symbol index
    int sym_index = -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            sym_index = i;
            break;
        }
    }
    
    if (sym_index >= 0 && !declared_vars[sym_index]) {
        if (sym->type == SCL_TYPE) {
            printf("    int %s;\n", var_name);
        } else if (sym->type == VEC_TYPE) {
            printf("    int %s[%d];\n", var_name, sym->size);
        }
        declared_vars[sym_index] = 1;
    }
}

void generate_code_with_declarations(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case SEMI_NODE:
            generate_code_with_declarations(node->left);
            generate_code_with_declarations(node->right);
            break;
        case ASSIGN_NODE:
            generate_assignment(node);
            break;
        case IF_NODE:
            generate_if(node);
            break;
        case LOOP_NODE:
            generate_loop(node);
            break;
        case PRINT_NODE:
            generate_print(node);
            break;
        default:
            break;
    }
}

void generate_scalar_assignment_with_declaration(char *var_name, ast_node *expr_node) {
    symbol *sym = get_symbol(var_name);
    if (!sym) return;
    
    // Find symbol index
    int sym_index = -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            sym_index = i;
            break;
        }
    }
    
    if (sym_index >= 0 && !declared_vars[sym_index]) {
        // Combine declaration and initialization
        printf("    int %s = ", var_name);
        generate_expression(expr_node);
        printf(";\n");
        declared_vars[sym_index] = 1;
    } else {
        // Variable already declared, just assign
        printf("    %s = ", var_name);
        generate_expression(expr_node);
        printf(";\n");
    }
}

void generate_vec_assignment_with_declaration(char *var_name, ast_node *vec_node, int size) {
    symbol *sym = get_symbol(var_name);
    if (!sym) return;
    
    // Find symbol index
    int sym_index = -1;
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, var_name) == 0) {
            sym_index = i;
            break;
        }
    }
    
    if (sym_index >= 0 && !declared_vars[sym_index]) {
        // Generate vector declaration with initialization
        printf("    int %s[%d] = {", var_name, size);
        
        // Extract values from AST
        ast_node *current = vec_node->left; // First element
        printf("%s", current->name);
        
        // Add remaining elements from the list
        current = vec_node->right; // The int_list part
        int count = 1;
        while (current && count < size) {
            if (current->type == COMMA_NODE) {
                printf(", %s", current->right->name);
                current = current->left;
            } else {
                printf(", %s", current->name);
                break;
            }
            count++;
        }
        
        printf("};\n");
        declared_vars[sym_index] = 1;
    } else {
        // Variable already declared, use individual assignments
        generate_vec_assignment(var_name, vec_node, size);
    }
}