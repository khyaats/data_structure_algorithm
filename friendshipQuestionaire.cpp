#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>
using namespace std;

const int MAX_DIFF = 100;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;

    int la = a.length();
    int lb = b.length();

    if (abs(la - lb) > MAX_DIFF) {
        cout << MAX_DIFF + 1 << "\n";  // impossible to reach within allowed edits
        return 0;
    }

    vector<int> prev(lb + 1, 0), curr(lb + 1, 0);

    for (int j = 0; j <= lb; ++j)
        prev[j] = j;

    for (int i = 1; i <= la; ++i) {
        curr[0] = i;
        int lower = max(1, i - MAX_DIFF);
        int upper = min(lb, i + MAX_DIFF);
        for (int j = lower; j <= upper; ++j) {
            if (a[i - 1] == b[j - 1])
                curr[j] = prev[j - 1];
            else
                curr[j] = 1 + min({ prev[j], curr[j - 1], prev[j - 1] });
        }
        swap(prev, curr);
    }

    cout << prev[lb] << "\n";
    return 0;
}
