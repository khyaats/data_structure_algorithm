#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

const int N = 5;

vector<pair<int, int>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}
};

// track 1-5: row 0 to 4 (entire row), track 6-10: column 0 to 4 (entire column)
bool isAttacked(int row, int column, int track) {
    if (track >= 1 && track <= 5) return row == track - 1;
    if (track >= 6 && track <= 10) return column == track - 6;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> attacks(n);
    for (int i = 0; i < n; ++i)
        cin >> attacks[i].first >> attacks[i].second;

    // Sort by time
    sort(attacks.begin(), attacks.end());

    set<pair<int, int>> current;
    // Initializing all 25 positions at time 0
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            current.insert({ i, j });

    int timePrev = 0;

    for (int i = 0; i < n; ) {
        int timeNow = attacks[i].first;

        // Advance time step by step from timePrev to timeNow
        for (int t = timePrev; t < timeNow; ++t) {
            set<pair<int, int>> next;

            for (auto [row, column] : current) {
                for (auto [dr, dc] : directions) {
                    int nextRow = row + dr, nextColumn = column + dc;
                    if (nextRow >= 0 && nextRow < N && nextColumn >= 0 && nextColumn < N)
                        next.insert({ nextRow, nextColumn });
                }
            }

            current = next;
            if (current.empty()) {
                cout << t << '\n';
                return 0;
            }
        }

        // Apply all attacks at current time timeNow
        while (i < n && attacks[i].first == timeNow) {
            int track = attacks[i].second;
            set<pair<int, int>> filtered;
            for (auto [row, column] : current) {
                if (!isAttacked(row, column, track))
                    filtered.insert({ row, column });
            }
            current = filtered;
            ++i;
        }

        if (current.empty()) {
            cout << timeNow << '\n';
            return 0;
        }

        timePrev = timeNow;
    }

    // Survived through all attacks
    cout << timePrev + 1 << '\n';
    return 0;
}