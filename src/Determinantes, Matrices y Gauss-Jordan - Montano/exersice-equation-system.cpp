/*
*Crear un programa que resuelva mediante el metodo de Gauss-Jordan el siguiente sistema de ecuaciones:
x − 2y − z = −6
x + y + z = 2
2x + 2y + z = 3
El programa debe:
Construir la matriz aumentada del sistema.
Imprimir la matriz aumentada inicial.
Aplicar el metodo de Gauss-Jordan.
Imprimir la matriz reducida final.
Mostrar los valores obtenidos de x, y y z.
 *
 */
#include <stdio.h>
#include <math.h>

#define N 3
#define COLS (N + 1)

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
    double augmented[N][COLS] = {
        {1, -2, -1, -6},
        {1,  1,  1,  2},
        {2,  2,  1,  3}
    };

    printf("Matriz aumentada inicial [A | b]:\n");
    printMatrix(augmented);

    printf("Operaciones elementales:\n");
    if (!gaussJordan(augmented)) {
        printf("El sistema no tiene solucion unica.\n");
        return 1;
    }

    printf("Matriz reducida final:\n");
    printMatrix(augmented);

    printf("Solucion:\n");
    printf("x = %.3f\n", augmented[0][N]);
    printf("y = %.3f\n", augmented[1][N]);
    printf("z = %.3f\n", augmented[2][N]);
    return 0;
}
