#include <cmath>
#include <iostream>
#define MATRIX_SIZE 3
#define TOLERANCE_VALUE 0.0001
void showMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE]);
void showMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]);
void showVector(double vector[MATRIX_SIZE]);
void initLAndUMapMatrixes(int Lmatrix[MATRIX_SIZE][MATRIX_SIZE], int Umatrix[MATRIX_SIZE][MATRIX_SIZE]);
void createLMatrix(double LMatrixAux[MATRIX_SIZE][MATRIX_SIZE], int LMatrixBool[MATRIX_SIZE][MATRIX_SIZE]);
void createUMatrix(double UMatrixAux[MATRIX_SIZE][MATRIX_SIZE], int UMatrixBool[MATRIX_SIZE][MATRIX_SIZE]);
double validateTolerance(double valueToCompare);
int descompositionLU(double matrix[MATRIX_SIZE][MATRIX_SIZE], double LMatrixAux[MATRIX_SIZE][MATRIX_SIZE], double UMatrixAux[MATRIX_SIZE][MATRIX_SIZE], int LMatrixBool[MATRIX_SIZE][MATRIX_SIZE], int UMatrixBool[MATRIX_SIZE][MATRIX_SIZE]);
void forwardSubstitution(double LMatrixAux[MATRIX_SIZE][MATRIX_SIZE], double independentMatrixValues[MATRIX_SIZE], double yVector[MATRIX_SIZE]);
void backwardSubstitution(double UMatrixAux[MATRIX_SIZE][MATRIX_SIZE], double yVector[MATRIX_SIZE], double unknownVariables[MATRIX_SIZE]);

