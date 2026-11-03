#include <iostream>
#include <string>
using namespace std;

bool esPalindromo(string palabra) {
    const int lenghtPhrase = palabra.length();
    int inversePhraseIndex = lenghtPhrase - 1;
    //Validamos la palabra comparando el indice 0 con el indice n - 1, despues 1 con n - 2, etc
    for (int phraseIndex = 0; phraseIndex < lenghtPhrase; phraseIndex++) {
        if (inversePhraseIndex < 0) {
            break;
        }

        //En caso de que la letra actual sea un espacio en blanco en direccion 0,1,2 nos pasamos a la siguiente letra
        if (isspace(palabra[phraseIndex])) {
            continue;
        }

        //En caso de que el indice que va al contrario del ciclo sea un espacio en blanco, movemos el indice y
        //restamos 1 al que va en direccion 0,1,2 para evitar perder la letra que estamos comparando
        if (isspace(palabra[inversePhraseIndex])) {
            phraseIndex--;
            inversePhraseIndex--;
            continue;
        }
        //Si ambos indices valen lo mismo y las letras son las mismas, rompemos el ciclo
        if (inversePhraseIndex == phraseIndex) {
            return true;
        }

        //Una vez que ya estamos seguros de estar validando letras, comparamos su contenido
        //Y en caso de que alguno se cumpla, restamos el indice que va inverso
        if ((int)palabra[phraseIndex] == (int) palabra[inversePhraseIndex]) {
            inversePhraseIndex--;
            continue;
        }
        //Si no son iguales, validamos si son iguales pero difieren en que uno es minuscula y otra mayuscula
        if(toupper(palabra[phraseIndex]) == toupper(palabra[inversePhraseIndex])) {
            inversePhraseIndex--;
            continue;
        }

        //En caso de que no hayamos encontrado coincidencias, en automatico no es palindromo y retornamos el resultado
        return false;
    }

    return true;
}
int main() {
    string pruebas[] = { "reconocer", "Anilina", "programa", " a ", "Anilina ", "a b", "Anita lava la tina", " ! A ! " };

    for(int pruebaIndex = 0; pruebaIndex < sizeof(pruebas) / sizeof(pruebas[0]); pruebaIndex++) {
        printf("Prueba # %d: ", pruebaIndex + 1);
        if(esPalindromo(pruebas[pruebaIndex])) {
            printf("'%s' es palindromo\n", pruebas[pruebaIndex].c_str());
            continue;
        }
        printf("'%s' no es palindromo\n", pruebas[pruebaIndex].c_str());
    }
    return 0;
}