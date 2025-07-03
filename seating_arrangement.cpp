#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, r;
        cin >> n >> r;
        vector<int> a(n);
        int total_people = 0;

        for (int i = 0; i < n; ++i)
            cin >> a[i];

        int pairs = 0;
        int singles = 0;

        for (int i = 0; i < n; ++i) {
            pairs += a[i] / 2;
            singles += a[i] % 2;
        }

        int remaining_rows = r - pairs;
        int happy_people = 0;
        if (singles == 0)
            happy_people = pairs * 2;
        else {
            if (remaining_rows >= singles)
                happy_people = pairs * 2 + singles;
            else
                happy_people = 2 * pairs + remaining_rows * 2 - singles;
        }
        cout << happy_people << endl;
    }
    return 0;
}
