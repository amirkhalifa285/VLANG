#include <iostream>
#include <cstring>
#include "runtime.hpp"
int main(){
int x = 0;
int y = 0;
int i = 0;
int v1[6] = {0};
int v2[6] = {0};
int v3[6] = {0};
int a[3] = {0};
int z[4] = {0};
x = 2;
for(int i=0; i<6; ++i) v1[i] = 2 * x;
int temp_vec_0[] = {1,1,2,2,3,3};
memcpy(v2,temp_vec_0,sizeof(int)*6);
std::cout << "V1<dot>V2: ";
std::cout << dot_product(v1,v2,6) << std::endl;
y = v2[(int)(4)];
i = 0;
for(int __i=0;__i<y;++__i){
v1[(int)(i)] = i;
i = i + 1;
}
std::cout << "v1 is: ";
print_vector("", v1, 6);
int temp_index_0[6];
vector_index_by_vector(temp_index_0,v2,v1,6);
std::cout << "v2 indexed: ";
print_vector("", temp_index_0, 6);
int temp_vec_expr_0[] = {5,4,3,2,1,0};
int temp_index_1[6];
vector_index_by_vector(temp_index_1,v1,temp_vec_expr_0,6);
int temp_index_2[6];
vector_index_by_vector(temp_index_2,v2,temp_index_1,6);
std::cout << "that reversed: ";
print_vector("", temp_index_2, 6);
int temp_vec_expr_1[6];
vector_vector_op(temp_vec_expr_1, v1, v2, 6, '+');
memcpy(v3, temp_vec_expr_1, sizeof(int)*6);
int temp_vec_expr_2[] = {2,1,0,2,2,0};
std::cout << ": ";
std::cout << v2[(int)((dot_product(temp_vec_expr_2,v3,6) / 10))] << std::endl;
int temp_vec_1[] = {10,0,20};
memcpy(a,temp_vec_1,sizeof(int)*3);
i = 0;
for(int __i=0;__i<3;++__i){
int temp_vec_expr_3[] = {1,0,0};
if(dot_product(a,temp_vec_expr_3,3)){
std::cout << "Rotate: ";
std::cout << i << " ";
print_vector("", a, 3);
int temp_vec_expr_4[] = {2,0,1};
int temp_index_3[3];
vector_index_by_vector(temp_index_3,a,temp_vec_expr_4,3);
memcpy(a, temp_index_3, sizeof(int)*3);
}
i = i + 1;
}
for(int i=0; i<4; ++i) z[i] = 10;
int temp_vec_expr_5[] = {2,4,6,8};
int temp_vec_expr_6[4];
vector_vector_op(temp_vec_expr_6, z, temp_vec_expr_5, 4, '+');
int temp_vec_expr_7[4];
vector_scalar_op(temp_vec_expr_7, (temp_vec_expr_6), 2, 4, '/');
memcpy(z, temp_vec_expr_7, sizeof(int)*4);
int temp_vec_expr_8[4];
vector_scalar_op(temp_vec_expr_8, z, 3, 4, '-');
int temp_vec_expr_9[] = {2,3,4,5};
int temp_vec_expr_10[4];
vector_vector_op(temp_vec_expr_10, temp_vec_expr_8, temp_vec_expr_9, 4, '+');
memcpy(z, temp_vec_expr_10, sizeof(int)*4);
std::cout << "z is: ";
print_vector("", z, 4);
int temp_vec_expr_11[] = {1,1,1,1};
std::cout << "z summed: ";
std::cout << dot_product(z,temp_vec_expr_11,4) << std::endl;
return 0;
}
