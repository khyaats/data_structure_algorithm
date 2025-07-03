#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MARATHON_LENGTH = 42195;

struct Interval {
    int start, end;
};

int main() {
    int n;
    cin >> n;

    vector<Interval> intervals;
    for (int i = 0; i < n; ++i) {
        int x, k;
        cin >> x >> k;
        int start = max(0, x - k);
        int end = min(MARATHON_LENGTH, x + k);
        if (end > start) {  // Only add valid intervals
            intervals.push_back({ start, end });
        }
    }

    // First check if entire course can be covered at least once
    sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
        return a.start < b.start;
        });

    int covered_until = 0;
    int i = 0;

    while (covered_until < MARATHON_LENGTH && i < n) {
        if (intervals[i].start > covered_until) {
            // Gap in coverage
            cout << -1 << endl;
            return 0;
        }

        // Find the interval that extends coverage the furthest
        int maxEnd = covered_until;
        int bestIdx = -1;

        while (i < n && intervals[i].start <= covered_until) {
            if (intervals[i].end > maxEnd) {
                maxEnd = intervals[i].end;
                bestIdx = i;
            }
            i++;
        }

        if (bestIdx == -1) break;
        covered_until = maxEnd;
    }

    if (covered_until < MARATHON_LENGTH) {
        cout << -1 << endl;
        return 0;
    }

    // Now solve for dual coverage
    vector<int> coverage(MARATHON_LENGTH + 1, 0);
    vector<bool> selected(n, false);
    int cameras_used = 0;

    while (true) {
        // Check if all points are covered by at least 2 cameras
        bool all_covered = true;
        int first_uncovered = 0;

        for (int j = 0; j < MARATHON_LENGTH; j++) {
            if (coverage[j] < 2) {
                all_covered = false;
                first_uncovered = j;
                break;
            }
        }

        if (all_covered) break;

        // Find the camera that covers the most currently uncovered points
        int best_camera = -1;
        int best_coverage = 0;

        for (int j = 0; j < n; j++) {
            if (selected[j]) continue;

            // Skip if this camera doesn't cover the first uncovered point
            if (intervals[j].start > first_uncovered || intervals[j].end <= first_uncovered) continue;

            int coverage_improvement = 0;
            for (int pos = intervals[j].start; pos < intervals[j].end; pos++)
                if (coverage[pos] < 2)
                    coverage_improvement++;

            if (coverage_improvement > best_coverage) {
                best_coverage = coverage_improvement;
                best_camera = j;
            }
        }

        if (best_camera == -1) {
            // Cannot provide dual coverage for all points
            cout << -1 << endl;
            return 0;
        }

        // Select this camera
        selected[best_camera] = true;
        cameras_used++;

        // Update coverage
        for (int pos = intervals[best_camera].start; pos < intervals[best_camera].end; pos++)
            coverage[pos]++;

    }

    cout << cameras_used << endl;
    return 0;
}