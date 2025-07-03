#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

// Using a large enough integer to represent infinity for plate counts.
const int INF_PLATES = 1e9;

struct PlateInfo {
    int id; // Original 1-based index
    int scaled_weight; // original_weight * 2, then rounded to int
};

// Helper function to print a list of plate indices
void print_plate_indices(const std::vector<int>& indices) {
    for (size_t i = 0; i < indices.size(); ++i) {
        std::cout << indices[i] << (i == indices.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n_plates_available;
    double x_total_target_weight;
    std::cin >> n_plates_available >> x_total_target_weight;

    // Pre-condition: x_total_target_weight must effectively be an integer.
    // If x_total_target_weight = K.5 (a half-integer), then x_total_target_weight/2 is not a multiple of 0.5.
    // Check: x_total_target_weight * 2 must be an even integer.
    long long x_times_2_rounded = static_cast<long long>(std::round(x_total_target_weight * 2.0));

    // If x is non-zero and x*2 is odd, then x must have been K.5, which is invalid.
    if (std::abs(x_total_target_weight) > 1e-9 && (x_times_2_rounded % 2 != 0)) {
        std::cout << -1 << std::endl;
        return 0;
    }

    // Handle x_total_target_weight = 0.0 case
    if (std::abs(x_total_target_weight) < 1e-9) {
        std::cout << 0 << std::endl;
        print_plate_indices({}); // Empty line for left plates
        print_plate_indices({}); // Empty line for right plates
        return 0;
    }

    // Target sum for one side, using scaled weights, is the original total target weight.
    int target_sum_scaled_per_side = static_cast<int>(std::round(x_total_target_weight));

    std::vector<PlateInfo> plates_data(n_plates_available);
    for (int i = 0; i < n_plates_available; ++i) {
        plates_data[i].id = i + 1; // 1-based indexing for output
        double original_w;
        std::cin >> original_w;
        plates_data[i].scaled_weight = static_cast<int>(std::round(original_w * 2.0));
    }

    // dp[k][sum_L][sum_R] = min_plates using first k plates
    std::vector<std::vector<std::vector<int>>> dp(
        n_plates_available + 1,
        std::vector<std::vector<int>>(
            target_sum_scaled_per_side + 1,
            std::vector<int>(target_sum_scaled_per_side + 1, INF_PLATES)
        )
    );

    // parent_choice[k][sum_L][sum_R]: 0=not used, 1=used for left, 2=used for right
    std::vector<std::vector<std::vector<unsigned char>>> parent_choice(
        n_plates_available + 1,
        std::vector<std::vector<unsigned char>>(
            target_sum_scaled_per_side + 1,
            std::vector<unsigned char>(target_sum_scaled_per_side + 1, 0)
        )
    );

    dp[0][0][0] = 0; // Base case: 0 plates for 0 sum on both sides

    for (int k = 1; k <= n_plates_available; ++k) {
        const auto& current_plate = plates_data[k - 1]; // 0-indexed access from plates_data
        int p_weight = current_plate.scaled_weight;

        for (int sL = 0; sL <= target_sum_scaled_per_side; ++sL) {
            for (int sR = 0; sR <= target_sum_scaled_per_side; ++sR) {
                // Option 1: Don't use plate k
                dp[k][sL][sR] = dp[k - 1][sL][sR];
                parent_choice[k][sL][sR] = 0;

                // Option 2: Use plate k for left side
                // Plate weight must be positive to contribute meaningfully if adding it costs 1 plate.
                // If scaled weight is 0, it can be used but doesn't change sum.
                if (sL >= p_weight && dp[k - 1][sL - p_weight][sR] != INF_PLATES) {
                    if (dp[k - 1][sL - p_weight][sR] + 1 < dp[k][sL][sR]) {
                        dp[k][sL][sR] = dp[k - 1][sL - p_weight][sR] + 1;
                        parent_choice[k][sL][sR] = 1;
                    }
                }

                // Option 3: Use plate k for right side
                if (sR >= p_weight && dp[k - 1][sL][sR - p_weight] != INF_PLATES) {
                    if (dp[k - 1][sL][sR - p_weight] + 1 < dp[k][sL][sR]) {
                        dp[k][sL][sR] = dp[k - 1][sL][sR - p_weight] + 1;
                        parent_choice[k][sL][sR] = 2;
                    }
                }
            }
        }
    }

    if (dp[n_plates_available][target_sum_scaled_per_side][target_sum_scaled_per_side] == INF_PLATES) {
        std::cout << -1 << std::endl;
    }
    else {
        std::cout << dp[n_plates_available][target_sum_scaled_per_side][target_sum_scaled_per_side] << std::endl;

        std::vector<int> left_plates_indices;
        std::vector<int> right_plates_indices;
        int cur_sL = target_sum_scaled_per_side;
        int cur_sR = target_sum_scaled_per_side;

        // Backtrack to find the plates used
        for (int k_idx = n_plates_available; k_idx > 0; --k_idx) {
            unsigned char choice = parent_choice[k_idx][cur_sL][cur_sR];
            const auto& plate_considered = plates_data[k_idx - 1]; // 0-indexed
            int current_p_weight = plate_considered.scaled_weight;

            if (choice == 1) { // Plate was used for left
                left_plates_indices.push_back(plate_considered.id);
                cur_sL -= current_p_weight;
            }
            else if (choice == 2) { // Plate was used for right
                right_plates_indices.push_back(plate_considered.id);
                cur_sR -= current_p_weight;
            }
            // If choice == 0, plate was not used for this state; sums remain for dp[k_idx-1]
        }
        // The plates were added in reverse order during backtracking
        std::reverse(left_plates_indices.begin(), left_plates_indices.end());
        std::reverse(right_plates_indices.begin(), right_plates_indices.end());

        print_plate_indices(left_plates_indices);
        print_plate_indices(right_plates_indices);
    }

    return 0;
}