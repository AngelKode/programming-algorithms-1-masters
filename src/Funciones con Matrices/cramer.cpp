/*
*Realizar un programa que resuelva sistemas de ecuaciones de 3x3 usando el metodo de Cramer
*/

#include <cstdlib>
#include <ctime>
#include <climits>
#include <stdio.h>

//MATRIX_SIZE: el metodo de Cramer se trabaja para sistemas de 3 ecuaciones con 3 variables
//MANUAL_OPTION y RANDOM_OPTION: opciones del menu para el llenado de la matriz
const int MATRIX_SIZE = 3, MANUAL_OPTION = 1, RANDOM_OPTION = 2;

//Tolerancia para considerar un numero como 0 (los decimales no siempre dan 0 exacto)
const double LOW_MIN_VALUE_COMPARATOR = 1e-9;

//Le preguntamos al usuario si quiere capturar los datos a mano o usar numeros aleatorios
int readFillMode() {
    int fillMode = 0;
    do {
        printf("Como deseas llenar el sistema de ecuaciones?\n");
        printf("%d) Captura manual\n", MANUAL_OPTION);
        printf("%d) Datos aleatorios\n", RANDOM_OPTION);
        printf("Opcion: ");
        if (scanf("%d", &fillMode) != 1) {
            exit(1);
        }

        if (fillMode != MANUAL_OPTION && fillMode != RANDOM_OPTION) {
            printf("[ERROR. OPCION INVALIDA] Debes elegir %d o %d.\n", MANUAL_OPTION, RANDOM_OPTION);
        }

        printf("----------------------------------------------------------------------------------------\n\n");
    } while (fillMode != MANUAL_OPTION && fillMode != RANDOM_OPTION);

    return fillMode;
}

//Llenado manual de la matriz aumentada
void fillMatrix(double equationMatrix[][MATRIX_SIZE + 1]) {
    for (int equationIndex = 0; equationIndex < MATRIX_SIZE; equationIndex++) {
        for (int variableIndex = 0; variableIndex < MATRIX_SIZE; variableIndex++) {
            printf("Ingresa los coeficientes para la ecuacion #%d, de la variable X[%d]: ", equationIndex + 1, variableIndex + 1);
            scanf("%lf", &equationMatrix[equationIndex][variableIndex]);
        }
        //Al terminar el llenado de los coeficientes, preguntamos el termino independiente
        printf("Ingresa el termino independiente para la ecuacion #%d: ", equationIndex + 1);
        scanf("%lf", &equationMatrix[equationIndex][MATRIX_SIZE]);
    }
}

//Genera un numero aleatorio entre minRand y maxRand (ambos incluidos)
int randomBetween(int minRand, int maxRand) {
    return (rand() % (maxRand - minRand + 1)) + minRand;
}

//Llenado automatico con numeros aleatorios
void fillMatrixAutomatically(double equationMatrix[][MATRIX_SIZE + 1], int minRand, int maxRand) {
    for (int equationIndex = 0; equationIndex < MATRIX_SIZE; equationIndex++) {
        for (int variableIndex = 0; variableIndex < MATRIX_SIZE; variableIndex++) {
            equationMatrix[equationIndex][variableIndex] = (double)randomBetween(minRand, maxRand);
        }
        //Al terminar el llenado de los coeficientes, llenamos el termino independiente
        equationMatrix[equationIndex][MATRIX_SIZE] = (double)randomBetween(minRand, maxRand);
    }
}

//Muestra la matriz aumentada
void printMatrix(double equationMatrix[][MATRIX_SIZE + 1]) {
    for (int equationIndex = 0; equationIndex < MATRIX_SIZE; equationIndex++) {
        printf("[ ");
        for (int variableIndex = 0; variableIndex < MATRIX_SIZE; variableIndex++) {
            printf("%.2lf ", equationMatrix[equationIndex][variableIndex]);
        }
        printf(" | %.2lf]\n", equationMatrix[equationIndex][MATRIX_SIZE]);
    }
}

