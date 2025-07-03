#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int rows, columns;
vector<vector<int>> heights;
vector<vector<int>> dp;

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

int dfsAlgorithm(int x, int y) {
    if (dp[x][y] != -1)
        return dp[x][y];

    int maxLength = 1;

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < columns && heights[nx][ny] < heights[x][y])
            maxLength = max(maxLength, 1 + dfsAlgorithm(nx, ny));
    }

    dp[x][y] = maxLength;
    return maxLength;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> rows >> columns;
    heights.assign(rows, vector<int>(columns));
    dp.assign(rows, vector<int>(columns, -1));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            cin >> heights[i][j];

    int longestPath = 0;

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            longestPath = max(longestPath, dfsAlgorithm(i, j));

    cout << longestPath << "\n";
    return 0;
}