#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> cost(26);
    for (int i = 0; i < k; ++i) {
        cin >> cost[i];
    }
    string s;
    cin >> s;

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j - 1];
            }
            else {
                int leftCost = cost[s[i] - 'a'] + dp[i + 1][j];
                int rightCost = cost[s[j] - 'a'] + dp[i][j - 1];
                dp[i][j] = min(leftCost, rightCost);
            }
        }
    }

    cout << dp[0][n - 1] << endl;
    return 0;
}