//Muestra una matriz cuadrada de 3x3 (sin terminos independientes)
void printSquareMatrix(double squareMatrix[][MATRIX_SIZE]) {
    for (int rowIndex = 0; rowIndex < MATRIX_SIZE; rowIndex++) {
        printf("[ ");
        for (int columnIndex = 0; columnIndex < MATRIX_SIZE; columnIndex++) {
            printf("%.2lf ", squareMatrix[rowIndex][columnIndex]);
        }
        printf("]\n");
    }
}

//Copiamos la matriz de coeficientes, y si replacedColumn es valida, cambiamos esa columna
//por los terminos independientes. Si replacedColumn vale -1, solo se copian los coeficientes
void buildCramerMatrix(double equationMatrix[][MATRIX_SIZE + 1], double cramerMatrix[][MATRIX_SIZE], int replacedColumn) {
    for (int rowIndex = 0; rowIndex < MATRIX_SIZE; rowIndex++) {
        for (int columnIndex = 0; columnIndex < MATRIX_SIZE; columnIndex++) {
            if (columnIndex == replacedColumn) {
                cramerMatrix[rowIndex][columnIndex] = equationMatrix[rowIndex][MATRIX_SIZE];
                continue;
            }
            cramerMatrix[rowIndex][columnIndex] = equationMatrix[rowIndex][columnIndex];
        }
    }
}

//Calculamos el determinante con la regla de Sarrus:
//sumamos los productos de las 3 diagonales hacia la derecha y restamos los de las 3 diagonales hacia la izquierda
double calculateDeterminant(double squareMatrix[][MATRIX_SIZE]) {
    double positiveDiagonalsSum = 0, negativeDiagonalsSum = 0;

    for (int startColumn = 0; startColumn < MATRIX_SIZE; startColumn++) {
        double positiveProduct = 1, negativeProduct = 1;
        for (int rowIndex = 0; rowIndex < MATRIX_SIZE; rowIndex++) {
            //Diagonal hacia la derecha: la columna avanza junto con la fila
            positiveProduct *= squareMatrix[rowIndex][(startColumn + rowIndex) % MATRIX_SIZE];
            //Diagonal hacia la izquierda: la columna retrocede mientras la fila avanza
            negativeProduct *= squareMatrix[rowIndex][(startColumn - rowIndex + MATRIX_SIZE) % MATRIX_SIZE];
        }
        positiveDiagonalsSum += positiveProduct;
        negativeDiagonalsSum += negativeProduct;
    }

    return positiveDiagonalsSum - negativeDiagonalsSum;
}

//Revisamos si un valor se puede considerar como 0 usando la tolerancia
int isZero(double value) {
    return value < LOW_MIN_VALUE_COMPARATOR && value > -LOW_MIN_VALUE_COMPARATOR;
}

//Metodo de Cramer: obtenemos el determinante del sistema y el determinante de cada variable,
//que es el de la matriz de coeficientes con su columna reemplazada por los terminos independientes
void cramer(double equationMatrix[][MATRIX_SIZE + 1], double &systemDeterminant, double variableDeterminants[]) {
    double cramerMatrix[MATRIX_SIZE][MATRIX_SIZE];

    printf("\n Operaciones realizadas - Metodo de Cramer\n");

    //Primero el determinante del sistema, solo con los coeficientes
    buildCramerMatrix(equationMatrix, cramerMatrix, -1);
    systemDeterminant = calculateDeterminant(cramerMatrix);

    printf("\nPaso 1: Determinante del sistema (D)\n");
    printSquareMatrix(cramerMatrix);
    printf("D = %.4lf\n", systemDeterminant);

    //Despues, un determinante por cada variable
    for (int variableIndex = 0; variableIndex < MATRIX_SIZE; variableIndex++) {
        buildCramerMatrix(equationMatrix, cramerMatrix, variableIndex);
        variableDeterminants[variableIndex] = calculateDeterminant(cramerMatrix);

        printf("\nPaso %d: Determinante de X_%d (D%d), columna %d reemplazada por los terminos independientes\n", variableIndex + 2, variableIndex + 1, variableIndex + 1, variableIndex + 1);
        printSquareMatrix(cramerMatrix);
        printf("D%d = %.4lf\n", variableIndex + 1, variableDeterminants[variableIndex]);
    }
}

