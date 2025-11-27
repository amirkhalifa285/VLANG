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
        // Generate C code to a temporary file
        FILE *c_file = fopen("temp_output.c", "w");
        if (!c_file) {
            fprintf(stderr, "Cannot create temporary C file\n");
            return 1;
        }
        
        // Write C code to file
        fprintf(c_file, "#include <stdio.h>\n");
        fprintf(c_file, "#include <stdlib.h>\n");
        fprintf(c_file, "#include <string.h>\n\n");
        
        fprintf(c_file, "int main() {\n");
        
        // Generate code from AST with smart declaration handling
        if (root_node) {
            // Set global file pointer for code generation
            output_file = c_file;
            generate_code_with_declarations(root_node);
        }
        
        fprintf(c_file, "    return 0;\n");
        fprintf(c_file, "}\n");
        
        fclose(c_file);
        
        // Compile the C code
        fprintf(stderr, "Compiling generated C code...\n");
        int compile_result = system("gcc temp_output.c -o temp_program.exe");
        if (compile_result != 0) {
            fprintf(stderr, "Compilation failed!\n");
            return 1;
        }
        
        // Run the executable
        fprintf(stderr, "Running compiled program:\n");
        fprintf(stderr, "------------------------\n");
        int run_result = system("temp_program.exe");
        
        // Clean up temporary files
        remove("temp_output.c");
        remove("temp_program.exe");
        
        return run_result;
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
            declare_variable_if_needed(node->left->name);
            fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            fprintf(output_file, ";\n");
        } else if (sym && sym->type == VEC_TYPE && (node->right->type == ADD_NODE || node->right->type == SUB_NODE || node->right->type == MUL_NODE || node->right->type == DIV_NODE)) {
            // Vector arithmetic assignment: v3 = v1+v2
            declare_variable_if_needed(node->left->name);
            fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            fprintf(output_file, ";\n");
        } else if (sym && sym->type == VEC_TYPE) {
            // Vector assignment with expression (like v1 = 2*x)
            declare_variable_if_needed(node->left->name);
            fprintf(output_file, "    for(int i = 0; i < %d; i++) %s[i] = ", sym->size, node->left->name);
            generate_expression(node->right);
            fprintf(output_file, ";\n");
        } else {
            // Simple scalar assignment: x = expression
            generate_scalar_assignment_with_declaration(node->left->name, node->right);
        }
    } else if (node->left->type == COLON_NODE) {
        // Vector indexing assignment: v:i = expression
        fprintf(output_file, "    %s[", node->left->left->name);
        generate_expression(node->left->right);
        fprintf(output_file, "] = ");
        generate_expression(node->right);
        fprintf(output_file, ";\n");
    }
}

void generate_expression(ast_node *node) {
    if (!node) return;
    
    switch (node->type) {
        case INT_LITERAL_NODE:
            fprintf(output_file, "%s", node->name);
            break;
        case ID_NODE:
            fprintf(output_file, "%s", node->name);
            break;
        case ADD_NODE:
        case SUB_NODE:
        case MUL_NODE:
        case DIV_NODE:
            fprintf(output_file, "(");
            generate_expression(node->left);
            switch(node->type) {
                case ADD_NODE: fprintf(output_file, " + "); break;
                case SUB_NODE: fprintf(output_file, " - "); break;
                case MUL_NODE: fprintf(output_file, " * "); break;
                case DIV_NODE: fprintf(output_file, " / "); break;
            }
            generate_expression(node->right);
            fprintf(output_file, ")");
            break;
        case VEC_LITERAL_NODE:
            generate_vec_literal(node);
            break;
        case COLON_NODE:
            // Vector indexing: v:i
            fprintf(output_file, "%s[", node->left->name);
            generate_expression(node->right);
            fprintf(output_file, "]");
            break;
        case AT_NODE:
            // Dot product - generate inline calculation
            generate_dot_product(node);
            break;
        default:
            break;
    }
}

void generate_vec_literal(ast_node *node) {
    int temp_id = temp_var_count++;
    fprintf(output_file, "({ int temp_vec_%d[] = {", temp_id);

    char *values[100];
    int value_count = 0;
    
    ast_node *current = node->left;
    values[value_count++] = current->name;
    
    current = node->right;
    collect_int_list_values(current, values, &value_count, 100);
    
    for (int i = 0; i < value_count; i++) {
        if (i > 0) fprintf(output_file, ", ");
        fprintf(output_file, "%s", values[i]);
    }
    
    fprintf(output_file, "}; temp_vec_%d; })", temp_id);
}

void generate_print(ast_node *node) {
    ast_node *expr = node->right;
    symbol *sym = NULL;

    if (expr->type == ID_NODE) {
        sym = get_symbol(expr->name);
    }

    if (sym && sym->type == VEC_TYPE) {
        fprintf(output_file, "    printf(\"%s: [\"");\n", node->left->name);
        fprintf(output_file, "    for (int i = 0; i < %d; i++) {\n", sym->size);
        fprintf(output_file, "        if (i > 0) printf(\", \");\n");
        fprintf(output_file, "        printf(\"%%d\", %s[i]);\n", expr->name);
        fprintf(output_file, "    }\n");
        fprintf(output_file, "    printf(\"]\\n\");\n");
    } else {
        fprintf(output_file, "    printf(\"%s: %%d\\n\", ", node->left->name);
        generate_expression(expr);
        fprintf(output_file, ");\n");
    }
}

