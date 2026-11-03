#include <iostream>

int sumOfDivisors(int number);
bool areFriends(int a, int b);
void displayFriendNumbers(int limit);

int main() {
    int number;
    printf("Ingresa el limite para calcular todos los numeros amigos menores o iguales a ese valor: ");
    scanf("%d", &number);

    if (number <= 0) {
        printf("[ERROR]. El valor ingresado debe ser mayor o igual a 1.");
        return 0;
    }

    displayFriendNumbers(number);
    return 0;
}

int sumOfDivisors(int number) {
    int sum = 0;

    for (int divisor = 1; divisor < number; divisor++) {
        if (number % divisor != 0) {
            continue;
        }
        sum += divisor;
    }

    return sum;
}

bool areFriends(int a, int b) {
    return (a == sumOfDivisors(b) && sumOfDivisors(a) == b) && a != b;
}

void displayFriendNumbers(int limit) {
    int numberOfFriendsNumbersFound = 0;
    int previousFriendNumber = 0;
    for (int currentNumber = 1; currentNumber <= limit; currentNumber++) {
        int currentSumOfDivisors = sumOfDivisors(currentNumber);
        //Validamos si el numero actual es amigo del numero que resulta de la suma de sus divisores
        if (!areFriends(currentSumOfDivisors, currentNumber)) {
            continue;
        }
        //Y validamos si el numero actual no lo hemos validado antes
        if(areFriends(currentNumber, previousFriendNumber)) {
            continue;
        }
        //En caso de que pase los filtros, se toma en cuenta como numero amigo
        numberOfFriendsNumbersFound++;
        printf("******Numero amigo encontrado******\n");
        printf(
         "  | | | |        | | | |\n"
             "  | | | | |      | | | | |\n"
             "  | | | | | _  _ | | | | |\n"
             "  | _.-'  |/ \\/ \\|  '-._ |\n"
             "  |       (      )       |\n"
             "   \\       \\    /       /\n"
             "    |       |  |       |\n"
        );
        printf("Los numeros %d y %d son amigos\n", currentNumber, currentSumOfDivisors);
        printf("Suma de los divisores de %d: %d\n", currentNumber, currentSumOfDivisors);
        printf("Suma de los divisores de %d: %d\n", currentSumOfDivisors, sumOfDivisors(currentSumOfDivisors));
        //Actualizamos el valor del numero amigo previamente encontrado
        previousFriendNumber = currentNumber;
    }

    if (numberOfFriendsNumbersFound == 0) {
        printf("No se encontraron numeros amigos en el rango de 1 a %d\n", limit);
    }
}
