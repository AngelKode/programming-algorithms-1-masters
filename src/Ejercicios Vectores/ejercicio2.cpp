//Dado un vector de 100 numeros, generar numeros aleatorios entre 1 y 20
//e indicar cuantas veces aparece cada numero repetido en el vector
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define MAX_INTEGER_TO_GENERATE 100
#define MAX_INTEGER_VALUE 20
#define MIN_INTEGER_VALUE 1

int main() {
    //Creamos el vector de los numeros aleatorios
    int repeatedNumbersVector[MAX_INTEGER_TO_GENERATE] = {};

    //Y el vector donde iremos guardando los numeros que ya comparamos
    int checkedNumbersVector[MAX_INTEGER_VALUE] = {}; //De tamaño 20, ya que es el maximo de numeros no repetidos

    //Aqui guardaremos las ocurrencias, la posicion 0 es la cantidad de ocurrencias para el elemento 0 del vector anterior y asi.
    int checkedNumbersVectorCount[MAX_INTEGER_VALUE] = {}; //De tamaño 20, ya que es el maximo de numeros no repetidos

    int currentNumber = 0;
    int isCheckedFlag = 0;
    int checkedNumberCount = 0;

    //Generamos la semilla para el numero aleatorio
    srand(time(0));

    //Generamos la primer lista con los 100 números aleatorios
    for (int generatedNumberIndex = 0; generatedNumberIndex < MAX_INTEGER_TO_GENERATE; generatedNumberIndex++) {
        //En cada iteracion generamos un numero aleatorio entre el 1 y 20, y lo asignamos al vector
        repeatedNumbersVector[generatedNumberIndex] = rand() % MAX_INTEGER_VALUE + MIN_INTEGER_VALUE;
    }

    //Imprimimos el vector generado
    printf("Lista inicial de numeros aleatorios generados \n[");
    for(int index = 0; index < MAX_INTEGER_TO_GENERATE; index++) {
        printf("%d, ", repeatedNumbersVector[index]);
    }
    printf("]\n\n\n");

    //Recorremos la lista para obtener cuantas veces se repiten los números
    for(int repeatedNumberIndex = 0; repeatedNumberIndex < MAX_INTEGER_TO_GENERATE; repeatedNumberIndex++) {
        currentNumber = repeatedNumbersVector[repeatedNumberIndex];

        //Recorremos el vector de los numeros que ya revisamos para saber si aun no se ha tomado en cuenta
        //En caso de que si, nos pasamos al siguiente numero del vector
        for(int checkedNumberIndex = 0; checkedNumberIndex < MAX_INTEGER_VALUE; checkedNumberIndex++) {
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
        for(int repeatedNumberIndexAux = 0; repeatedNumberIndexAux < MAX_INTEGER_TO_GENERATE; repeatedNumberIndexAux++) {
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

    //Ordenamos la lista de ocurrencias y la cantidad cada una
    for(int checkedNumberIndex = 0; checkedNumberIndex < checkedNumberCount; checkedNumberIndex++) {
        for(int checkedNumberIndexAux = checkedNumberIndex + 1; checkedNumberIndexAux < checkedNumberCount; checkedNumberIndexAux++) {
            //Ordenamos el numero actual respecto al anterior
            //Si el actual es menor, cambiamos posiciones
            if (checkedNumbersVector[checkedNumberIndexAux] > checkedNumbersVector[checkedNumberIndex]) {
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

    //Imprimimos las ocurrencias
    for (int checkedNumberIndex = 0; checkedNumberIndex < checkedNumberCount; checkedNumberIndex++) {
        printf("El numero %d se repite %d veces.\n", checkedNumbersVector[checkedNumberIndex], checkedNumbersVectorCount[checkedNumberIndex]);
    }
}
