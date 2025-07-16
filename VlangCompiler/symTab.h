
#ifndef SYMTAB_H
#define SYMTAB_H

typedef enum { SCL_TYPE, VEC_TYPE } var_type;

typedef enum {
    ADD_NODE, SUB_NODE, MUL_NODE, DIV_NODE, AT_NODE, COLON_NODE, ASSIGN_NODE,
    IF_NODE, LOOP_NODE, PRINT_NODE, SEMI_NODE, COMMA_NODE, VEC_LITERAL_NODE,
    INT_LITERAL_NODE, ID_NODE, STRING_LITERAL_NODE
} ast_node_type;

typedef struct ast_node {
    ast_node_type type;
    char *name;
    struct ast_node *left;
    struct ast_node *right;
} ast_node;

typedef struct {
    char *name;
    var_type type;
    int size;
} symbol;

extern symbol symbol_table[100];
extern int symbol_count;
extern ast_node *root_node;

ast_node *new_node(int type, ast_node *left, ast_node *right);
ast_node *new_leaf(int type, char *name);
void add_symbol(char *name, var_type type, int size);
symbol *get_symbol(char *name);

#endif
