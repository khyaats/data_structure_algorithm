#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// DP table: dp[i][len][turn]
// dp[i][len][0]: max score Preston gets from circular segment of length 'len' starting at index 'i' (original index) if Preston's turn.
// dp[i][len][1]: max score Preston gets from circular segment of length 'len' starting at index 'i' (original index) if Celvin's turn.
// Dimensions: n x (n+1) x 2. Initialize with -1.
vector<vector<vector<long long>>> dp;
vector<int> A; // Store original slice sizes

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n; // Read the number of slices

    A.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> A[i]; // Read slice sizes
    }

    if (n == 1) {
        cout << A[0] << endl;
        return 0;
    }

    // Initialize DP table
    dp.assign(n, vector<vector<long long>>(n + 1, vector<long long>(2, -1)));

    // Fill DP table by length
    // Length 1 Base Cases:
    for (int i = 0; i < n; ++i) {
        dp[i][1][0] = A[i]; // Preston's turn on single slice: takes it
        dp[i][1][1] = 0;     // Celvin's turn on single slice: takes it, Preston gets 0
    }

    // Length 2 to n
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i < n; ++i) { // Starting index of the circular segment
            int j = (i + len - 1) % n; // Ending index of the circular segment

            // Calculate dp[i][len][0] (Preston's turn)
            // Option 1: Preston takes A[i]
            // Remaining segment: length len-1, starts at (i+1)%n, Celvin's turn
            long long score_taking_left = (long long)A[i] + dp[(i + 1) % n][len - 1][1];

            // Option 2: Preston takes A[j]
            // Remaining segment: length len-1, starts at i, Celvin's turn
            long long score_taking_right = (long long)A[j] + dp[i][len - 1][1];

            dp[i][len][0] = max(score_taking_left, score_taking_right);

            // Calculate dp[i][len][1] (Celvin's turn)
            // Celvin takes the larger of A[i] and A[j]
            if (A[i] > A[j]) {
                // Celvin takes A[i]. Remaining segment: length len-1, starts at (i+1)%n, Preston's turn
                dp[i][len][1] = dp[(i + 1) % n][len - 1][0];
            }
            else {
                // Celvin takes A[j]. Remaining segment: length len-1, starts at i, Preston's turn
                dp[i][len][1] = dp[i][len - 1][0];
            }
        }
    }

    // Find the maximum score Preston can get by choosing the first slice
    long long max_preston_cake = 0;

    // Preston chooses A[k] as the first slice (k from 0 to n-1)
    for (int k = 0; k < n; ++k) {
        // After Preston takes A[k], the remaining slices form a circular segment
        // of length n-1 starting at index (k+1)%n.
        // The game on this segment starts with Celvin's turn.
        // The maximum score Preston gets from this remaining game is dp[(k + 1) % n][n - 1][1].
        long long preston_score_from_remaining_game = dp[(k + 1) % n][n - 1][1];

        // Preston's total score for this first move = size of A[k] + score from remaining game
        long long current_preston_score = (long long)A[k] + preston_score_from_remaining_game;

        max_preston_cake = max(max_preston_cake, current_preston_score);
    }

    cout << max_preston_cake << endl;

    return 0;
}