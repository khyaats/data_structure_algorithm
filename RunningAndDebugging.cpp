#include <iostream>
#include <vector>
#include <unordered_map>

int findFaultyStep(const std::vector<int>& stairHeights, int noOfSteps) {
    if (noOfSteps <= 2) return 1;

    std::vector<int> differences(noOfSteps - 1);
    std::unordered_map<int, int> diffCount;

    // Compute differences and count frequencies
    for (int i = 0; i < noOfSteps - 1; i++) {
        differences[i] = stairHeights[i + 1] - stairHeights[i];
        diffCount[differences[i]]++;
    }

    // Identify the most frequent difference
    int common_diff = differences[0], max_freq = 0;
    for (const auto& [diff, freq] : diffCount) {
        if (freq > max_freq) {
            max_freq = freq;
            common_diff = diff;
        }
    }

    // Finding faulty Step
    for (int i = 0; i < noOfSteps - 1; i++) {
        if (differences[i] != common_diff) {
            if (i == 0) {
                // Faulty Step at the strt
                if (differences[i + 1] == common_diff) return 1;     // first step is faulty
                else return 2;                                 // second step is faulty
            }
            else if (i == noOfSteps - 2) {
                // Faulty Step is at Last
                if (differences[i - 1] == common_diff) return noOfSteps;     // last step is faulty
                else return noOfSteps - 1;                             // last second step is faulty
            }
            else {
                // Faulty Step is in middle
                if (differences[i - 1] == common_diff && differences[i + 1] == common_diff)
                    return i + 1; // ith step is faulty
                else
                    return i + 2; // i+1 step is faulty
            }
        }
    }
    return 1;
}

int main() {
    int noOfSteps;
    std::cin >> noOfSteps;
    std::vector<int> stairHeights(noOfSteps);
    for (int& height : stairHeights)
        std::cin >> height;
 
    std::cout << findFaultyStep(stairHeights, noOfSteps) << std::endl;
    return 0;
}