int main() {
    int keepInTheLoop = 1;
    do {
        printf(" +==========================================================+ \n");
        printf(" |        EXAMEN PARCIAL - METODO DE DESCOMPOSICION LU      |\n");
        printf(" +==========================================================+ \n");
        std::cout<< std::endl;
        std::cout << "Hola usuario. Favor de ingresar los siguientes valores que se indican." << std::endl;
        std::cout << "Ingresa los 9 coeficientes de la matriz 3x3" << std::endl;

        double rootMatrix[MATRIX_SIZE][MATRIX_SIZE];
        double independantMatrixValues[MATRIX_SIZE];
        for (int currentEquation = 0; currentEquation < MATRIX_SIZE; currentEquation++) {
            for (int currentCoefficient = 0; currentCoefficient < MATRIX_SIZE; currentCoefficient++) {
                printf("Ingrese el valor para [ECUACION #%d, COEFICIENTE #%d]: ", currentEquation + 1, currentCoefficient + 1);

                if (scanf("%lf", &rootMatrix[currentEquation][currentCoefficient]) >= 1 ) {
                    //Validamos el valor ingresado contra el valor de tolerancia
                    rootMatrix[currentEquation][currentCoefficient] = validateTolerance(rootMatrix[currentEquation][currentCoefficient]);
                    continue;
                }

                printf("[ERROR]. El valor ingresado para [ECUACION #%d, COEFICIENTE #%d] no es un valor valido.\n", currentEquation + 1, currentCoefficient + 1);
                printf("Cerrando programa...");
                return -1;
            }
            //Terminando de ingresar todos los coeficientes, pedimos el valor independiente
            printf("Ingrese el valor para [ECUACION #%d, TERMINO INDEPENDIENTE]: ", currentEquation + 1);

            if (scanf("%lf", &independantMatrixValues[currentEquation]) >= 1) {
                //Validamos el valor ingresado contra el valor de tolerancia
                independantMatrixValues[currentEquation] = validateTolerance(independantMatrixValues[currentEquation]);
                continue;
            }
            printf("[ERROR]. El valor ingresado para [ECUACION #%d, TERMINO INDEPENDIENTE] no es un valor valido.\n", currentEquation + 1);
            printf("Cerrando programa...");
            return -1;
        }

        printf("Matriz ingresada correctamente!\n\n");
        printf("Matriz ingresada [A]:\n");
        showMatrix(rootMatrix);

        printf("Matriz de terminos independientes [y]:\n");
        showVector(independantMatrixValues);

        printf("\nImplementando descomposicion LU\n\n");

        //Implementacion del Metodo de Descomposicion LU
        double uknownVariables[MATRIX_SIZE];
        double LMatrix[MATRIX_SIZE][MATRIX_SIZE];
        double UMatrix[MATRIX_SIZE][MATRIX_SIZE];
        int LMatrixMapCalculated[MATRIX_SIZE][MATRIX_SIZE];
        int UMatrixMapCalculated[MATRIX_SIZE][MATRIX_SIZE];

        initLAndUMapMatrixes(LMatrixMapCalculated, UMatrixMapCalculated);//Inicializamos en 0 los valores de las matrices que mapean que valores ya fueron calculados

        createLMatrix(LMatrix, LMatrixMapCalculated);//Creamos la matriz L con su matriz de mapeo
        createUMatrix(UMatrix, UMatrixMapCalculated);//Creamos la matriz U con su matriz de mapeo

        //Hacemos el calculo de los coeficientes de L y U
        if (descompositionLU(rootMatrix, LMatrix, UMatrix, LMatrixMapCalculated, UMatrixMapCalculated) == 0) {
            printf("No se pudo resolver el sistema");
            return -1;
        }


        printf("Matriz L: \n");
        showMatrix(LMatrix);
        printf("Matriz U: \n");
        showMatrix(UMatrix);

        printf("\n");

        //Hacemos sustitucion hacia adelante
        double yVector[MATRIX_SIZE];
        forwardSubstitution(LMatrix, independantMatrixValues, yVector);
        printf("\nVector intermedio y (L * y = b):\n");
        showVector(yVector);

        printf("\n");

        //Hacemos sustitucion hacia atras
        backwardSubstitution(UMatrix, yVector, uknownVariables);
        printf("\nSolucion del sistema (U * x = y):\n");
        printf("x = %.4lf\n", uknownVariables[0]);
        printf("y = %.4lf\n", uknownVariables[1]);
        printf("z = %.4lf\n", uknownVariables[2]);

        printf("\n\n");

        //Preguntamos si quiere ingresar otro sistema de ecuaciones
        printf("Desea ingresar otro sistema de ecuaciones? (1=Si / Otro valor=No): ");
        scanf("%d", &keepInTheLoop);

    }while (keepInTheLoop == 1);

    return 0;
}

void showMatrix(double matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int currentRow = 0; currentRow < MATRIX_SIZE; currentRow++) {
        printf("| ");
        for (int currentColumn = 0; currentColumn < MATRIX_SIZE; currentColumn++) {
            printf("%.3lf ", matrix[currentRow][currentColumn]);
        }
        printf(" |\n");
    }
}

void showMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int currentRow = 0; currentRow < MATRIX_SIZE; currentRow++) {
        printf("| ");
        for (int currentColumn = 0; currentColumn < MATRIX_SIZE; currentColumn++) {
            printf("%d ", matrix[currentRow][currentColumn]);
        }
        printf(" |\n");
    }
}

void showVector(double vector[MATRIX_SIZE]) {
    printf("| ");
    for (int currentValue = 0; currentValue < MATRIX_SIZE; currentValue++) {
        printf("%.3lf ", vector[currentValue]);
    }
    printf(" |\n");
}

void initLAndUMapMatrixes(int LMatrixMap[MATRIX_SIZE][MATRIX_SIZE], int UMatrixMap[MATRIX_SIZE][MATRIX_SIZE]) {
    //Inicializamos el mapa donde vamos a ir asigando 1 cuando ese valor ya este calculado
    for (int currentRow = 0; currentRow < MATRIX_SIZE; currentRow++) {
        for (int currentColumn = 0; currentColumn < MATRIX_SIZE; currentColumn++) {
            LMatrixMap[currentRow][currentColumn] = 0;
            UMatrixMap[currentRow][currentColumn] = 0;
        }
    }
}

