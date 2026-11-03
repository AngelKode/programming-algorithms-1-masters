//Dado un vector de 100 numeros, generar numeros aleatorios entre 1 y 1000
//llenar el vector con esos numeros y llengar un segundo y tercer vector,
//el segundo vector con los numeros pares del vector original y el tercer vector con los numeros impares del vector original.
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define MAX_INTEGER_TO_GENERATE 100
#define MAX_INTEGER_VALUE 1000
#define MIN_INTEGER_VALUE 1

int main() {
    //Creamos el vector de los numeros aleatorios
    int repeatedNumbersVector[MAX_INTEGER_TO_GENERATE] = {};

    //Creamos el vector para los numeros pares
    int evenNumbersVector[MAX_INTEGER_TO_GENERATE] = {};

    //Creamos el vector para los numeros impares
    int oddNumbersVector[MAX_INTEGER_TO_GENERATE] = {};

    int evenNumbersCount = 0, oddNumbersCount = 0;

    //Creamos la semilla para la generacion de numeros aleatorios
    srand(time(0));

    //Generamos la primer lista con los 100 números aleatorios
    for (int generatedNumberIndex = 0; generatedNumberIndex < MAX_INTEGER_TO_GENERATE; generatedNumberIndex++) {
        //En cada iteracion generamos un numero aleatorio entre el 1 y 1000, y lo asignamos al vector
        int generatedNumber = rand() % MAX_INTEGER_VALUE + MIN_INTEGER_VALUE;
        repeatedNumbersVector[generatedNumberIndex] = generatedNumber;

        //Si el numero es par lo agregamos a la lista de pares
        if(generatedNumber % 2 == 0) {
            evenNumbersVector[evenNumbersCount] = generatedNumber;
            evenNumbersCount++;
        }
        //Caso contrario, al de impares
        if(generatedNumber % 2 != 0) {
            oddNumbersVector[oddNumbersCount] = generatedNumber;
            oddNumbersCount++;
        }
    }

    //Imprimimos la lista de los numeros generados
    printf("Lista de numeros aleatorios GENERADOS:\n[");
    for(int generatedNumberIndex = 0; generatedNumberIndex < MAX_INTEGER_TO_GENERATE; generatedNumberIndex++) {
        printf("%d, ", repeatedNumbersVector[generatedNumberIndex]);
    }
    printf("]\n\n");

    //Imprimimos la lista de pares
    printf("Lista de numeros aleatorios - PARES:\n[");
    for(int evenIndex = 0; evenIndex < evenNumbersCount; evenIndex++) {
        printf("%d, ", evenNumbersVector[evenIndex]);
    }
    printf("]\n\n");

    //Imprimimos la lista de impares
    printf("Lista de numeros aleatorios - IMPARES:\n[");
    for(int oddIndex = 0; oddIndex < oddNumbersCount; oddIndex++) {
        printf("%d, ", oddNumbersVector[oddIndex]);
    }
    printf("]\n\n");
}
