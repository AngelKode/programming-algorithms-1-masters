
#include <stdio.h>

int main() {
    int nCount;
    printf("Ingresa el valor de n: ");
    scanf("%d", &nCount);

    int matrix[nCount][nCount];

    for (int rowCount =0; rowCount < nCount; rowCount++) {
        for (int columnCount =0; columnCount < nCount; columnCount++) {
            printf("Ingresa el valor [%d,%d]: ", rowCount, columnCount);
            scanf("%d", &matrix[rowCount][columnCount]);
        }
    }
    //Validamos si alguna fila o columna todos sus elementos valen 0
    int isNotResolvableX = 1, isNotResolvableY = 1;
    for (int rowCount = 0; rowCount < nCount; rowCount++) {
        isNotResolvableY = 1;
        isNotResolvableX = 1;
        for (int columnCount = 0; columnCount < nCount; columnCount++) {
            //Fila
            if (matrix[rowCount][columnCount] != 0) {
                isNotResolvableY = 0;
            }
            //Columna
            if (matrix[columnCount][rowCount] != 0) {
                isNotResolvableX = 0;
            }
        }
        //Si alguna de las variables isNotResolvableX o isNotResolvableY vale 1, el sistema no se puede resolver por kramer
        if(isNotResolvableX == 1) {
            printf("El sistema no tiene solucion debido a que la columna %d todos sus elementos son 0!\n", rowCount + 1);
            return 0;
        }
        if (isNotResolvableY == 1) {
            printf("El sistema no tiene solucion debido a que la fila %d sus elementos son 0!\n",rowCount + 1);
            return 0;
        }
    }

    //Si si tiene solucion, empezamos el método de Kramer
    //Si el tamaño es de 1x1, es el caso base
    if (nCount - 1 == 0) {
        printf("El resultado es: %d",matrix[0][0]);
        return 0;
    }

    if (nCount - 1 == 1) {//No se ocupa usar kramer, ya esta resuelto
        printf("El resultado de X_1: : %d\n",matrix[0][1]);
        printf("El resultado de X_2: : %d\n",matrix[1][1]);
        return 0;
    }

    //nCount - 1 = 3
    for (int mainMatrixDeterminantOps = 0; mainMatrixDeterminantOps < nCount; mainMatrixDeterminantOps++) {
        
    }
}
