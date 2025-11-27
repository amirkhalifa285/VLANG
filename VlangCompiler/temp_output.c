#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x = 2;
    int v1[6];
    for(int i = 0; i < 6; i++) v1[i] = (2 * x);
    int v2[6] = {1, 1, 2, 2, 3, 3};
    printf("V1<dot>V2: %d\n", ({int dot_sum_0 = 0; for(int dot_i_0 = 0; dot_i_0 < 6; dot_i_0++) { dot_sum_0 += v1[dot_i_0] * v2[dot_i_0]; } dot_sum_0; }));
    int y = v2[4];
    int i = 0;
    for (int loop_var_0 = 0; loop_var_0 < y; loop_var_0++) {
    v1[i] = i;
    i = (i + 1);
    }
    printf("v1 is: [%d, %d, %d, %d, %d, %d]\n", v1[0], v1[1], v1[2], v1[3], v1[4], v1[5]);
    printf("v2 indexed: %d\n", v2[v1]);
    printf("that reversed: %d\n", v2[v1[/* vector literal */]]);
    int v3[6];
    for(int i = 0; i < 6; i++) v3[i] = v1[i] + v2[i];
    printf(": %d\n", v2[(({int dot_sum_1 = 0; for(int dot_i_1 = 0; dot_i_1 < 0; dot_i_1++) { dot_sum_1 += /* vector literal */[dot_i_1] * v3[dot_i_1]; } dot_sum_1; }) / 10)]);
    int a[3] = {10, 0, 20};
    i = 0;
    for (int loop_var_1 = 0; loop_var_1 < 3; loop_var_1++) {
    if (({int dot_sum_2 = 0; for(int dot_i_2 = 0; dot_i_2 < 3; dot_i_2++) { dot_sum_2 += a[dot_i_2] * /* vector literal */[dot_i_2]; } dot_sum_2; })) {
    printf("Rotate: %d\n", i);
    for(int i = 0; i < 3; i++) a[i] = a[/* vector literal */];
    i = (i + 1);
    }
    }
    int z[4];
    for(int i = 0; i < 4; i++) z[i] = 10;
    for(int i = 0; i < 4; i++) z[i] = ((z + /* vector literal */) / 2);
    for(int i = 0; i < 4; i++) z[i] = ((z - 3) + /* vector literal */);
    printf("z is: [%d, %d, %d, %d]\n", z[0], z[1], z[2], z[3]);
    printf("z summed: %d\n", ({int dot_sum_3 = 0; for(int dot_i_3 = 0; dot_i_3 < 4; dot_i_3++) { dot_sum_3 += z[dot_i_3] * /* vector literal */[dot_i_3]; } dot_sum_3; }));
    return 0;
}
