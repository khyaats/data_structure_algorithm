#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arrayOfNumbers(n);
    int countOfOne = 0, countOfTwo = 0, countOfThree = 0;

    for (int i = 0; i < n; i++) {
        cin >> arrayOfNumbers[i];
        if (arrayOfNumbers[i] == 1) countOfOne++;
        else if (arrayOfNumbers[i] == 2) countOfTwo++;
        else countOfThree++;
    }

    int oneInTwoArea = 0, oneInThreeArea = 0;
    int twoInOneArea = 0, twoInThreeArea = 0;
    int threeInOneArea = 0, threeInTwoArea = 0;

    for (int i = 0; i < n; i++) {
        if (i < countOfOne) {
            if (arrayOfNumbers[i] == 2) twoInOneArea++;
            if (arrayOfNumbers[i] == 3) threeInOneArea++;
        }
        else if (i < countOfOne + countOfTwo) {
            if (arrayOfNumbers[i] == 1) oneInTwoArea++;
            if (arrayOfNumbers[i] == 3) threeInTwoArea++;
        }
        else {
            if (arrayOfNumbers[i] == 1) oneInThreeArea++;
            if (arrayOfNumbers[i] == 2) twoInThreeArea++;
        }
    }

    int numberOfSwaps = 0;

    int directSwapOne = min(oneInTwoArea, twoInOneArea);
    numberOfSwaps += directSwapOne;
    oneInTwoArea -= directSwapOne;
    twoInOneArea -= directSwapOne;

    int directSwapTwo = min(oneInThreeArea, threeInOneArea);
    numberOfSwaps += directSwapTwo;
    oneInThreeArea -= directSwapTwo;
    threeInOneArea -= directSwapTwo;

    int directSwapThree = min(twoInThreeArea, threeInTwoArea);
    numberOfSwaps += directSwapThree;
    twoInThreeArea -= directSwapThree;
    threeInTwoArea -= directSwapThree;

    int remainingSwaps = oneInTwoArea + oneInThreeArea;
    numberOfSwaps += 2 * remainingSwaps;

    cout << numberOfSwaps << endl;
    return 0;
}