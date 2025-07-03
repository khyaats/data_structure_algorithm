#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> increasing(n, 1), decreasing(n, 1);

    // Compute LIS ending at i 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[j] < a[i]) {
                increasing[i] = max(increasing[i], increasing[j] + 1);
            }
        }
    }

    // Compute LDS starting at i
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (a[j] < a[i]) {
                decreasing[i] = max(decreasing[i], decreasing[j] + 1);
            }
        }
    }

    // Combine LIS and LDS to get max LUS
    int maximum_lus = 0;
    for (int i = 0; i < n; i++) {
        if (increasing[i] > 1 && decreasing[i] > 1) {
            maximum_lus = max(maximum_lus, increasing[i] + decreasing[i] - 1);
        }
    }

    cout << maximum_lus << endl;
    return 0;
}