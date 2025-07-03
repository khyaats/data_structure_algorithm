#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int money;
    cin >> money;
    vector<int> price_of_candies(10);

    for (int i = 1; i <= 9; ++i)
        cin >> price_of_candies[i];

    int minimum_price = 1e5 + 1, digit_minimum = -1;
    for (int i = 1; i <= 9; ++i) {
        if (price_of_candies[i] <= minimum_price) {
            minimum_price = price_of_candies[i];
            digit_minimum = i;
        }
    }

    int max_digits = money / minimum_price;
    if (max_digits == 0) {
        cout << -1 << endl;
        return 0;
    }

    string result(max_digits, '0' + digit_minimum);
    int remaining = money - (max_digits * minimum_price);

    for (int i = 0; i < max_digits; ++i) {
        for (int d = 9; d > digit_minimum; --d) {
            int diff = price_of_candies[d] - minimum_price;
            if (remaining >= diff) {
                result[i] = '0' + d;
                remaining -= diff;
                break;
            }
        }
    }

    cout << result << endl;
    return 0;
}