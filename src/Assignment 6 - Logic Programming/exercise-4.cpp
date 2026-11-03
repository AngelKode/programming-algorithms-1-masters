#include <iostream>
#include <string>
using namespace std;

char getHexadecimal(int numero) {
    char hexadecimal = '0';
    if (numero < 10) {
        hexadecimal = '0' + numero;
    }
    switch (numero) {
        case 10:
            hexadecimal = 'A';
            break;
        case 11:
            hexadecimal = 'B';
            break;
        case 12:
            hexadecimal = 'C';
            break;
        case 13:
            hexadecimal = 'D';
            break;
        case 14:
            hexadecimal = 'E';
            break;
        case 15:
            hexadecimal = 'F';
            break;
    }
    return hexadecimal;
}

string convertir(int numero, int base) {
    string resultado = "";

    if (base == 2) {
        //En caso de que valga 0 o 1, imprimimos ese valor
        if (numero == 0) {
            return"0";
        }
        //Para el caso base 2, vamos dividiendo el numero entre 2 hasta que numero sea diferente de 0
        //En caso de que sea 0, hemos terminado
        while (numero != 0) {
            //Convertimos el resultado a char
            //Usando '0' y le agregamos el residuo, ya que '0' vale 48 y al agregarle ya sea 0 o 1 segun sea
            //el caso, se va a convertir en ese valor pero en char
            const char aux = '0' + (numero % base);
            resultado = aux + resultado;
            numero /= base;
        }
        return resultado;
    }

    if (base == 8) {
        //En caso de que el numero sea menor que 8, imprimimos ese valor
        //Caso contrario, agregamos el residuo de dividir entre 8 y actualizamos el numero
        //Al resultado de dividir el numero entre 8, y asi sucesivamente
        if (numero < 8) {
            resultado = '0' + numero;
            return resultado;
        }
        //Para el caso base 8, vamos dividiendo el numero entre 8 hasta que numero sea menor a 8
        //En caso de que sea menor, terminamos de obtener el octal
        for (; numero >= base; numero /= base) {
            //Convertimos el resultado a char
            //Usando '0' y le agregamos el residuo, ya que '0' vale 48 y al agregarle ya sea 0 o 1 segun sea
            //el caso, se va a convertir en ese valor pero en char
            const char aux = '0' + (numero % base);
            resultado = aux + resultado;
        }
        //Antes de retornar, agregamos el último residuo
        const char aux = '0' + numero;
        resultado = aux + resultado;
        return resultado;
    }

    if (base == 16) {
        //Si el numero es menor a 10, retornamos el valor como tal
        if (numero < 16) {
            return getHexadecimal(numero) + resultado;
        }
        //Para el caso base 16, vamos dividiendo el numero entre 16 hasta que numero sea menor a 10
        //En caso de que sea menor, terminamos de obtener el hexadecimal
        //Si vale 10 le asignamos A, 11 B, ... , F 15
        for (; numero > base ; numero /= base) {
            //Convertimos el resultado a char
            //Usando '0' y le agregamos el residuo, ya que '0' vale 48 y al agregarle ya sea 0 o 1 segun sea
            //el caso, se va a convertir en ese valor pero en char
            int divideResult = (numero % base);

            //Agregamos primero el decimal y luego el acumulado
            resultado = getHexadecimal(divideResult) + resultado;
        }
        //Antes de retornar, agregamos el último residuo
        resultado = getHexadecimal(numero) + resultado;
        return resultado;

    }

    return resultado;
}

int main() {
    int numberToConvert;
    printf("Ingresa el numero a calcular: ");
    scanf("%d", &numberToConvert);

    printf("Binario: %s\n", convertir(numberToConvert, 2).c_str());
    printf("Octal: %s\n",convertir(numberToConvert, 8).c_str());
    printf("Hexadecimal: %s\n", convertir(numberToConvert, 16).c_str());
    return 0;
}
