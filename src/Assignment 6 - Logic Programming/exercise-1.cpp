#include <iostream>
using namespace std;

int main() {
    int nCount = 0;

    printf("Ingrese el valor de n: ");
    scanf("%d", &nCount);

    if (nCount <= 0) {
        printf("[Error]: El valor minimo requerido es de 1.\n");
        return 0;
    }

    //i = 0, 1, ... , nCount - 1
    for (int rowOperations = 0; rowOperations < nCount; rowOperations++) {
        //En la variable initialSpaces guardamos cuantos espacios imprimir antes de imprimir los *
        //Por ejemplo, si n = 6, para el primer renglon son 5, para el segundo 4 y asi hasta 0, que es el ultimo
        int initialSpaces = nCount - (1 + rowOperations);

        for (int printSpaces = 0; printSpaces < initialSpaces; printSpaces++) {
            printf(" ");
        }
        //Una vez impresos los espacios, imprimimos la cantidad de * aplicando la formula 2i - 1
        for (int asteriskCount = (2 * (rowOperations + 1) - 1); asteriskCount > 0; asteriskCount--) {
            printf("*");
        }
        printf("\n");
    }

    //Basandonos en la cantidad de n, obtenemos la altura del arbol
    int treeBaseHeightSize = nCount / 3;

    //En caso de que sea 0 para valores muy pequeños, nos aseguramos que minimo valga 1
    if (treeBaseHeightSize == 0) {
        treeBaseHeightSize = 1;

    }

    //Para imprimir el tronco, obtenemos una posicion central para colocarla basandonos en el tamaño del ultimo renglon
    //Dependiendo la posicion del primer renglon, el inicial estara en el espacio n - 1, hasta n
    //Teniendo ambos indices, solo lo imprimimos

    //Si n vale 1, funciona diferente y solo imprimimos 2 **
    if (nCount - 2 < 0) {
        printf("**\n");
        return 0;
    }

    //En caso de que n sea 2, 3, ...
    for (int treeHeightIndex = 0; treeHeightIndex < treeBaseHeightSize; treeHeightIndex++) {
        for (int treeBasePrintIndex = 0; treeBasePrintIndex < nCount; treeBasePrintIndex++) {
            //En caso de que no corresponda a los indices calculados, imprimimos un espacio
            if (treeBasePrintIndex != nCount - 2 && treeBasePrintIndex != nCount - 1) {
                printf(" ");
                continue;
            }
            //Caso contrario, imprimimos un *
            printf("*");
        }
        printf("\n");
    }
    return 0;
}