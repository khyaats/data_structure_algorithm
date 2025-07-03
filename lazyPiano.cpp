#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath> // For std::abs

// Using long long for fatigue sums to be safe, though int might suffice
// given problem constraints (max fatigue ~2.5e7).
const long long INF = 1e18; // A large enough value for infinity

void solve() {
    int n; // Number of presses
    int k; // Number of keys on the piano
    std::cin >> n >> k;
    std::vector<int> a(n); // Keys to be pressed
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    if (n == 0) { // Based on constraints, n >= 1, but as a safeguard
        std::cout << 0 << std::endl;
        return;
    }

    // dp_prev[j] will store the minimum fatigue after the (i-1)-th note (a[i-1])
    // was played, where one hand is on a[i-1] and the other hand is on key j.
    // Initialize for the first note a[0]:
    // After a[0] is played, one hand is on a[0], and the other hand can be
    // on any key 'j' with 0 initial fatigue.
    std::vector<long long> dp_prev(k + 1, 0);

    // Iterate for notes from the second note a[1] up to a[n-1]
    for (int i = 1; i < n; ++i) {
        std::vector<long long> dp_curr(k + 1, INF); // dp_curr for note a[i]
        int current_note_key = a[i];
        int prev_note_key = a[i - 1];

        // Iterate over all possible positions of the 'other' hand (prev_other_hand_pos)
        // after the previous note (a[i-1]) was played.
        for (int prev_other_hand_pos = 1; prev_other_hand_pos <= k; ++prev_other_hand_pos) {
            if (dp_prev[prev_other_hand_pos] == INF) {
                continue; // This state was unreachable
            }

            // Case 1: The hand that played prev_note_key (it's currently at prev_note_key)
            // also plays the current_note_key.
            // This hand moves from prev_note_key to current_note_key.
            // The other hand (which was at prev_other_hand_pos) stays there.
            // So, after current_note_key is played, the 'other' hand is still at prev_other_hand_pos.
            long long fatigue_case1 = dp_prev[prev_other_hand_pos] + std::abs(current_note_key - prev_note_key);
            dp_curr[prev_other_hand_pos] = std::min(dp_curr[prev_other_hand_pos], fatigue_case1);

            // Case 2: The hand that was at prev_other_hand_pos plays the current_note_key.
            // This hand moves from prev_other_hand_pos to current_note_key.
            // The other hand (which was at prev_note_key) now becomes the new 'other' hand.
            // So, after current_note_key is played, the 'other' hand is now at prev_note_key.
            long long fatigue_case2 = dp_prev[prev_other_hand_pos] + std::abs(current_note_key - prev_other_hand_pos);
            dp_curr[prev_note_key] = std::min(dp_curr[prev_note_key], fatigue_case2);
        }
        dp_prev = dp_curr; // Current state becomes previous state for the next iteration
    }

    // The final answer is the minimum fatigue in dp_prev after all notes are played.
    // dp_prev now holds the fatigue states after the last note a[n-1] was played.
    // One hand is at a[n-1], and the other hand is at some key j (index of dp_prev).
    long long min_total_fatigue = INF;
    if (n == 0) { // Should ideally not be hit due to constraints 1 <= n
        min_total_fatigue = 0;
    }
    else { // If n=1, loop for i=1..n-1 doesn't run, dp_prev is still all 0s. Min will be 0.
        for (int j = 1; j <= k; ++j) {
            min_total_fatigue = std::min(min_total_fatigue, dp_prev[j]);
        }
    }
    std::cout << min_total_fatigue << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t; // Number of test cases
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}