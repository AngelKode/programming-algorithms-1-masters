#include <iostream>
using namespace std;

int main () {
    int nFibonacciValue;
    printf("Ingresa el valor de n para imprimir n valores de Fibonacci: ");
    scanf("%d", &nFibonacciValue);

    //Manejamos el error si n vale <= 0
    if (nFibonacciValue <= 0) {
        printf("[ERROR]. El valor debe ser mayor o igual a 1\n");
        return 0;
    }

    //Empezamos de forma iterativa la obtención de los n valores de Fibonacci
    unsigned long long sumAccFibonacci = 0;
    unsigned long long k1Value = 0;
    unsigned long long k2Value = 0;
    for (int nFibonacciSequence = 0; nFibonacciSequence < nFibonacciValue; nFibonacciSequence++) {
        //Dependiendo si Fo o F1, imprimimos 0 o 1 respectivamente
        //Imprimimos el valor y lo sumamos a la variable donde vamos a ir acumulando la suma
        if (nFibonacciSequence == 0) {
            printf("0 ");
            sumAccFibonacci += 0;
            continue;
        }
        if (nFibonacciSequence == 1) {
            printf("1 ");
            sumAccFibonacci += 1;
            k2Value = 0;
            k1Value = 1;
            continue;
        }
        //En caso de que no sean los caso base de Fo = 0 o F1 = 1, usamos la formula que viene en el PDF
        //Fk = Fk - 1 + Fk - 2

        //Primero sumamos
        sumAccFibonacci = k1Value + k2Value;
        //Actualizamos k2, ahora vale lo que habia en k-1 porque ya nos recorrimos 1 lugar
        k2Value = k1Value;

        //Actualizamos k1, ahora vale el valor de la sumatoria calculada
        k1Value = sumAccFibonacci;
        printf("%lld ", sumAccFibonacci);
    }
    return 0;
}
