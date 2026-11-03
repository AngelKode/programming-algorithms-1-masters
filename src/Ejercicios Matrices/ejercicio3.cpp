/*
 *Realizar un programa que llene una matriz cuadrada de dimensión igual o mayor a 3,
 *obtener de esa matriz la suma de los numeros que estan en el borde.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    const int minIntegerMatrixValue = 1;
    int maxIntegerMatrixValue = 0, matrixDimension = 0;

    do {
        printf("****************************************************\n\n");
        if (matrixDimension < 3) {
            printf("Ingrese el valor N, para la matriz NxN: ");
            scanf("%d", &matrixDimension);
        }

        if (maxIntegerMatrixValue <= minIntegerMatrixValue) {
            printf("Ingrese el maximo valor aleatorio para generar la matriz. El rango sera de 1 a Y, donde Y es su numero ingresado: ");
            scanf("%d", &maxIntegerMatrixValue);
        }

        if (matrixDimension < 3) {
            printf("Ingrese un valor mayor o igual a 3 para N\n");
        }

        if (maxIntegerMatrixValue <= minIntegerMatrixValue) {
            printf("Ingrese un valor mayor a 1 para Y\n");
        }
        printf("****************************************************\n");
    }while (matrixDimension < 3 || (maxIntegerMatrixValue <= minIntegerMatrixValue));

    srand(time(NULL));
    int matrix[matrixDimension][matrixDimension];

    printf("Matriz generada: \n");
    for (int rowIndex = 0; rowIndex < matrixDimension; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixDimension; columnIndex++) {
            matrix[rowIndex][columnIndex] = (rand() % maxIntegerMatrixValue) + 1;
            printf("  %d  ", matrix[rowIndex][columnIndex]);
        }
        printf("\n");
    }

    int borderMatrixSum = 0;
    for (int rowIndex = 1; rowIndex < matrixDimension - 1; rowIndex++) {
        for (int columnIndex = 1; columnIndex < matrixDimension - 1; columnIndex++) {
            //Sumamos la primer y ultima fila, de la segunda capa
            if (rowIndex == 1 || rowIndex == (matrixDimension - 2)) {
               borderMatrixSum += matrix[rowIndex][columnIndex];
                continue; //Para no sumar 2 veces elementos como 0,0 2 veces
            }
            //Sumamos la primer y ultima columna de la segunda capa
            if (columnIndex == 1 || columnIndex == (matrixDimension - 2)) {
                borderMatrixSum += matrix[rowIndex][columnIndex];
            }
        }
    }

    printf("\n");
    printf("La suma de los elementos del segundo borde es igual a: %d\n", borderMatrixSum);
    return 0;
}
