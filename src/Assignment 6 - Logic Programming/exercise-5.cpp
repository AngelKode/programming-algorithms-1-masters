#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string inputPhrase;

    printf("Ingresa la palabra: ");
    getline(cin, inputPhrase);

    bool isValidPhrase = false;
    int letters[27] = {};
    printf("%s\n", inputPhrase.c_str());
    //Recorremos la frase para solamente obtener letras validas y su conteo
    for (int phraseIndex = 0; phraseIndex < inputPhrase.length(); phraseIndex++) {
        if (isalpha(inputPhrase[phraseIndex])) {
            isValidPhrase = true;
            char minusLetter = tolower(inputPhrase[phraseIndex]);
            //Sumamos en 1 cuantas letras hay
            //Usamos minusLetter - 'a' porque la primer letra de todas es a
            //Si la letra que estamos leyendo es a, el resultado va a ser 0, y para b 1, y asi hasta 26
            letters[minusLetter - 'a']++;
        }

    }

    if (!isValidPhrase) {
        printf("La palabra no tiene letras validas");
        return 0;
    }

    int maxCount = 0;
    int minCount = inputPhrase.length() + 1;//Para si o si encontrar el mas minimo y de ahi para adelante

    //Encontramos la cantidad máxima y mínima de repeticiones
    for (int letterIndex = 0; letterIndex < 26; letterIndex++) {
        if (letters[letterIndex] > 0) { // Solo evaluamos las letras que sí existen en la frase
            if (letters[letterIndex] > maxCount) {
                //Actualizamos el monto maximo
                maxCount = letters[letterIndex];
            }
            if (letters[letterIndex] < minCount) {
                //Actualizamos el monto minimo
                minCount = letters[letterIndex];
            }
        }
    }

    //Mostramos la o las letras que mas se repiten segun la cantidad maxima que encontramos
    //Y que la cantidad corresponda a maxCount
    printf("Mas repetida: ");
    for (int letterIndex = 0; letterIndex < 26; letterIndex++) {
        if (letters[letterIndex] == maxCount) {
            //Asi como le hicimos para el conteo minusLetter - 'a', hacemos la inversa
            //Aqui ya no aplicamos tolower porque solo almacenamos minusculas
            printf("%c ", letterIndex + 'a');
        }
    }
    printf("(%d veces)\n", maxCount);

    //Mostramos la o las letras que menos se repiten
    printf("Menos repetida: ");
    for (int letterIndex = 0; letterIndex < 26; letterIndex++) {
        if (letters[letterIndex] == minCount) {
            printf("%c ", letterIndex + 'a');
        }
    }
    printf("(%d veces)\n", minCount);

    return 0;
}