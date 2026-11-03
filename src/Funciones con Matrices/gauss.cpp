/*
*Realizar un programa que implemente el metodo de gauss en minimo 3 funciones
*/

#include <cstdlib>
#include <ctime>
#include <climits>
#include <stdio.h>

//MAX_MANUAL_COUNT: a partir de este valor ya no se capturan datos a mano, se usan aleatorios
//MAX_STORAGE_COUNT: tamaño real de la matriz; nunca se puede trabajar con mas ecuaciones o variables que esto
const int MAX_MANUAL_COUNT = 10, MAX_STORAGE_COUNT = 50, MIN_EQUATION_COUNT = 2, MIN_VARIABLE_COUNT = 2;

//Primero, le preguntamos al usuario la cantidad de variables del sistema de ecuaciones a ingresar
//Y la cantidad de ecuaciones.
void readDimensions(int &equationCount, int &variableCount) {
    int validDimensions = 0;
    do {
        printf("Ingresa la cantidad de ecuaciones del sistema: ");
        if (scanf("%d", &equationCount) != 1) {
            exit(1);
        }

        printf("Ingresa la cantidad de variables del sistema: ");
        if (scanf("%d", &variableCount) != 1) {
            exit(1);
        }

        validDimensions = 1;

        if (equationCount < MIN_EQUATION_COUNT || equationCount > MAX_STORAGE_COUNT) {
            printf("[ERROR. NUMERO DE ECUACIONES] La cantidad de ecuaciones debe estar entre %d y %d.\n", MIN_EQUATION_COUNT, MAX_STORAGE_COUNT);
            validDimensions = 0;
        }

        if (variableCount < MIN_VARIABLE_COUNT || variableCount > MAX_STORAGE_COUNT) {
            printf("[ERROR. NUMERO DE VARIABLES] La cantidad de variables debe estar entre %d y %d.\n", MIN_VARIABLE_COUNT, MAX_STORAGE_COUNT);
            validDimensions = 0;
        }

        printf("----------------------------------------------------------------------------------------\n\n");
    } while (!validDimensions);
}

//Si la cantidad de ecuaciones y/o variables supera el maximo para captura manual, se desactiva el modo manual
void verifiyLimits(int equationCount, int variableCount, int &MANUAL_MODE_ON) {
    if (equationCount > MAX_MANUAL_COUNT || variableCount > MAX_MANUAL_COUNT) {
        printf("La cantidad de ecuaciones y/o variables ingresada supera el limite de captura manual (%d).\n", MAX_MANUAL_COUNT);
        printf("Se utilizaran datos aleatorios y no se podra ingresar datos de manera manual.\n\n");
        MANUAL_MODE_ON = 0;
    }
}

//Llenado manual de la matriz
void fillMatrix(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationCount, int variableCount) {
    for (int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
        for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
            printf("Ingresa los coeficientes para la ecuacion #%d, de la variable X[%d]: ", equationIndex + 1, variableIndex + 1);
            scanf("%lf", &equationMatrix[equationIndex][variableIndex]);
        }
        //Al terminar el llenado de los coeficientes, preguntamos el termino independiente
        printf("Ingresa el termino independiente para la ecuacion #%d: ", equationIndex + 1);
        scanf("%lf", &equationMatrix[equationIndex][variableCount]);
    }
}

//Genera un numero aleatorio entre minRand y maxRand (ambos incluidos)
int randomBetween(int minRand, int maxRand) {
    return (rand() % (maxRand - minRand + 1)) + minRand;
}

//Llenado automatico con numeros aleatorios
void fillMatrixAutomatically(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationCount, int variableCount, int minRand, int maxRand) {
    for (int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
        for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
            equationMatrix[equationIndex][variableIndex] = (double)randomBetween(minRand, maxRand);
        }
        //Al terminar el llenado de los coeficientes, llenamos el termino independiente
        equationMatrix[equationIndex][variableCount] = (double)randomBetween(minRand, maxRand);
    }
}

//Muestra la matriz aumentada
void printMatrix(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationCount, int variableCount) {
    for (int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
        printf("[ ");
        for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
            printf("%.2lf ", equationMatrix[equationIndex][variableIndex]);
        }
        printf(" | %.2lf]\n", equationMatrix[equationIndex][variableCount]);
    }
}