void createLMatrix(double LMatrixAux[MATRIX_SIZE][MATRIX_SIZE], int LMatrixBool[MATRIX_SIZE][MATRIX_SIZE]) {
    //Establecemos en 1 toda la diagonal central
    for(int currentDiagonalElement = 0; currentDiagonalElement < MATRIX_SIZE; currentDiagonalElement++) {
        LMatrixAux[currentDiagonalElement][currentDiagonalElement] = 1.0L;
        LMatrixBool[currentDiagonalElement][currentDiagonalElement] = 1;
    }

    //Los terminos del triangulo superior como 0s
    for (int currentEquation = 0; currentEquation < MATRIX_SIZE - 1; currentEquation++) {
        for (int currentCoefficient = currentEquation + 1; currentCoefficient < MATRIX_SIZE; currentCoefficient++) {
            LMatrixAux[currentEquation][currentCoefficient] = 0.0L;
            LMatrixBool[currentEquation][currentCoefficient] = 1;
        }
    }

    //Y los demas valores quedan pendientes
}
void createUMatrix(double UMatrixAux[MATRIX_SIZE][MATRIX_SIZE], int UMatrixBool[MATRIX_SIZE][MATRIX_SIZE]) {
    //Los terminos del triangulo inferior como 0s
    for (int currentEquation = MATRIX_SIZE - 1; currentEquation > 0; currentEquation--) {
        for (int currentCoefficient = 0; currentCoefficient < currentEquation; currentCoefficient++) {
            UMatrixAux[currentEquation][currentCoefficient] = 0.0L;
            UMatrixBool[currentEquation][currentCoefficient] = 1;
        }
    }

    //Y los demas valores quedan pendientes
}

double validateTolerance(double valueToCompare) {
    if (std::abs(valueToCompare) >= TOLERANCE_VALUE) {
        return valueToCompare;
    }

    return 0.0L;
}

int descompositionLU(double matrix[MATRIX_SIZE][MATRIX_SIZE], double LMatrixAux[MATRIX_SIZE][MATRIX_SIZE], double UMatrixAux[MATRIX_SIZE][MATRIX_SIZE], int LMatrixBool[MATRIX_SIZE][MATRIX_SIZE], int UMatrixBool[MATRIX_SIZE][MATRIX_SIZE]) {
    //Realizamos las operaciones para obtener los coeficientes
    //Empezamos con la descomposicion Fila 1 U -> Columna 1 L -> Fila 2 U -> Columna 2 L -> Fila 3 U

    //En cada paso currentStep se calcula primero la fila currentStep de U
    //y despues la columna currentStep de L
    for (int currentStep = 0; currentStep < MATRIX_SIZE; currentStep++) {

        // Fila currentStep de U
        //u[i][j] = a[i][j] - (l[i][0]*u[0][j] + ... + l[i][i-1]*u[i-1][j])
        //Solo se calculan las columnas desde la diagonal hacia la derecha
        for (int currentUColumn = currentStep; currentUColumn < MATRIX_SIZE; currentUColumn++) {
            double productsSum = 0.0;
            //En el paso 0 este ciclo no se ejecuta, la suma queda en 0 y u[0][j] = a[0][j]
            for (int k = 0; k < currentStep; k++) {
                productsSum += LMatrixAux[currentStep][k] * UMatrixAux[k][currentUColumn];
            }
            UMatrixAux[currentStep][currentUColumn] = validateTolerance(matrix[currentStep][currentUColumn] - productsSum);
            UMatrixBool[currentStep][currentUColumn] = 1; //Actualizamos la matriz de mapeo
        }

        //Validamos el elemento actual
        //El elemento actual es u[currentStep][currentStep]; la columna de L se divide entre el.
        //Validamos si el elemento actual de la matriz U vale 0
        if (UMatrixAux[currentStep][currentStep] == 0.0) {
            //En caso de ser 0, validamos si podemos hacer un switch de filas
            printf("[INFO]. El valor en la matriz U[%d,%d] vale 0.\n", currentStep + 1, currentStep + 1);
            if (currentStep < MATRIX_SIZE - 1) {
                printf("[INFO]. Hay posibilidad de intercambiar filas para evitar singularidad\n");
                return 0;
            }
            printf("[ERROR CALCULO]. La matriz es singular: el sistema no tiene solucion unica debido a que el valor del elemento en U[%d,%d] es 0 y no hay posibilidad de intercambiar filas\n", currentStep + 1, currentStep + 1);
            return 0;
        }

        // Columna currentStep de L
        //l[r][i] = (a[r][i] - (l[r][0]*u[0][i] + ... + l[r][i-1]*u[i-1][i])) / u[i][i]
        //Solo se calculan las filas debajo de la diagonal
        for (int currentLRow = currentStep + 1; currentLRow < MATRIX_SIZE; currentLRow++) {
            double productsSum = 0.0;
            for (int k = 0; k < currentStep; k++) {
                productsSum += LMatrixAux[currentLRow][k] * UMatrixAux[k][currentStep];
            }
            LMatrixAux[currentLRow][currentStep] = validateTolerance((matrix[currentLRow][currentStep] - productsSum) / UMatrixAux[currentStep][currentStep]);
            LMatrixBool[currentLRow][currentStep] = 1; //Actualizamos la matriz de mapeo
        }
    }

    return 1;
}

