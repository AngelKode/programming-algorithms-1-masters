/*
Hacer un programa de dimension NxN dada por el usuario, llenarlo con numeros aleatorios enteros
Obtener el numero Mayor
Obtener el numero menor
Obtener La media
Obtener la suma de los primos
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {

    int matrixSizeN = 0;
    int maxRandomIntegerValue = 0;
    const int minRandomIntegerValue = 1;
    do {
        if (matrixSizeN <= 0) {
            printf("Ingrese el valor N, para la matriz NxN: ");
            scanf("%d", &matrixSizeN);
        }

        if (maxRandomIntegerValue <= minRandomIntegerValue) {
            printf("Ingrese el maximo valor aleatorio para generar la matriz. El rango sera de 1 a Y, donde Y es su numero ingresado: ");
            scanf("%d", &maxRandomIntegerValue);
        }

        if (matrixSizeN <= 0) {
            printf("Ingrese un valor mayor a 0 para N\n");
        }

        if (maxRandomIntegerValue <= minRandomIntegerValue) {
            printf("Ingrese un valor mayor a 1 para Y\n");
        }
        printf("****************************************************\n");
    }while (matrixSizeN <= 0 || (maxRandomIntegerValue <= minRandomIntegerValue));

    //Inicializamos la semilla y la matriz
    srand(time(NULL));
    int coreMatrix[matrixSizeN][matrixSizeN];

    //Llenamos la matriz con numeros aleatorios
    printf("Matriz de %dx%d generada: \n", matrixSizeN, matrixSizeN);
    for (int rowIndex = 0; rowIndex < matrixSizeN; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixSizeN; columnIndex++) {
            coreMatrix[rowIndex][columnIndex] = rand() % maxRandomIntegerValue + minRandomIntegerValue;
            printf("%d ",coreMatrix[rowIndex][columnIndex]);
        }
        printf("\n");
    }

    //Obtenemos el número mayor y menor
    //Usando 2 variables para almacenar dicho dato
    int currentBiggerNumber = coreMatrix[0][0];
    int currentSmallerNumber = coreMatrix[0][0];
    //Aprovechando que vamos a recorrer toda la matriz, obtenemos la suma de todos sus elementos
    //Y la suma de todos los numeros primos
    int matrixTotalSum = 0;
    int matrixTotalPrimeNumbersSum = 0, currentNumber = 0, isPrime = 0;

    for (int rowIndex = 0; rowIndex < matrixSizeN; rowIndex++) {
        for (int columnIndex = 0; columnIndex < matrixSizeN; columnIndex++) {
            currentNumber = coreMatrix[rowIndex][columnIndex];
            //Si el numero mas grande guardado es menor al elemento actual que estamos comparando
            //actualizamos el valor del numero mas grande
            if(currentBiggerNumber < currentNumber) {
                currentBiggerNumber = currentNumber;
            }
            //Si el numero mas pequeño guardado es mayor al elemento actual que estamos comparando
            //actualizamos el valor del numero mas pequeño
            if(currentSmallerNumber > currentNumber) {
                currentSmallerNumber = currentNumber;
            }

            //Agregamos el valor actual a la suma total de toda la matriz
            matrixTotalSum += currentNumber;

            //Para el caso base, cuando se intente validar si el 1 es primo, en automatico nos saltamos la parte de analizar el numero
            if (currentNumber == 1) {
                continue;
            }

            //Calculamos si el numero actual es numero primo o no
            isPrime = 1;
            for (int numberToEvaluate = currentNumber - 1; numberToEvaluate > 1; numberToEvaluate--) {
                if (currentNumber % numberToEvaluate == 0) {//Si algun numero lo puede dividir, no es primo
                    //Actualizamos la bandera y nos salimos del ciclo para no seguir comparando
                    isPrime = 0;
                    break;
                }
            }
            //Si la bandera sigue teniendo el valor de 1, lo agregamos a la suma total de primos
            if (isPrime == 1) {
                matrixTotalPrimeNumbersSum += currentNumber;
            }
        }
    }
    printf("\n");
    printf("El numero mayor de toda la matriz es: [%d]\n", currentBiggerNumber);
    printf("El numero menor de toda la matriz es: [%d]\n", currentSmallerNumber);
    printf("La media de la matriz es: [%.2f]\n", (float)matrixTotalSum / (float)(matrixSizeN * matrixSizeN));
    printf("La suma de todos los numeros primos de la matrix es [%d]\n", matrixTotalPrimeNumbersSum);

    return 0;
}
