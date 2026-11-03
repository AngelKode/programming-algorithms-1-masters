/*
Crear una función que reciba una matriz de 2×2 y regrese su determinante.
Utilizar la siguiente matriz:
2 1
1 4
El programa debe imprimir la matriz y su determinante.

Crear una función que calcule el determinante de una matriz de 3×3. Probar la función con las siguientes matrices:
Matriz A:
1 1 -1
0 1 1
-1 1 1
Matriz B:
3 1 2
1 4 -4
1 0 2
Matriz C:
4 0 8
5 0 7
3 1 2
El programa debe imprimir cada matriz y el determinante correspondiente.
 */

#include <stdio.h>

void calculateDeterminant2x2(int matrix[2][2]);
void calculateDeterminant3x3(int matrix[3][3]);


int main() {
    int testProblem1[2][2] = {{2,1},{1,4}};
    int testProblem2_A[3][3] = {{1,1,-1},{0,1,1},{-1, 1, 1}};
    int testProblem2_B[3][3] = {{3,1,2},{1,4,-4},{1, 0, 2}};
    int testProblem2_C[3][3] = {{4,0,8},{5,0,7}, {3,1,2}};

    printf("Test Problema 1:\n");
    calculateDeterminant2x2(testProblem1);
    printf("Test Problema 2 con Matriz A:\n");
    calculateDeterminant3x3(testProblem2_A);
    printf("Test Problema 2 con Matriz B:\n");
    calculateDeterminant3x3(testProblem2_B);
    printf("Test Problema 2 con Matriz C:\n");
    calculateDeterminant3x3(testProblem2_C);
}

void calculateDeterminant2x2(int matrix[2][2]) {
    for (int rowIndex = 0; rowIndex < 2; rowIndex++) {
        printf("[");
        for (int columnIndex = 0; columnIndex < 2; columnIndex++) {
            printf("%d ", matrix[rowIndex][columnIndex]);
        }
        printf("]\n");
    }
    int determinant =  matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    printf("El valor de la determinante es: %d\n\n", determinant);
}

void calculateDeterminant3x3(int matrix[3][3]) {
    for (int rowIndex = 0; rowIndex < 3; rowIndex++) {
        printf("[");
        for (int columnIndex = 0; columnIndex < 3; columnIndex++) {
            printf("%d ", matrix[rowIndex][columnIndex]);
        }
        printf("]\n");
    }
    int determinant = 0;
    for (int blockedIndex = 0; blockedIndex < 3; blockedIndex++) {
        //Usamos % 3 para obtener el indice que corresponda dependiendo blockedIndex
        //Por ejemplo para el 0, ambos resultados son 1 y 2
        //Para 1, son 2 y 0
        //Y asi siempre obtenemos las submatrices
        int firstIndex = (blockedIndex + 1) % 3;
        int secondIndex = (blockedIndex + 2) % 3;
        determinant += matrix[0][blockedIndex] * (matrix[1][firstIndex] * matrix[2][secondIndex] - matrix[1][secondIndex] * matrix[2][firstIndex]);
    }
    printf("El valor de la determinante es: %d\n\n", determinant);
}