//Si el valor del factor actual es igual a 0.00, buscamos una fila hacia abajo que tenga
//un valor diferente de 0 en la misma columna y las intercambiamos
void swappEquations(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationIndex, int equationCount, int variableCount, double &currentDependantVariableFactor) {
    printf("Haciendo swapping de ecuaciones: \n");
    for (int currentEquationFactorToBeSwapped = equationIndex + 1; currentEquationFactorToBeSwapped < equationCount; currentEquationFactorToBeSwapped++) {
        //Revisamos la columna actual (equationIndex) de la fila candidata
        if (equationMatrix[currentEquationFactorToBeSwapped][equationIndex] == 0.0) {
            continue; //No tomamos esta ecuacion si vale 0.0
        }
        //En caso de que encontremos un elemento diferente de 0, hacemos un swap entre las 2
        for (int dependantVariableIndex = 0; dependantVariableIndex <= variableCount; dependantVariableIndex++) {
            double auxiliarDependantValue = equationMatrix[equationIndex][dependantVariableIndex];
            equationMatrix[equationIndex][dependantVariableIndex] = equationMatrix[currentEquationFactorToBeSwapped][dependantVariableIndex];
            equationMatrix[currentEquationFactorToBeSwapped][dependantVariableIndex] = auxiliarDependantValue;
        }
        printf("Se intercambio la ecuacion #%d con la ecuacion #%d\n", equationIndex + 1, currentEquationFactorToBeSwapped + 1);
        //Actualizamos el factor, ya que hicimos un swap entre funciones
        currentDependantVariableFactor = equationMatrix[equationIndex][equationIndex];
        break; //Con un solo intercambio es suficiente
    }
}

//Dividimos la ecuacion actual para que el coeficiente de la diagonal sea 1
void normalizeEcuation(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationIndex, int variableCount, double currentDependantVariableFactor) {
    for (int variableIndex = 0; variableIndex <= variableCount; variableIndex++) {
        if (equationMatrix[equationIndex][variableIndex] == 0) {
            continue;
        }
        equationMatrix[equationIndex][variableIndex] /= currentDependantVariableFactor;
    }
}

//Hacemos la operacion entre la ecuacion actual y las demás para que todos los elementos
//Debajo de el coeficiente de la diagonal que nos importa, sean 0
void makeZeroUnderCurrentEquation(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationIndex, int equationCount, int variableCount) {
    //Aqui tendra el valor por el que tendremos que multiplicar todos los elementos de la ecuacion actual
    //Para sumar con otra funcion para que su valor, en esta misma posicion, quede 0
    double currentFactor = 0;
    for (int equationOperations = equationIndex + 1; equationOperations < equationCount; equationOperations++) {
        currentFactor = (equationMatrix[equationOperations][equationIndex]) * -1;
        for (int variableIndex = 0; variableIndex <= variableCount; variableIndex++) {
            equationMatrix[equationOperations][variableIndex] = (equationMatrix[equationIndex][variableIndex] * currentFactor) + equationMatrix[equationOperations][variableIndex];
        }
    }
}

//Metodo de Gauss: hacemos que los elementos de la diagonal tengan valor de 1, y todos los valores inferiores, 0
void gauss(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationCount, int variableCount) {
    printf("\n Operaciones realizadas - Metodo Gauss\n");

    //El limite de operaciones es el menor entre la cantidad de ecuaciones y la cantidad de variables
    const int operationsLimit = (equationCount < variableCount) ? equationCount : variableCount;

    for (int equationIndex = 0; equationIndex < operationsLimit; equationIndex++) {
        //Obtenemos el factor actual
        double currentDependantVariableFactor = equationMatrix[equationIndex][equationIndex];

        if (currentDependantVariableFactor == 0.00) {
            swappEquations(equationMatrix, equationIndex, equationCount, variableCount, currentDependantVariableFactor);
        }

        //Si despues de seguir evaluando no hay algun elemento que sea diferente de 0
        //Nos saltamos la columna actual continuamos con la siguiente
        if (equationMatrix[equationIndex][equationIndex] == 0.0) {
            continue;
        }

        normalizeEcuation(equationMatrix, equationIndex, variableCount, currentDependantVariableFactor);
        makeZeroUnderCurrentEquation(equationMatrix, equationIndex, equationCount, variableCount);

        printf("\nPaso %d:\n", equationIndex + 1);
        printMatrix(equationMatrix, equationCount, variableCount);
    }
}

