// runtime.hpp

#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <iostream>
#include <vector>
#include <string>

void vector_scalar_op(int* dst, int* src, int val, int size, char op);
void vector_vector_op(int* dst, int* a, int* b, int size, char op);
int dot_product(int* a, int* b, int size);
void vector_index_by_vector(int* dst, int* vec, int* indices, int size);
void print_vector(const std::string& label, int* vec, int size);

#endif