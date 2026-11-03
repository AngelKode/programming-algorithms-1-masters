//Crear un programa que genere 100 números aleatorios entre 1 y 50, de esos numeros deberá generar
//un segundo vector con los numeros no repetidos, puede ser en orden o en desorden.
#include <cstdio>
#include <cstdlib>
#include <ctime>
#define MAX_INTEGER_TO_GENERATE 100
#define MAX_INTEGER_VALUE 50
#define MIN_INTEGER_VALUE 1

using namespace std;
int main() {
    //Creamos ambos vectores
    int repeatedNumbersVector[MAX_INTEGER_TO_GENERATE] = {};
    int nonRepeatedNumbersVector[MAX_INTEGER_VALUE] = {};//De tamaño 50 ya que la maxima cantidad de no repetidos es 50, del 1 al 50

    int generatedNumber = 0;
    int repeatedFlag = 0;
    int currentNumber = 0;
    int nonRepeatedNumbersCount = 0;

    //Generamos la semilla para el numero aleatorio
    srand(time(0));

    //Generamos la primer lista con los 100 números aleatorios

    for (int currentGeneratedNumberIndex = 0; currentGeneratedNumberIndex < MAX_INTEGER_TO_GENERATE; currentGeneratedNumberIndex++) {
        //En cada iteracion generamos un numero aleatorio entre el 1 y 50, y lo asignamos al vector
        generatedNumber = rand() % MAX_INTEGER_VALUE + MIN_INTEGER_VALUE;
        repeatedNumbersVector[currentGeneratedNumberIndex] = generatedNumber;
    }

    //Generamos el nuevo vector unicamente con los no repetidos
    for(int currentRepeatedVectorIndex = 0; currentRepeatedVectorIndex < MAX_INTEGER_TO_GENERATE; currentRepeatedVectorIndex++) {
        currentNumber = repeatedNumbersVector[currentRepeatedVectorIndex];

        for (int currentNonRepeatedVectorIndex = 0; currentNonRepeatedVectorIndex < MAX_INTEGER_TO_GENERATE; currentNonRepeatedVectorIndex++) {
            //Si es el mismo valor, ignorar ya que es el mismo número
            if (currentRepeatedVectorIndex == currentNonRepeatedVectorIndex) {
                continue;
            }

            //Validamos si encontramos alguna coincidencia del numero actual en la lista principal
            if (currentNumber == repeatedNumbersVector[currentNonRepeatedVectorIndex]) {
                repeatedFlag = 1;
                break;
            }
        }

        //Si la bandera esta activada, no agregamos el numero a la lista
        if(repeatedFlag == 1) {
            repeatedFlag = 0;
            continue;
        }

        //En caso contrario, agregamos el numero a la nueva lista y aumentamos en 1 el contador de la cantidad de no repetidos
        nonRepeatedNumbersVector[nonRepeatedNumbersCount] = currentNumber;
        nonRepeatedNumbersCount++;
    }

    //Imprimimos ambos vectores
    printf("Lista inicial de numeros aleatorios generados \n[");
    for(int index = 0; index < MAX_INTEGER_TO_GENERATE; index++) {
        printf("%d, ", repeatedNumbersVector[index]);
    }
    printf("]\n");

    printf("\nNo repetidos \n[");
    for(int index = 0; index < nonRepeatedNumbersCount; index++) {
        printf("%d, ", nonRepeatedNumbersVector[index]);
    }
    printf("]\n");

    return 0;
}
