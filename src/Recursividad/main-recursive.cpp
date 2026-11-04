#include <iostream>

int calculatePositiveSum(int n);
int calculateFactorial(int n);
int calculatePotenceSum(int base, int potency);
int calculateSumOfDigits(int n);

int main() {
    //--------------------------------------Problema 1--------------------------------------
    int limit = 0;
    printf("-----------------------PROGRAMA 1-----------------------");
    printf("\nIngresa el numero limite: ");
    scanf("%d", &limit);

    int sumOfNumberSequence = calculatePositiveSum(10);
    printf("El resultado de sumar todos los numeros de 1 a %d es: %d", limit, sumOfNumberSequence);
    printf("\n-----------------------PROGRAMA 1-----------------------");
    //--------------------------------------Problema 1--------------------------------------

    //--------------------------------------Problema 2--------------------------------------
    int numberToCalculateFactorial = 0;
    printf("\n\n-----------------------PROGRAMA 2-----------------------");
    printf("\nIngresa el numero para calcular el factorial: ");
    scanf("%d", &numberToCalculateFactorial);
    int factorialResult = calculateFactorial(numberToCalculateFactorial);
    printf("El factorial de %d es: %d", numberToCalculateFactorial, factorialResult);
    printf("\n-----------------------PROGRAMA 2-----------------------");
    //--------------------------------------Problema 2--------------------------------------

    //--------------------------------------Problema 3--------------------------------------
    int base, potency = 0;
    printf("\n\n-----------------------PROGRAMA 3-----------------------");
    printf("\nIngresa el valor de la base: ");
    scanf("%d", &base);
    printf("\nIngresa el valor de la potencia: ");
    scanf("%d", &potency);

    int resultOfPotency = calculatePotenceSum(base, potency);
    printf("El resultado de elevar el numero %d a %d es: %d", base, potency, resultOfPotency);
    printf("\n-----------------------PROGRAMA 3-----------------------");
    //--------------------------------------Problema 3--------------------------------------

    //--------------------------------------Problema 4--------------------------------------
    int numberToCalculateItDigitsSum = 0;
    int resultDigitSum = 0;
    printf("\n\n-----------------------PROGRAMA 4-----------------------");
    printf("\nIngrese el numero al que se le va a calcular la suma de sus digitos: ");
    scanf("%d", &numberToCalculateItDigitsSum);
    resultDigitSum = calculateSumOfDigits(numberToCalculateItDigitsSum);
    printf("El resultado de sumar los digitos de %d es: %d", numberToCalculateItDigitsSum, resultDigitSum);
    printf("\n-----------------------PROGRAMA 4-----------------------");
    //--------------------------------------Problema 4--------------------------------------
}

int calculatePositiveSum(int n) {
    if (n == 1) {
        return 1;
    }
    return n + calculatePositiveSum(n - 1);
}

int calculateFactorial(int n) {
    if (n == 1) {
        return 1;
    }

    return n * calculateFactorial(n - 1);
}

int calculatePotenceSum(int base, int potency) {
    if (base == 1) {
        return 1;
    }

    if (potency == 1) {
        return base;
    }

    return base * calculatePotenceSum(base, potency - 1);
}

int calculateSumOfDigits(int n) {
    if (n / 10 == 0) {
        return n;
    }

    return (n % 10) + calculateSumOfDigits(n / 10);
}
