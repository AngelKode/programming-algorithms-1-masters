/*
 *
Crear un programa que obtenga mediante el metodo de Gauss-Jordan la inversa de la siguiente matriz:
1 2
1 1
El programa debe:
Construir la matriz aumentada formada por la matriz original y la matriz identidad.
Imprimir la matriz aumentada inicial.
Aplicar las operaciones elementales necesarias.
Imprimir la matriz reducida final.
Mostrar la matriz inversa.

*/
#include <stdio.h>
#include <math.h>

#define N 2
#define COLS (2 * N)

void printMatrix(double matrix[N][COLS]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j == N) {
                printf(" | ");
            }
            double value = matrix[i][j];
            if (fabs(value) < 1e-9) {
                value = 0.0;
            }
            printf("%8.3f ", value);
        }
        printf("\n");
    }
    printf("\n");
}

int gaussJordan(double matrix[N][COLS]) {
    for (int pivotRow = 0; pivotRow < N; pivotRow++) {
        if (fabs(matrix[pivotRow][pivotRow]) < 1e-9) {
            int swapRow = -1;
            for (int k = pivotRow + 1; k < N; k++) {
                if (fabs(matrix[k][pivotRow]) > 1e-9) {
                    swapRow = k;
                    break;
                }
            }
            if (swapRow == -1) {
                return 0;
            }
            for (int j = 0; j < COLS; j++) {
                double temp = matrix[pivotRow][j];
                matrix[pivotRow][j] = matrix[swapRow][j];
                matrix[swapRow][j] = temp;
            }
            printf("R%d <-> R%d\n", pivotRow + 1, swapRow + 1);
            printMatrix(matrix);
        }

        double pivot = matrix[pivotRow][pivotRow];
        if (fabs(pivot - 1.0) > 1e-9) {
            for (int j = 0; j < COLS; j++) {
                matrix[pivotRow][j] /= pivot;
            }
            printf("R%d = R%d / %.3f\n", pivotRow + 1, pivotRow + 1, pivot);
            printMatrix(matrix);
        }

        for (int i = 0; i < N; i++) {
            if (i == pivotRow) {
                continue;
            }
            double factor = matrix[i][pivotRow];
            if (fabs(factor) < 1e-9) {
                continue;
            }
            for (int j = 0; j < COLS; j++) {
                matrix[i][j] -= factor * matrix[pivotRow][j];
            }
            printf("R%d = R%d - (%.3f)R%d\n", i + 1, i + 1, factor, pivotRow + 1);
            printMatrix(matrix);
        }
    }
    return 1;
}

int main(void) {
    double original[N][N] = {
        {1, 2},
        {1, 1}
    };

    double augmented[N][COLS];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            augmented[i][j] = original[i][j];
            if (i == j) {
                augmented[i][j + N] = 1;
            } else {
                augmented[i][j + N] = 0;
            }
        }
    }

    printf("Matriz aumentada inicial [A | I]:\n");
    printMatrix(augmented);

    printf("Operaciones elementales:\n");
    if (!gaussJordan(augmented)) {
        printf("La matriz no es invertible.\n");
        return 1;
    }

    printf("Matriz reducida final [I | A^-1]:\n");
    printMatrix(augmented);

    printf("Matriz inversa A^-1:\n");
    for (int i = 0; i < N; i++) {
        for (int j = N; j < COLS; j++) {
            printf("%8.3f ", augmented[i][j]);
        }
        printf("\n");
    }
    return 0;
}

