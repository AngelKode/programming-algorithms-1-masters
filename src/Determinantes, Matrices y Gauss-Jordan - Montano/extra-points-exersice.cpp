#include <stdio.h>

int main() {
    const int fixedSize = 2;
    double matrix[fixedSize][fixedSize];

    printf("Ingrese los valores para la matrix [%d][%d]\n", fixedSize, fixedSize);

    for (int rowIndex = 0; rowIndex < fixedSize; rowIndex++) {
        for (int columnIndex = 0; columnIndex < fixedSize; columnIndex++) {
            printf("Ingrese el valor [%d][%d]: ", rowIndex + 1, columnIndex + 1);

            if (scanf("%lf", &matrix[rowIndex][columnIndex]) != 1) {
                printf("Error al obtener los datos.\n");
                return 0;
            }
        }
    }

    //Calculamos la determinante para poder obtener la inversa
    const double determinat = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if (determinat == 0) {
        printf("La determinante ingresada no tiene matriz inversa debido a que el valor de la determinante es igual a %lf\n", determinat);
        return 0;
    }
    printf("Valor de la determinante: %lf\n", determinat);

    //Con la determinante != de 0 aplicamos la formula
    double invDeterminant[fixedSize][fixedSize];

    //Intercambiamos los elementos de la diagonal principal
    invDeterminant[0][0] = matrix[1][1];
    invDeterminant[1][1] = matrix[0][0];

    //Cambiamos el signo de los elementos de la diagonal no principal (multiplicamos por - 1)
    invDeterminant[0][1] = matrix[0][1] * -1;
    invDeterminant[1][0] = matrix[1][0] * -1;

    //Multiplicamos todos los elementos por 1 / det y vamos mostrando los datos
    printf("Matriz inversa de la matriz ingresada:\n");
    for (int rowIndex = 0; rowIndex < fixedSize; rowIndex++) {
        printf("[");
        for (int columnIndex = 0; columnIndex < fixedSize; columnIndex++) {
            invDeterminant[rowIndex][columnIndex] *= (1 / determinat);
            printf("%.2lf", invDeterminant[rowIndex][columnIndex]);
            printf(" ");
        }
        printf("]\n");
    }

    //Con la matriz inversa, la multiplicamos para validar si obtenemos la matriz de identidad o no
    double resultInvXMatrix[fixedSize][fixedSize];//Es de tamaño 2x2 ya que el tamaño es igual y no hay cambio en las dimensiones

    //Recorremos la matriz inicial
    for (int currentRowIndex = 0; currentRowIndex < fixedSize; currentRowIndex++) {
        //Recorremos la matriz inversa
        for (int currentColumnIndexOperation = 0; currentColumnIndexOperation < fixedSize; currentColumnIndexOperation++) {
            double currentSum = 0L;
            //Hacemos la operacion de multiplicar renglon-currentRowIndex * todas las columnas currentColumnIndexOperation
            for (int operationsIndex = 0; operationsIndex < fixedSize; operationsIndex++) {
                currentSum += matrix[currentRowIndex][operationsIndex] * invDeterminant[operationsIndex][currentColumnIndexOperation];
            }

            resultInvXMatrix[currentRowIndex][currentColumnIndexOperation] = currentSum;
        }
    }

    //Validamos si el resultado nos da la matriz de identidad
    printf("Resultado de multiplicar la Matriz * Inv(Matriz): \n");
    for (int rowIndex = 0; rowIndex < fixedSize; rowIndex++) {
        printf("[");
        for (int columnIndex = 0; columnIndex < fixedSize; columnIndex++) {
            printf("%.2lf ", resultInvXMatrix[rowIndex][columnIndex]);
        }
        printf("]\n");
    }

    //Validamos si el resultado de la multiplicacion nos da la matriz de identidad, es decir, la diagonal en 1 y todos los demas elementos en 0
    if (resultInvXMatrix[0][0] != 1L || resultInvXMatrix[1][1] != 1L) {
        printf("La matriz inversa no fue calculada de manera correcta.\n");
        return 0;
    }

    if (resultInvXMatrix[0][1] != 0L || resultInvXMatrix[1][0] != 0L) {
        printf("La matriz inversa no fue calculada de manera correcta.\n");
        return 0;
    }

    printf("La matriz inversa fue calculada correctamente\n");
    return 0;
}