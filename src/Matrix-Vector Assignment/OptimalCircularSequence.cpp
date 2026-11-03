#include <cmath>
#include <cstring>
#include <stdio.h>
int main() {
    long long n = 0;
    scanf("%d", &n);

    if (n < 2 || n > 200000) {
        return 0;
    }

    long long xElements[n], distAdjPos[n], distAdjNeg[n], positiveDistanceSum = 0, negativeDistanceSum = 0,
    positiveCosts[n], negativeCosts[n],d = 1, s = 0;

    for (long long i = 0; i < n; i++) {
        scanf("%lld", &xElements[i]);
    }

    //Calulating de adjacent distance when d = 1 and d = -1
    for (long long i = 0; i < n; i++) {
        //In case the previous element for d=1 its < than 0, the previous position will be n - 1
        //Otherwise, i - 1
        const long long indexPosPrev = (i - 1) < 0 ? n - 1 : i - 1;
        const long long indexNegPrev = (i + 1) > n - 1 ? 0 : i + 1;

        distAdjPos[i] = std::abs(xElements[i] - xElements[indexPosPrev]);
        positiveDistanceSum += distAdjPos[i];

        distAdjNeg[i] = std::abs(xElements[i] - xElements[indexNegPrev]);
        negativeDistanceSum += distAdjNeg[i];
    }


    //First, we calculate the cost at the initial s, we defined it as s = 0, s+1 = 1, ... , s + (n - 1)
    //For d = 1 and d = -1
    positiveCosts[0] = 0;
    negativeCosts[0] = 0;
    for (long long costIndexJ = 1; costIndexJ < n; costIndexJ++) {
        //We calculate the sum of j * (yj - yj - 1)
        const long long firstIndexPositive = costIndexJ;
        const long long secondIndexPositive = costIndexJ - 1;

        const long long firstIndexNegative = (n - costIndexJ) % n;
        const long long secondIndexNegative = (n - costIndexJ + 1) % n;

        const long long positiveCost = costIndexJ * std::abs(xElements[firstIndexPositive] - xElements[secondIndexPositive]);
        const long long negativeCost = costIndexJ * std::abs(xElements[firstIndexNegative] - xElements[secondIndexNegative]);

        //We add it the value at the position 0 since we are calculating the cost of starting at s
        positiveCosts[0] += positiveCost;
        negativeCosts[0] += negativeCost;
    }

    //When we get the cost of starting at s, calculating s+1, s+2, ... , s + n - 1 its easier applying the calculated formula
    //i derive for d = 1 and d = -1 at my report (19) and (37)
    long long lowestPositiveCost = positiveCosts[0];
    long long lowestPositiveCostSValue = 0;
    long long lowestNegativeCost = negativeCosts[0];
    long long lowestNegativeCostSValue = 0;
    for (long long sIndex = 1; sIndex < n; sIndex++) {
        //For d = 1, we calculate the cost using equation 19
        positiveCosts[sIndex] = ((n * distAdjPos[sIndex - 1] ) - positiveDistanceSum ) + positiveCosts[sIndex - 1];
        //For d = -1 we calculate the cost using equation 37
        negativeCosts[sIndex] = (negativeDistanceSum - (n * distAdjNeg[sIndex]) ) + negativeCosts[sIndex - 1];

        //When we calculate the new cost at sIndex, we compare it with the sIndex - 1 cost value
        //To always have the lowest cost and the s value that has that cost value
        if (positiveCosts[sIndex] < lowestPositiveCost) {
            lowestPositiveCost = positiveCosts[sIndex];
            lowestPositiveCostSValue = sIndex;
        }
        if (negativeCosts[sIndex] < lowestNegativeCost) {
            lowestNegativeCost = negativeCosts[sIndex];
            lowestNegativeCostSValue = sIndex;
        }
    }

    //When we evaluate all we just get which d and s values are the best options
    long long currentMinimumCost = 0;
    long long sWithMinimumCost = 0;
    const char* bestDirCharacters = "";

    if(lowestPositiveCostSValue < lowestNegativeCostSValue) {
        currentMinimumCost = lowestPositiveCost;
        sWithMinimumCost = lowestPositiveCostSValue;
        bestDirCharacters = "CW";
    }else if(lowestNegativeCostSValue < lowestPositiveCostSValue) {
        currentMinimumCost = lowestNegativeCost;
        sWithMinimumCost = lowestNegativeCostSValue;
        bestDirCharacters = "CCW";
    }else {
        if (lowestPositiveCost < lowestNegativeCost) {
            currentMinimumCost = lowestPositiveCost;
            sWithMinimumCost = lowestPositiveCostSValue;
            bestDirCharacters = "CW";
        }

        if (lowestNegativeCost < lowestPositiveCost) {
            currentMinimumCost = lowestNegativeCost;
            sWithMinimumCost = lowestNegativeCostSValue;
            bestDirCharacters = "CCW";
        }

        if (lowestNegativeCost == lowestPositiveCost) {
            currentMinimumCost = lowestPositiveCost;
            sWithMinimumCost = lowestPositiveCostSValue;
            bestDirCharacters = "CW";
        }
    }



    printf("%lld\n", currentMinimumCost);
    printf("%lld\n", sWithMinimumCost);
    printf("%s\n", bestDirCharacters);

    const long long elementsToPrint = (n < 10) ? n : 10;
    const long long step = (strcmp(bestDirCharacters, "CW")) ? -1 : 1;

    for (int elementCount = 0; elementCount < elementsToPrint; elementCount++) {
        long long indexBasedOnS = (sWithMinimumCost + (step * elementCount)) % n;
        if (indexBasedOnS < 0) {
            indexBasedOnS += n;
        }
        printf("%lld ", xElements[indexBasedOnS]);
    }
    return 0;
}
