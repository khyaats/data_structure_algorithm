#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = -1e9;

int n, m;
vector<int> credit;
vector<vector<int>> children;
vector<vector<int>> dp;

void dfs(int u) {
    dp[u][1] = credit[u];  // you must take u

    for (int v : children[u]) {
        dfs(v);

        vector<int> temp = dp[u];
        for (int i = m; i >= 1; --i) {
            for (int j = 1; j <= i - 1; ++j) {
                if (dp[u][i - j] != INF && dp[v][j] != INF) {
                    temp[i] = max(temp[i], dp[u][i - j] + dp[v][j]);
                }
            }
        }
        dp[u] = temp;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    credit.resize(n + 1);
    children.resize(n + 1);
    dp.assign(n + 1, vector<int>(m + 1, INF));

    vector<int> roots;

    for (int i = 1; i <= n; ++i) {
        int p, c;
        cin >> p >> c;
        credit[i] = c;
        if (p == 0) {
            roots.push_back(i);
        }
        else {
            children[p].push_back(i);
        }
    }

    vector<int> result(m + 1, 0);

    for (int root : roots) {
        dfs(root);
        vector<int> temp = result;
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j + i <= m; ++j) {
                if (dp[root][j] != INF) {
                    temp[i + j] = max(temp[i + j], result[i] + dp[root][j]);
                }
            }
        }
        result = temp;
    }

    cout << *max_element(result.begin(), result.end()) << "\n";
    return 0;
}
