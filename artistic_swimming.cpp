#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int number_of_males, number_of_females;
    cin >> number_of_males >> number_of_females;
    vector<int> males(number_of_males), females(number_of_females);

    for (int i = 0; i < number_of_males; ++i)
        cin >> males[i];
    for (int i = 0; i < number_of_females; ++i)
        cin >> females[i];

    sort(males.begin(), males.end(), greater<int>());
    sort(females.begin(), females.end(), greater<int>());

    int female_index = 0;
    int trio_count = 0;

    for (int i = 0; i < number_of_males; ++i) {
        int count = 0;
        while (female_index < number_of_females && count < 2) {
            if (females[female_index] < males[i]) {
                ++count;
            }
            ++female_index;
        }
        if (count == 2)
            ++trio_count;
        else
            break;
    }

    cout << trio_count << '\n';
    return 0;
}