void forwardSubstitution(double LMatrixAux[MATRIX_SIZE][MATRIX_SIZE], double independentMatrixValues[MATRIX_SIZE], double yVector[MATRIX_SIZE]) {
    //Tomando la forma Ly = b, donde b es el termino independiente
    //y[i] = b[i] - (l[i][0]*y[0] + ... + l[i][i-1]*y[i-1])
    //Ax = b, (LU)x = b,  L(Ux) = b, Ux = y entonces Ly = b
    for (int currentRow = 0; currentRow < MATRIX_SIZE; currentRow++) {
        double productsSum = 0.0;
        //Solo se usan los y ya calculados. En la fila 0 no hay ninguno.
        for (int k = 0; k < currentRow; k++) {
            productsSum += LMatrixAux[currentRow][k] * yVector[k];
        }
        yVector[currentRow] = validateTolerance(independentMatrixValues[currentRow] - productsSum);
    }
}
void backwardSubstitution(double UMatrixAux[MATRIX_SIZE][MATRIX_SIZE], double yVector[MATRIX_SIZE], double unknownVariables[MATRIX_SIZE]) {
    //Resolvemos U * x = y
    //x[i] = (y[i] - (u[i][i+1]*x[i+1] + ... + u[i][n-1]*x[n-1])) / u[i][i]
    //Ax = b, (LU)x = b,  L(Ux) = b, Ux = y entonces Ly = b, pero como estamos calculando las incognitas x = y / U

    for (int currentRow = MATRIX_SIZE - 1; currentRow >= 0; currentRow--) {
        double productsSum = 0.0;
        //Solo se usan los x ya calculados. En la ultima fila no hay ninguno.
        //Por ejemplo, en la primer iteracion k = 3, pero tiene que ser menor a Matrix Size entonces no entra
        //Para la siguiente, k = 2, entra 1 vez y obtenemos la posicion 2, y asi sucesivamente
        for (int k = currentRow + 1; k < MATRIX_SIZE; k++) {
            productsSum += UMatrixAux[currentRow][k] * unknownVariables[k];
        }
        unknownVariables[currentRow] = validateTolerance((yVector[currentRow] - productsSum) / UMatrixAux[currentRow][currentRow]);
    }
}