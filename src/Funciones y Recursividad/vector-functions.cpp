#include <iostream>

int getLargest(int numbers[], int size);
int getSmallest(int numbers[], int size);
double calculateAverage(int numbers[], int size);
int countEven(int numbers[], int size);
int countOdd(int numbers[], int size);
bool isPrime(int number);
int countPrimes(int numbers[], int size);
int getSecondLargest(int numbers[], int size);
int mostFrequentNumber(int numbers[], int size);

int main() {
    int integersToEnter = 0;
    printf("Inserte la cantidad de numeros que quieres insertar: ");
    scanf("%d", &integersToEnter);

    if (integersToEnter < 1) {
        printf("[ERROR]. Debes ingresar un valor mayor o igual a 1");
        return 0;
    }

    int numberVector[integersToEnter];
    for(int enteredNumber = 0; enteredNumber < integersToEnter; enteredNumber++) {
        printf("Ingresa el numero %d: ", enteredNumber + 1);
        scanf("%d", &numberVector[enteredNumber]);
    }

    printf("El numero mas grande: %d \n", getLargest(numberVector, integersToEnter));
    printf("El 2o numero mas grande: %d\n", getSecondLargest(numberVector, integersToEnter));
    printf("El numero menos grande: %d\n", getSmallest(numberVector, integersToEnter));
    printf("El promedio de los datos es: %.2f\n", calculateAverage(numberVector, integersToEnter));
    printf("Cantidad de numeros pares: %d\n", countEven(numberVector, integersToEnter));
    printf("Cantidad de numeros impares %d\n", countOdd(numberVector, integersToEnter));
    printf("Cantidad de numeros primos: %d\n", countPrimes(numberVector, integersToEnter));
    printf("Numero mas repetido: %d\n", mostFrequentNumber(numberVector, integersToEnter));
}

int getLargest(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }
    int largest = numbers[0];
    for (int numberIndex = 1; numberIndex < size; numberIndex++) {
        if (numbers[numberIndex] <= largest) {
            continue;
        }
        largest = numbers[numberIndex];
    }
    return largest;
}
int getSecondLargest(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }
    int biggest = getLargest(numbers, size);

    int secondLargest = numbers[0];
    for (int numberIndex = 1; numberIndex < size; numberIndex++) {
        if (numbers[numberIndex] <= secondLargest) {
            continue;
        }
        if (numbers[numberIndex] > secondLargest && numbers[numberIndex] != biggest) {
            secondLargest = numbers[numberIndex];
        }
    }
    return secondLargest;
}

int getSmallest(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }
    int smallest = numbers[0];
    for (int numberIndex = 1; numberIndex < size; numberIndex++) {
        if (numbers[numberIndex] >= smallest) {
            continue;
        }
        smallest = numbers[numberIndex];
    }
    return smallest;
}
double calculateAverage(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }
    double sum = 0;
    for(int numberIndex = 0; numberIndex < size; numberIndex++) {
        sum += numbers[numberIndex];
    }
    return sum / size;
}
int countEven(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }
    int evenCount = 0;
    for(int numberIndex = 0; numberIndex < size; numberIndex++) {
        if (numbers[numberIndex] % 2 != 0) {
            continue;
        }
        evenCount++;
    }
    return evenCount;
}
int countOdd(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }
    int oddCount = 0;
    for(int numberIndex = 0; numberIndex < size; numberIndex++) {
        if (numbers[numberIndex] % 2 == 0) {
            continue;
        }
        oddCount++;
    }
    return oddCount;
}
bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }

    if (number == 2) {
        return true;
    }

    for(int currentNumber = 2; currentNumber < number; currentNumber++) {
        if (number % currentNumber == 0) {
            return false;
        }
    }
    return true;
}
int countPrimes(int numbers[], int size) {
    int primesCount = 0;
    if (size < 1) {
        return 0;
    }
    for (int currentNumber = 0; currentNumber < size; currentNumber++) {
        if (!isPrime(numbers[currentNumber])) {
            continue;
        }
        primesCount++;
    }
    return primesCount;
}
int mostFrequentNumber(int numbers[], int size) {
    if (size < 1) {
        return 0;
    }

    if (size == 1) {
        return numbers[0];
    }

    int mostFrequentNumber = 0;
    int mostFrequentNumberCount = 0;
    int prevNumber = INT_MIN; //Para evitar un numero que pudiera ser ingresado, como el 0 o asi
    int prevNumberCount = 0;
    for (int currentNumberIndex = 0; currentNumberIndex < size; currentNumberIndex++) {
        int currentNumber = numbers[currentNumberIndex];
        int currentNumberCount = 0;
        //Recorremos del elemento actual al siguiente
        for (int currentNumberIndexAux = currentNumberIndex + 1; currentNumberIndexAux < size; currentNumberIndexAux++) {
            if (currentNumber != numbers[currentNumberIndexAux]) {
                continue;
            }
            //No evita cuando no estan en secuencia, pero ahorra ciertas operaciones
            if (currentNumber == prevNumber) {
                continue;
            }
            currentNumberCount++;
        }

        //En caso de que sea el primer elemento, no hay uno previo
        //O si el conteo actual no es mayor al previo que tenemos como mayor, no actualizamos los datos
        if (currentNumberIndex != 0 && currentNumberCount <= prevNumberCount) {
           continue;
        }
        //Si no se cumple lo anterior, actualizamos los datos ya sea porque estamos comparando el primer elemento
        //O el conteo actual supera al conteo previo
        mostFrequentNumber = currentNumber;
        mostFrequentNumberCount = currentNumberCount;
        prevNumberCount = currentNumberCount;
        prevNumber = currentNumber;
    }

    return mostFrequentNumber;
}