//Si el determinante del sistema es diferente de 0, el sistema tiene solucion unica.
//Si vale 0 y algun determinante de variable no, el sistema NO TIENE SOLUCION.
//Si todos valen 0, Cramer no alcanza para decidir: puede tener infinitas soluciones o ninguna
void analyzeEquationSystem(double systemDeterminant, double variableDeterminants[], int &hasUniqueSolution, int &hasSolution) {
    if (!isZero(systemDeterminant)) {
        hasUniqueSolution = 1;
        return;
    }

    hasUniqueSolution = 0;
    for (int variableIndex = 0; variableIndex < MATRIX_SIZE; variableIndex++) {
        if (!isZero(variableDeterminants[variableIndex])) {
            hasSolution = 0;
            return;
        }
    }
}

//Con Cramer, cada variable se obtiene dividiendo su determinante entre el determinante del sistema: X_n = Dn / D
void printSolutions(double systemDeterminant, double variableDeterminants[]) {
    for (int variableIndex = 0; variableIndex < MATRIX_SIZE; variableIndex++) {
        double variableValue = variableDeterminants[variableIndex] / systemDeterminant;
        //Evitamos que se muestre -0.0000
        if (isZero(variableValue)) {
            variableValue = 0.0;
        }
        printf("Valor para X_%d : %.4lf / %.4lf = %.4lf \n", variableIndex + 1, variableDeterminants[variableIndex], systemDeterminant, variableValue);
    }
}

int main() {
    srand(time(NULL)); // Para obtener un numero diferente en cada ejecucion

    //Matriz aumentada de 3x3, con una columna extra para los terminos independientes
    double equationMatrix[MATRIX_SIZE][MATRIX_SIZE + 1];

    int fillMode = readFillMode();

    if (fillMode == MANUAL_OPTION) {
        fillMatrix(equationMatrix);
    } else {
        int minRandomUser = 0, maxRandomUser = 0;
        printf("Ingresa el valor minimo que deben tener los numeros aleatorios generados: ");
        if (scanf("%d", &minRandomUser) != 1 || minRandomUser < 0) {
            printf("El limite inferior es invalido\n");
            return 1;
        }

        printf("Ingresa el valor maximo que deben tener los numeros aleatorios generados: ");
        if (scanf("%d", &maxRandomUser) != 1 || maxRandomUser < minRandomUser || maxRandomUser == INT_MAX) {
            printf("El limite superior es invalido (debe ser mayor o igual al minimo)\n");
            return 1;
        }
        printf("Generando datos aleatorios para la matriz...\n\n");
        fillMatrixAutomatically(equationMatrix, minRandomUser, maxRandomUser);
    }

    //Mostramos la matriz ingresada
    printf("Matriz ingresada (%d ecuaciones, %d variables): \n\n", MATRIX_SIZE, MATRIX_SIZE);
    printMatrix(equationMatrix);

    double systemDeterminant = 0;
    double variableDeterminants[MATRIX_SIZE];
    cramer(equationMatrix, systemDeterminant, variableDeterminants);

    printf("----------------------------------------------------------------------------------------\n");
    printf("Resultados de la matriz: \n\n");

    int hasUniqueSolution = 0;
    int hasSolution = 1;
    analyzeEquationSystem(systemDeterminant, variableDeterminants, hasUniqueSolution, hasSolution);

    //En caso de que no tenga solucion unica, imprimimos el motivo, en caso de que si, seguimos para mostrar los resultados
    if (hasSolution == 0) {
        printf("El sistema de ecuaciones NO TIENE SOLUCION (D = 0 y al menos un Dn es diferente de 0)\n");
        return 0;
    }

    if (hasUniqueSolution == 0) {
        printf("El sistema NO TIENE SOLUCION UNICA (D = 0 y todos los Dn = 0): puede tener INFINITAS SOLUCIONES o ninguna\n");
        return 0;
    }

    printSolutions(systemDeterminant, variableDeterminants);
    printf("----------------------------------------------------------------------------------------\n");
    return 0;
}