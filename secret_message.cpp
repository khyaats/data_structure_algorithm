#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i)
        cin >> grid[i];

    // Min-heap: (current_string, x, y)
    priority_queue<tuple<string, int, int>,
        vector<tuple<string, int, int>>,
        greater<>> pq;

    pq.push({ string(1, grid[0][0]), 0, 0 });

    while (!pq.empty()) {
        auto [path, x, y] = pq.top();
        pq.pop();

        // If we reached bottom-right
        if (x == n - 1 && y == m - 1) {
            cout << path << "\n";
            return 0;
        }

        // Move down
        if (x + 1 < n) {
            pq.push({ path + grid[x + 1][y], x + 1, y });
        }

        // Move right
        if (y + 1 < m) {
            pq.push({ path + grid[x][y + 1], x, y + 1 });
        }
    }

    return 0;
}