void generate_if(ast_node *node) {
    fprintf(output_file, "    if (");
    generate_expression(node->left);
    fprintf(output_file, ") {\n");
    generate_code_with_declarations(node->right);
    fprintf(output_file, "    }\n");
}

void generate_loop(ast_node *node) {
    int loop_label = label_count++;
    fprintf(output_file, "    for (int loop_var_%d = 0; loop_var_%d < ", loop_label, loop_label);
    generate_expression(node->left);
    fprintf(output_file, "; loop_var_%d++) {\n", loop_label);
    generate_code_with_declarations(node->right);
    fprintf(output_file, "    }\n");
}

void generate_vec_assignment(char *var_name, ast_node *vec_node, int size) {
    // Generate assignment for vector literal like v = [1,2,3,4,5]
    int index = 0;
    ast_node *current = vec_node->left; // First element
    
    // Assign first element
    fprintf(output_file, "    %s[%d] = %s;\n", var_name, index++, current->name);
    
    // Assign remaining elements from the list
    current = vec_node->right; // The int_list part
    while (current && index < size) {
        if (current->type == COMMA_NODE) {
            fprintf(output_file, "    %s[%d] = %s;\n", var_name, index++, current->right->name);
            current = current->left;
        } else {
            fprintf(output_file, "    %s[%d] = %s;\n", var_name, index++, current->name);
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
            fprintf(output_file, "    int %s;\n", var_name);
        } else if (sym->type == VEC_TYPE) {
            fprintf(output_file, "    int %s[%d];\n", var_name, sym->size);
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
        fprintf(output_file, "    int %s = ", var_name);
        generate_expression(expr_node);
        fprintf(output_file, ";\n");
        declared_vars[sym_index] = 1;
    } else {
        // Variable already declared, just assign
        fprintf(output_file, "    %s = ", var_name);
        generate_expression(expr_node);
        fprintf(output_file, ";\n");
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
        fprintf(output_file, "    int %s[%d] = {", var_name, size);
        
        // Extract values from AST - need to collect all values first to print in correct order
        char *values[size];
        int value_count = 0;
        
        // Get first element
        ast_node *current = vec_node->left;
        values[value_count++] = current->name;
        
        // Get remaining elements from the int_list
        current = vec_node->right;
        collect_int_list_values(current, values, &value_count, size);
        
        // Print all values in correct order
        for (int i = 0; i < value_count && i < size; i++) {
            if (i > 0) fprintf(output_file, ", ");
            fprintf(output_file, "%s", values[i]);
        }
        
        fprintf(output_file, "};\n");
        declared_vars[sym_index] = 1;
    } else {
        // Variable already declared, use individual assignments
        generate_vec_assignment(var_name, vec_node, size);
    }
}

void collect_int_list_values(ast_node *node, char **values, int *count, int max_size) {
    if (!node || *count >= max_size) return;
    
    if (node->type == COMMA_NODE) {
        // Recursively collect from left side first (this maintains order)
        collect_int_list_values(node->left, values, count, max_size);
        // Then add the right side value
        if (node->right && *count < max_size) {
            values[(*count)++] = node->right->name;
        }
    } else {
        // Single value node
        values[(*count)++] = node->name;
    }
}

void generate_dot_product(ast_node *node) {
    // Generate dot product calculation: left @ right
    // This creates a temporary variable and calculates the sum
    int temp_id = temp_var_count++;
    
    // Get vector sizes - assume both vectors have same size for now
    symbol *left_sym = NULL;
    int vec_size = 0;
    
    if (node->left->type == ID_NODE) {
        left_sym = get_symbol(node->left->name);
        if (left_sym && left_sym->type == VEC_TYPE) {
            vec_size = left_sym->size;
        }
    } else if (node->left->type == VEC_LITERAL_NODE) {
        // A bit of a hack, we don't know the size of the literal here easily.
        // We'll assume a size, or we need to pass it down the AST.
        // For now, let's assume the size is known from the other operand if it's a variable.
        if(node->right->type == ID_NODE) {
            symbol *right_sym = get_symbol(node->right->name);
            if(right_sym && right_sym->type == VEC_TYPE) {
                vec_size = right_sym->size;
            }
        }
    }


    
    // Generate inline dot product calculation
    fprintf(output_file, "({int dot_sum_%d = 0; for(int dot_i_%d = 0; dot_i_%d < %d; dot_i_%d++) { dot_sum_%d += ", 
            temp_id, temp_id, temp_id, vec_size, temp_id, temp_id);
    
    generate_expression(node->left);
    fprintf(output_file, "[dot_i_%d] * ", temp_id);
    generate_expression(node->right);
    fprintf(output_file, "[dot_i_%d]; } dot_sum_%d; })", temp_id, temp_id);
}

void generate_print_expressions(ast_node *node) {
    // Handle comma-separated expressions in print statements
    if (node->type == COMMA_NODE) {
        generate_print_expressions(node->left);
        fprintf(output_file, "    printf(\", \");\n");
        generate_print_expressions(node->right);
    } else {
        // Print expression result
        fprintf(output_file, "    printf(\"%%d\", ");
        generate_expression(node);
        fprintf(output_file, ");\n");
    }
}
