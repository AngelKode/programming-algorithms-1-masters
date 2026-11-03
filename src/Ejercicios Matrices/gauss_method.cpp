/*
*Realizar un programa que implemente el metodo de gauss para resolver ecuaciones
*lineales. Mostrar las variables como X1, X2, .... , Xn
*/

#include <stdio.h>

int main() {
    const int MAX_EQUATION_COUNT = 10, MAX_VARIABLE_COUNT = 10, MIN_EQUATION_COUNT = 2, MIN_VARIABLE_COUNT = 2;
    int MANUAL_MODE_ON = 1;
    int variableCount = 0, equationCount = 0;
    //Primero, le preguntamos al usuario la cantidad de variables del sistema de ecuaciones a ingresar
    //Y la cantidad de ecuaciones. Si la cantidad de ecuaciones es mayor a 10 y la cantidad de variables mayor a 10,
    //se llenara la matriz automaticamente

    do {
        printf("Ingresa la cantidad de ecuaciones del sistema: ");
        scanf("%d", &equationCount);

        printf("Ingresa la cantidad de variables del sistema: ");
        scanf("%d", &variableCount);

        if (equationCount < MIN_EQUATION_COUNT) {
            printf("[ERROR. NUMERO DE ECUACIONES] La cantidad minima de ecuaciones valida es de %d.\n", MIN_EQUATION_COUNT);
        }

        if(variableCount < MIN_VARIABLE_COUNT) {
            printf("[ERROR. NUMERO DE VARIABLES] La cantidad minima de variables valida es de %d.\n", MIN_VARIABLE_COUNT);
        }

        printf("----------------------------------------------------------------------------------------\n\n");
    }while(equationCount < MIN_EQUATION_COUNT || variableCount < MIN_VARIABLE_COUNT);

    //Si la cantidad de ecuaciones y variables supera el minimo establecido, llenarlo con datos aleatorios
    if (equationCount > MAX_EQUATION_COUNT || variableCount > MAX_VARIABLE_COUNT) {
        printf("La cantidad de ecuaciones y/o variables ingresada supera el limite establecido del programa.\n");
        printf("Se utilizaran datos aleatorios y no se podra ingresar datos de manera manual.\n\n");
        MANUAL_MODE_ON = 0;
    }

    //Matriz principal
    //La cantidad columnas + 1, para los términos independientes de las ecuaciones ingresadas
    float equationMatrix[MAX_EQUATION_COUNT][MAX_VARIABLE_COUNT + 1];

    if (MANUAL_MODE_ON == 1) {
        //Llenado manual
        for(int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
            for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
                printf("Ingresa los coeficientes para la ecuacion #%d, de la variable X[%d]: ", equationIndex + 1, variableIndex + 1);
                scanf("%f", &equationMatrix[equationIndex][variableIndex]);
            }
            //Al terminar el llenado de los coeficientes, preguntamos el termino independiente
            printf("Ingresa el termino independiente para la ecuacion #%d: ", equationIndex + 1);
            scanf("%f", &equationMatrix[equationIndex][variableCount]);
        }

        //Mostramos la matriz ingresada
        printf("Matriz ingresada: \n\n");
        for(int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
            printf("[ ");
            for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
                printf("%.2f ", equationMatrix[equationIndex][variableIndex]);
            }
            printf(" | %.2f]\n", equationMatrix[equationIndex][variableCount]);
        }
        printf("\n Operaciones realizadas - Metodo Gauss\n");
        //Empezamos con el metodo de gauss

        //Hacemos que los elementos de la diagonal tengan valor de 1, y todos los valores inferiores, 0

        //Antes de empezar, para asegurarnos que la cantidad de operaciones se mantenga en la diagonal

        //Validamos si la cantidad de ecuaciones es menor que la cantidad de variables independientes
        // en caso de que la cantidad de variables sea mayor, el limite de operaciones sera igual a la cantidad de variables dependientes
        const int operationsLimit = (equationCount < variableCount) ? equationCount : variableCount;

        for (int equationIndex = 0; equationIndex < operationsLimit; equationIndex++) {
            for(int equationIndex2 = 0; equationIndex2 < equationCount; equationIndex2++) {
                printf("[ ");
                for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
                    printf("%.2f ", equationMatrix[equationIndex2][variableIndex]);
                }
                printf(" | %.2f]\n", equationMatrix[equationIndex2][variableCount]);
            }
            printf("\n");
            //Minimo, tenemos que recorrer todas las ecuaciones al menos 1 vez
            //Primero, dividimos el elemento de la diagonal para que su valor sea 1

            //Obtenemos el factor actual
            float currentDependantVariableFactor = equationMatrix[equationIndex][equationIndex];

            //Si el valor del factor actual es igual a 0.00, validamos si podemos hacer un cambio entre la fila actual
            //Y otra que se encuentre hacia abajo
            if (currentDependantVariableFactor == 0.00) {
                printf("Haciendo swapping de ecuaciones: \n");
                for (int currentEquationFactorToBeSwapped = equationIndex + 1; currentEquationFactorToBeSwapped < equationCount; currentEquationFactorToBeSwapped++) {
                    if(equationMatrix[equationIndex][currentEquationFactorToBeSwapped] == 0) {
                        continue; //No tomamos esta ecuacion si vale 0.0
                    }
                    //En caso de que encontremos un elemento diferente de 0, hacemos un swap entre las 2
                    for (int dependantVariableIndex = 0; dependantVariableIndex <= variableCount; dependantVariableIndex++) {
                        float auxiliarDependantValue = equationMatrix[equationIndex][dependantVariableIndex];
                        printf("cambiando %.2f por %.2f\n", auxiliarDependantValue, equationMatrix[currentEquationFactorToBeSwapped][dependantVariableIndex]);
                        equationMatrix[equationIndex][dependantVariableIndex] = equationMatrix[currentEquationFactorToBeSwapped][dependantVariableIndex];
                        equationMatrix[currentEquationFactorToBeSwapped][dependantVariableIndex] = auxiliarDependantValue;
                    }
                    //Actualizamos el factor, ya que hicimos un swap entre funciones
                    currentDependantVariableFactor = equationMatrix[equationIndex][equationIndex];
                }
            }

            //Si despues de seguir evaluando no hay algun elemento que sea diferente de 0
            //Nos saltamos la columna actual continuamos con la siguiente
            if (equationMatrix[equationIndex][equationIndex] == 0.0) {
                continue;
            }

            for(int variableIndex = 0; variableIndex <= variableCount; variableIndex++) {
                if (equationMatrix[equationIndex][variableIndex] == 0) {
                    continue;
                }
                equationMatrix[equationIndex][variableIndex] /= currentDependantVariableFactor;
            }
            for(int equationIndex2 = 0; equationIndex2 < equationCount; equationIndex2++) {
                printf("[ ");
                for (int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
                    printf("%.2f ", equationMatrix[equationIndex2][variableIndex]);
                }
                printf(" | %.2f]\n", equationMatrix[equationIndex2][variableCount]);
            }
            printf("\n");
            //Una vez aplicado la division para que, el coeficiente de la variable de la diagonal sea 1
            //Hacemos la operacion entre la ecuacion actual y las demás para que todos los elementos
            //Debajo de el coeficiente de la diagonal que nos importa, sean 0

            //Aqui tendra el valor por el que tendremos que multiplicar todos los elementos de la ecuacion actual
            //Para sumar con otra funcion para que su valor, en esta misma posicion, quede 0
            float currentFactor = 0;
            for (int equationOperations = equationIndex + 1; equationOperations < equationCount; equationOperations++) {
                currentFactor = (equationMatrix[equationOperations][equationIndex]) * -1;
                for(int variableIndex = 0; variableIndex <= variableCount; variableIndex++) {
                    //A todos los elementos de las ecuaciones que se encuentran debajo, les aplicamos la suma
                    //con la ecuacion actual multiplicada por el valor del factor(currentFactor)
                    //(equationMatrix[equationIndex][variableIndex] * currentFactor) es la ecuacion que convertimos a 1 la diagonal
                    //equationMatrix[equationOperations][variableIndex] es la ecuacion que estamos haciendo la operacion para dejar en 0 el valor de X1, X2, etc
                    equationMatrix[equationOperations][variableIndex] = (equationMatrix[equationIndex][variableIndex] * currentFactor) + equationMatrix[equationOperations][variableIndex];
                }
            }
        }

        //Teniendo los valores en la diagonal en 1 y 0 los elementos debajo, vamos sustituyendo de abajo hacia arriba
        //Para obtener cada valor de X1, X2, .... , Xn
        printf("----------------------------------------------------------------------------------------\n");
        printf("Resultados de la matriz: \n\n");

        //Antes de mostrar resultados, hay que valir si la cantidad de ecuaciones que todos sus valores sean 0's
        //En caso de que la variable independiente sea diferente de 0, NO TIENE SOLUCION
        //Si es igual a cero, TIENE INFINITAS SOLUCIONES
        int hasSolution = 1;
        int validEquationCount = 0;
        for (int equationIndex = 0; equationIndex < equationCount; equationIndex++) {
            int allElementsZero = 0;
            for(int variableIndex = 0; variableIndex < variableCount; variableIndex++) {
                if (equationMatrix[equationIndex][variableIndex] == 0.0) {
                    allElementsZero = 1;
                }
            }

            //Si todos los elementos son 0, validamos si la variable independiente es 0 o diferente de 0
            if(allElementsZero) {
                if (equationMatrix[equationCount][variableCount] > 0.0) {
                    hasSolution = 0;
                }
                continue;
            }

            validEquationCount++;
        }

        //En caso de que no sea valido, imprimimos el resultado, en caso de que si, seguimos para mostrar los resultados
        if(hasSolution == 0) {
            printf("El sistema de ecuaciones no tiene solución\n");
            return 0;
        }

        if (validEquationCount < equationCount - 1) {
            printf("El sistema tiene INFINITAS SOLUCIONES\n");
            return 0;
        }

        float x_nResults[variableCount];
        for(int diagonalCenterElementIndex = variableCount - 1; diagonalCenterElementIndex >= 0; diagonalCenterElementIndex--) {
            //Caso base, el ultimo elemento el cual su valor es igual a el valor independiente
            if(diagonalCenterElementIndex == variableCount - 1) {
                printf("Valor para X_%d : %.2f \n", diagonalCenterElementIndex + 1, equationMatrix[diagonalCenterElementIndex][diagonalCenterElementIndex + 1]);
                x_nResults[diagonalCenterElementIndex] =  equationMatrix[diagonalCenterElementIndex][diagonalCenterElementIndex + 1];
                continue;
            }

            //Caso contrario, hay que obtenerlo de la ecuación y sustituir valores

            float independentVariable = equationMatrix[diagonalCenterElementIndex][variableCount];
            float dependentVariablesResult = 0.0;
            float currentFactor = 0.0;
            //Para obtener el valor dependentVariablesResult, hay que ir obteniendo el valor de multiplicar el coeficiente por el valor de X_n de la ecuacion
            for(int variableElementIndex = diagonalCenterElementIndex + 1; variableElementIndex < variableCount; variableElementIndex++) {
                //Obtenemos el valor de la matriz, cada elemento a la derecha del 1 de la ecuación que estamos evaluando
                currentFactor = equationMatrix[diagonalCenterElementIndex][variableElementIndex];
                //Lo multiplicamos por el valor que se encuentra en x_nResults, por ejemplo, si estamos obteniendo el valor X_2
                //vamos a buscar el valor de X_3 el cual ya lo obtuvimos, y que es necesario para obtener X_2 (en una matriz 3x3)
                dependentVariablesResult += currentFactor * x_nResults[variableElementIndex];
            }

            const float equationResult = independentVariable - dependentVariablesResult;
            printf("Valor para X_%d : %.2f \n", diagonalCenterElementIndex + 1, equationResult);
            x_nResults[diagonalCenterElementIndex] = equationResult;
        }
        printf("----------------------------------------------------------------------------------------\n");
        return 0;
    }
    return 0;
}