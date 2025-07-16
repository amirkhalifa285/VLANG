
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symTab.h"

symbol symbol_table[100];
int symbol_count = 0;
ast_node *root_node = NULL;

ast_node *new_node(int type, ast_node *left, ast_node *right) {
    ast_node *node = (ast_node *)malloc(sizeof(ast_node));
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

ast_node *new_leaf(int type, char *name) {
    ast_node *node = (ast_node *)malloc(sizeof(ast_node));
    node->type = type;
    node->name = name;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void add_symbol(char *name, var_type type, int size) {
    symbol_table[symbol_count].name = name;
    symbol_table[symbol_count].type = type;
    symbol_table[symbol_count].size = size;
    symbol_count++;
}

symbol *get_symbol(char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return &symbol_table[i];
        }
    }
    return NULL;
}
