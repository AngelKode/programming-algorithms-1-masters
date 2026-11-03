
#include <stdio.h>
#define data_type long long
int main() {
    //We declare the input variables the user is going to enter
    data_type n,m,r,T,q;
    scanf("%lld",&n);
    scanf("%lld",&m);
    scanf("%lld",&r);
    scanf("%lld",&T);
    scanf("%lld",&q);

    //We ask for every element of the matrix
    data_type matrixA[n][m];
    for (size_t row = 0; row < n; row++) {
        scanf("%lld", &matrixA[row]);
    }

    //Declare variables for what we are going to calculate: anomalous cell count, top-q elements, sum of all deviations i,j
    data_type anomalousCellCount = 0, deviationSum = 0;
    data_type topQElements[q][2];
    return 0;

    //Auxiliary matrix defined in the restrictions
    data_type auxiliaryMatrix[n+1][m+1];
}