//Validamos si hay ecuaciones con todos sus coeficientes en 0
//En caso de que la variable independiente sea diferente de 0, NO TIENE SOLUCION
//Si es igual a cero, la ecuacion no aporta informacion (no cuenta como valida)
void analyzeEquationSystem(double equationMatrix[][MAX_STORAGE_COUNT + 1], int equationCount, int variableCount, int &hasSolution, int &validEquationCount) {
    //Tolerancia para considerar un numero como 0 (los decimales no siempre dan 0 exacto)
    const double LOW_MIN_VALUE_COMPARATOR = 1e-9;

    for (int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
        int allElementsZero = 1; //Suponemos que todos son 0 hasta encontrar uno que no lo sea
        for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
            double value = equationMatrix[equationIndex][variableIndex];
            if (value > LOW_MIN_VALUE_COMPARATOR || value < -LOW_MIN_VALUE_COMPARATOR) {
                allElementsZero = 0;
                break;
            }
        }

        //Si todos los coeficientes son 0, revisamos el termino independiente de ESTA ecuacion
        if (allElementsZero) {
            double independentTerm = equationMatrix[equationIndex][variableCount];
            if (independentTerm > LOW_MIN_VALUE_COMPARATOR || independentTerm < -LOW_MIN_VALUE_COMPARATOR) {
                hasSolution = 0;
            }
            continue;
        }

        validEquationCount++;
    }
}

//Teniendo los valores en la diagonal en 1 y 0 los elementos debajo, vamos sustituyendo de abajo hacia arriba
//Para obtener cada valor de X1, X2, .... , Xn
void getUknownVariables(double equationMatrix[][MAX_STORAGE_COUNT + 1], int variableCount) {
    double x_nResults[MAX_STORAGE_COUNT];
    for (int diagonalCenterElementIndex = variableCount - 1; diagonalCenterElementIndex >= 0; diagonalCenterElementIndex--) {
        //El termino independiente siempre esta en la columna variableCount
        double independentVariable = equationMatrix[diagonalCenterElementIndex][variableCount];
        double dependentVariablesResult = 0.0;

        //Multiplicamos cada coeficiente a la derecha del 1 por el valor de X_n que ya obtuvimos
        //(para el ultimo renglon este ciclo no se ejecuta y el resultado es el termino independiente)
        for (int variableElementIndex = diagonalCenterElementIndex + 1; variableElementIndex < variableCount; variableElementIndex++) {
            dependentVariablesResult += equationMatrix[diagonalCenterElementIndex][variableElementIndex] * x_nResults[variableElementIndex];
        }

        x_nResults[diagonalCenterElementIndex] = independentVariable - dependentVariablesResult;
    }

    for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
        printf("Valor para X_%d : %.4lf \n", variableIndex + 1, x_nResults[variableIndex]);
    }
}

int main() {
    int MANUAL_MODE_ON = 1;
    int variableCount = 0, equationCount = 0;
    srand(time(NULL)); // Para obtener un numero diferente en cada ejecucion

    readDimensions(equationCount, variableCount);
    verifiyLimits(equationCount, variableCount, MANUAL_MODE_ON);

    //Matriz principal, con el tamaño maximo de almacenamiento
    //La cantidad columnas + 1, para los términos independientes de las ecuaciones ingresadas
    double equationMatrix[MAX_STORAGE_COUNT][MAX_STORAGE_COUNT + 1];

    if (MANUAL_MODE_ON == 1) {
        fillMatrix(equationMatrix, equationCount, variableCount);
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
        fillMatrixAutomatically(equationMatrix, equationCount, variableCount, minRandomUser, maxRandomUser);
    }

    //Mostramos la matriz ingresada
    printf("Matriz ingresada (%d ecuaciones, %d variables): \n\n", equationCount, variableCount);
    printMatrix(equationMatrix, equationCount, variableCount);

    gauss(equationMatrix, equationCount, variableCount);

    printf("----------------------------------------------------------------------------------------\n");
    printf("Resultados de la matriz: \n\n");

    int hasSolution = 1;
    int validEquationCount = 0;
    analyzeEquationSystem(equationMatrix, equationCount, variableCount, hasSolution, validEquationCount);

    //En caso de que no sea valido, imprimimos el resultado, en caso de que si, seguimos para mostrar los resultados
    if (hasSolution == 0) {
        printf("El sistema de ecuaciones NO TIENE SOLUCION\n");
        return 0;
    }

    //Si hay menos ecuaciones validas que variables, sobran incognitas libres
    if (validEquationCount < variableCount) {
        printf("El sistema tiene INFINITAS SOLUCIONES\n");
        return 0;
    }

    getUknownVariables(equationMatrix, variableCount);
    printf("----------------------------------------------------------------------------------------\n");
    return 0;
}