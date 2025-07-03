#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::min
#include <utility>   // For std::pair

// Hashing parameters (use two hash functions for robustness)
long long P1 = 31, M1 = 1e9 + 7;
long long P2 = 53, M2 = 1e9 + 9; // Different prime base and modulus

// Global vectors for powers and prefix hashes.
// Sized for the maximum possible sum of |s| or max individual |s|.
std::vector<long long> powers1;
std::vector<long long> powers2;
std::vector<long long> h_pref1; // h_pref1[i] stores hash of s[0...i-1]
std::vector<long long> h_pref2;

const int MAX_S_LEN = 1000005;

// Precompute powers of P1 and P2 modulo M1 and M2
void precompute_powers_if_needed(int n_max) {
    // Only compute if not already computed or if a larger size is needed.
    // For sum of N constraint, precomputing once to MAX_S_LEN is simplest.
    if (powers1.empty() || powers1.size() < n_max + 1) {
        powers1.resize(n_max + 1);
        powers2.resize(n_max + 1);
        powers1[0] = 1;
        powers2[0] = 1;
        for (int i = 1; i <= n_max; ++i) {
            powers1[i] = (powers1[i - 1] * P1) % M1;
            powers2[i] = (powers2[i - 1] * P2) % M2;
        }
    }
}

// Compute prefix hashes for the given string s
void compute_prefix_hashes(const std::string& s) {
    int n = s.length();
    h_pref1.assign(n + 1, 0); // h_pref1[0] = 0 (hash of empty prefix)
    h_pref2.assign(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        // Map '0'-'9' to integer values (e.g., 1-10 to avoid issues with 0 if base is small)
        int char_val = s[i] - '0' + 1;
        h_pref1[i + 1] = (h_pref1[i] * P1 + char_val) % M1;
        h_pref2[i + 1] = (h_pref2[i] * P2 + char_val) % M2;
    }
}

// Get hash of substring s[l...r] (0-indexed)
std::pair<long long, long long> get_substring_hash(int l, int r) {
    int len = r - l + 1;
    // Hash for s[0...r] is h_pref[r+1]
    // Hash for s[0...l-1] is h_pref[l]
    long long sub_hash1 = (h_pref1[r + 1] - (h_pref1[l] * powers1[len]) % M1 + M1) % M1;
    long long sub_hash2 = (h_pref2[r + 1] - (h_pref2[l] * powers2[len]) % M2 + M2) % M2;
    return { sub_hash1, sub_hash2 };
}

void solve_test_case() {
    std::string s;
    std::cin >> s;
    int n = s.length();

    if (n == 0) {
        std::cout << 0 << std::endl;
        return;
    }

    compute_prefix_hashes(s); // Compute hashes for the current string s

    int k_ans = 0;
    int current_l = 0;
    int current_r = n - 1;

    while (current_l <= current_r) {
        int current_len = current_r - current_l + 1;
        if (current_len == 0) { // Empty segment
            break;
        }
        if (current_len == 1) { // Single character segment
            k_ans++;
            break;
        }

        bool matched_in_segment = false;
        // Try to find the smallest L for the current segment
        for (int L = 1; L <= current_len / 2; ++L) {
            // Prefix: s[current_l ... current_l + L - 1]
            // Suffix: s[current_r - L + 1 ... current_r]
            std::pair<long long, long long> hash_prefix = get_substring_hash(current_l, current_l + L - 1);
            std::pair<long long, long long> hash_suffix = get_substring_hash(current_r - L + 1, current_r);

            if (hash_prefix == hash_suffix) {
                k_ans += 2; // Add two parts (s_i and s_{k-i+1})
                current_l += L;
                current_r -= L;
                matched_in_segment = true;
                break; // Found the smallest L, move to the inner segment
            }
        }

        if (!matched_in_segment) {
            // The remaining s[current_l...current_r] forms one block
            k_ans++;
            break; // No further partitioning of this type is possible
        }
    }
    std::cout << k_ans << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Precompute powers once for the maximum possible string length encountered
    precompute_powers_if_needed(MAX_S_LEN - 1); // -1 because max index can be MAX_S_LEN-1 for length MAX_S_LEN
    // powers[k] means p^k, needs up to N. So N is correct.

    int t;
    std::cin >> t;
    while (t--) {
        solve_test_case();
    }

    return 0;
}