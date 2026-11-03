//Hacer un programa que cree un vector de N posiciones dadas por el
//usuario, es decir, el usuario da la dimensión del vector.
//Generar numeros aleatorios entre el 1 y 100, con base en esos datos
//obtener la media, moda, mediana, varianza y desviación estándar
//se puede usar sqrt, pow,

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define MAX_INTEGER_VALUE 100
#define MIN_INTEGER_VALUE 1

int main() {

    int userSizeEnteredValue = 0;
    printf("Ingrese la cantidad de elementos a generar: ");
    scanf("%d", &userSizeEnteredValue);

    //Creamos el vector de los numeros aleatorios
    int repeatedNumbersVector[userSizeEnteredValue];

    //Y el vector donde iremos guardando los numeros que ya comparamos
    int checkedNumbersVector[userSizeEnteredValue]; //De tamaño N

    //Aqui guardaremos las ocurrencias, la posicion 0 es la cantidad de ocurrencias para el elemento 0 del vector anterior y asi.
    int checkedNumbersVectorCount[userSizeEnteredValue]; //De tamaño N

    int currentNumber = 0;
    int isCheckedFlag = 0;
    int checkedNumberCount = 0;

    //Generamos la semilla para el numero aleatorio
    srand(time(0));

    //Generamos la primer lista con los 100 números aleatorios
    for (int generatedNumberIndex = 0; generatedNumberIndex < userSizeEnteredValue; generatedNumberIndex++) {
        //En cada iteracion generamos un numero aleatorio entre el 1 y 100, y lo asignamos al vector
        repeatedNumbersVector[generatedNumberIndex] = rand() % MAX_INTEGER_VALUE + MIN_INTEGER_VALUE;
    }

    //Imprimimos el vector generado
    printf("Lista inicial de numeros aleatorios generados \n[");
    for(int index = 0; index < userSizeEnteredValue; index++) {
        printf("%d, ", repeatedNumbersVector[index]);
    }
    printf("]\n\n");



    //Recorremos la lista para obtener cuantas veces se repiten los números
    for(int repeatedNumberIndex = 0; repeatedNumberIndex < userSizeEnteredValue; repeatedNumberIndex++) {
        currentNumber = repeatedNumbersVector[repeatedNumberIndex];

        //Recorremos el vector de los numeros que ya revisamos para saber si aun no se ha tomado en cuenta
        //En caso de que si, nos pasamos al siguiente numero del vector
        for(int checkedNumberIndex = 0; checkedNumberIndex < userSizeEnteredValue; checkedNumberIndex++) {
            if (checkedNumbersVector[checkedNumberIndex] == currentNumber) {
                isCheckedFlag = 1;
                break;
            }
        }

        //Si es 1, no hacemos el conteo y nos pasamos al siguiente elemento
        if (isCheckedFlag == 1) {
           isCheckedFlag = 0;
            continue;
        }

        //Caso contrario, realizamos el conteo de las repeticiones
        int occurrences = 1;

        for(int repeatedNumberIndexAux = 0; repeatedNumberIndexAux < userSizeEnteredValue; repeatedNumberIndexAux++) {
            //Si ambos contadores tienen el mismo valor lo omitimos, para evitar contar el mismo 2 veces
            if (repeatedNumberIndex == repeatedNumberIndexAux) {
                continue;
            }

            //Si encontramos una coincidencia, aumentamos en 1 las ocurrencias
            if (repeatedNumbersVector[repeatedNumberIndexAux] == currentNumber) {
                occurrences++;
            }
        }

        //Agregamos a la lista de ocurrencias el valor obtenido
        //Y el numero a el vector de números que ya verificamos
        checkedNumbersVectorCount[checkedNumberCount] = occurrences;
        checkedNumbersVector[checkedNumberCount] = currentNumber;
        checkedNumberCount++;
    }



    //Ordenamos la lista de ocurrencias y la cantidad cada una de mayor a menor
    for(int checkedNumberIndex = 0; checkedNumberIndex < checkedNumberCount; checkedNumberIndex++) {
        for(int checkedNumberIndexAux = checkedNumberIndex + 1; checkedNumberIndexAux < checkedNumberCount; checkedNumberIndexAux++) {
            //Ordenamos el numero actual respecto al anterior
            //Si el actual es mayor, cambiamos posiciones
            if (checkedNumbersVectorCount[checkedNumberIndexAux] < checkedNumbersVectorCount[checkedNumberIndex]) {
                continue;//Caso contrario, nos saltamos la operacion
            }

            int biggerNumber = checkedNumbersVector[checkedNumberIndex]; //El numero
            int biggerNumberOccurences = checkedNumbersVectorCount[checkedNumberIndex]; //Las veces que esta repetido el numero

            //Ordenamos el vector de numeros
            checkedNumbersVector[checkedNumberIndex] = checkedNumbersVector[checkedNumberIndexAux];
            checkedNumbersVector[checkedNumberIndexAux] = biggerNumber;

            //Ordenamos el vector de ocurrencias para que coincidan
            checkedNumbersVectorCount[checkedNumberIndex] = checkedNumbersVectorCount[checkedNumberIndexAux];
            checkedNumbersVectorCount[checkedNumberIndexAux] = biggerNumberOccurences;
        }
    }

    //Ordenamos los numeros de menor a mayor para poder obtener la mediana
    for(int checkedNumberIndex = 0; checkedNumberIndex < userSizeEnteredValue; checkedNumberIndex++) {
        for(int checkedNumberIndexAux = checkedNumberIndex + 1; checkedNumberIndexAux < checkedNumberCount; checkedNumberIndexAux++) {
            //Ordenamos el numero actual respecto al anterior
            //Si el actual es mayor, cambiamos posiciones
            if (repeatedNumbersVector[checkedNumberIndexAux] > repeatedNumbersVector[checkedNumberIndex]) {
                continue;//Caso contrario, nos saltamos la operacion
            }

            int biggerNumber = repeatedNumbersVector[checkedNumberIndex]; //El numero

            //Ordenamos el vector de numeros
            repeatedNumbersVector[checkedNumberIndex] = repeatedNumbersVector[checkedNumberIndexAux];
            repeatedNumbersVector[checkedNumberIndexAux] = biggerNumber;
        }
    }

    //Ya con la lista de repetidos,la frecuencia de repetición y la lista ordenada de elementos, obtenemos
    //Media
    int totalSum = 0;
    for (int checkedNumberIndex = 0; checkedNumberIndex < checkedNumberCount; checkedNumberIndex++) {
        int value = checkedNumbersVector[checkedNumberIndex];
        int frequency = checkedNumbersVectorCount[checkedNumberIndex];
        totalSum += (value * frequency);
    }
    float totalAverage = ((float)totalSum / (float)userSizeEnteredValue);
    printf("El valor de la Media es: %.2f\n", totalAverage);

    //Moda
    //Validamos que haya más de 1 dato
    if (checkedNumberCount >= 2) {
        //Vector donde iremos agregando las ocurrencias
        int mostRepeatedNumbersList[checkedNumberCount];
        mostRepeatedNumbersList[0] = checkedNumbersVector[0];
        int sameFrequencyNumbersCount = 1;

        for (int numberIndex = 1; numberIndex < checkedNumberCount; numberIndex++) {
            if (checkedNumbersVectorCount[numberIndex] < checkedNumbersVectorCount[0]) {
                break;//Nos salimos del ciclo, ya no hay otro elemento con la misma frecuencia
            }

            //Caso contrario, lo agregamos a la lista
            mostRepeatedNumbersList[sameFrequencyNumbersCount] = checkedNumbersVector[numberIndex];
            sameFrequencyNumbersCount++;
        }
        //Si solo hay 1 elemento, es Moda normal
        //Si solo hay 2 elementos, es BIMODAL
        //Caso contrario es MULTIMODAL
        if (sameFrequencyNumbersCount == 1) {
            printf("La distribucion es de tipo unimodal con valor: [%d] con frecuencia %d\n", checkedNumbersVector[0],checkedNumbersVectorCount[0]);
        }else if (sameFrequencyNumbersCount == 2) {
            printf("La distribucion es de tipo bimodal con valores: [%d,%d] con frecuencia [%d]\n", mostRepeatedNumbersList[0],mostRepeatedNumbersList[1],checkedNumbersVectorCount[0]);
        }else {
            printf("La distribucion es de tipo multimodal con valores : [");
            for (int sameFrequencyNumberIndex = 0; sameFrequencyNumberIndex < sameFrequencyNumbersCount; sameFrequencyNumberIndex++) {
                printf("%d,", mostRepeatedNumbersList[sameFrequencyNumberIndex]);
            }
            printf("] con frecuencia [%d]\n", checkedNumbersVectorCount[0]);
        }

    }else {
        //Si solo hay 1 elemento es si o si, unimodal
        printf("La distribucion es de tipo unimodal con valor: [%d] con %d frecuencia\n", checkedNumbersVector[0],checkedNumbersVectorCount[0]);
    }

    //Mediana
    //Si el tamaño ingresado por el usuario es impar, la Mediana estará justo en la posicion central
    if(userSizeEnteredValue % 2 != 0) {
        printf("La mediana es %d\n", repeatedNumbersVector[userSizeEnteredValue / 2]);
    }else {
        //Caso contrario sacamos el promedio de los 2 centrales de la lista ordenada de elementos
        int sum = repeatedNumbersVector[(userSizeEnteredValue / 2) - 1] + repeatedNumbersVector[(userSizeEnteredValue / 2)];
        printf("La mediana es %.2f\n", (float)sum / 2.0);
    }

    //Varianza
    double varianza = 0.0f;
    //Recorremos todos los elementos y le aplicamos la formula
    for(int currentNumberIndex = 0; currentNumberIndex < userSizeEnteredValue; currentNumberIndex++) {
        varianza += pow((double)repeatedNumbersVector[currentNumberIndex] - totalAverage, 2);
    }
    varianza /= (double)(userSizeEnteredValue); //Dividimos la sumatoria total entre N, que es el tamaño del vector indicado por el usuario
    printf("La varianza: %.2f\n", varianza);
    //Desviación estandar
    printf("La desviacion estandar: %.2f\n", sqrt(varianza));
}