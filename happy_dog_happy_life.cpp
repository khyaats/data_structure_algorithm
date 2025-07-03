// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <map>
#include<bits/stdc++.h>

using namespace std;

struct SegTreeNode {
    long long max_val;
};

vector<long long> funness_g;
vector<SegTreeNode> segtree_g;
vector<int> f_g;
map<int, int> funness_rank_g;
int N_g;
int D_g;

void build_segment_tree(int node_idx, int start, int end) {
    if (start == end) {
        segtree_g[node_idx] = { 0LL };
    }
    else {
        int mid = (start + end) / 2;
        build_segment_tree(2 * node_idx, start, mid);
        build_segment_tree(2 * node_idx + 1, mid + 1, end);
        segtree_g[node_idx] = { 0LL };
    }
}

void update_segment_tree(int node_idx, int start, int end, int target_rank, long long new_dp_val) {
    if (start == end) {
        segtree_g[node_idx].max_val = max(segtree_g[node_idx].max_val, new_dp_val);
        return;
    }
    int mid = (start + end) / 2;
    if (start <= target_rank && target_rank <= mid) {
        update_segment_tree(2 * node_idx, start, mid, target_rank, new_dp_val);
    }
    else {
        update_segment_tree(2 * node_idx + 1, mid + 1, end, target_rank, new_dp_val);
    }
    segtree_g[node_idx].max_val = max(segtree_g[2 * node_idx].max_val, segtree_g[2 * node_idx + 1].max_val);
}

long long query_segment_tree(int node_idx, int start, int end, int query_l_rank, int query_r_rank) {
    if (query_r_rank < start || end < query_l_rank || query_l_rank > query_r_rank) {
        return 0LL;
    }
    if (query_l_rank <= start && end <= query_r_rank) {
        return segtree_g[node_idx].max_val;
    }
    int mid = (start + end) / 2;
    long long p1 = query_segment_tree(2 * node_idx, start, mid, query_l_rank, query_r_rank);
    long long p2 = query_segment_tree(2 * node_idx + 1, mid + 1, end, query_l_rank, query_r_rank);
    return max(p1, p2);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N_g;
    funness_g.resize(N_g);
    vector<int> temp_f(N_g);

    for (int i = 0; i < N_g; ++i) {
        cin >> funness_g[i];
        temp_f[i] = funness_g[i];
    }

    if (N_g == 0) {
        cout << 0 << endl;
        return 0;
    }

    sort(temp_f.begin(), temp_f.end());
    temp_f.erase(unique(temp_f.begin(), temp_f.end()), temp_f.end());

    f_g = temp_f;
    D_g = f_g.size();

    funness_rank_g.clear();
    for (int i = 0; i < D_g; ++i) {
        funness_rank_g[f_g[i]] = i;
    }

    segtree_g.assign(4 * D_g + 5, { 0LL });
    if (D_g > 0) {
        build_segment_tree(1, 0, D_g - 1);
    }

    long long max_overall_happiness = 0LL;

    for (int i = 0; i < N_g; ++i) {
        int current_funness_val = funness_g[i];
        int funness_rank = funness_rank_g[current_funness_val];

        long long prev_max_dp_sum = 0LL;
        if (funness_rank > 0 && D_g > 0) {
            prev_max_dp_sum = query_segment_tree(1, 0, D_g - 1, 0, funness_rank - 1);
        }

        long long current_toy_term = (long long)current_funness_val * (N_g - i);

        long long dp_for_current_toy = current_toy_term + prev_max_dp_sum;

        if (D_g > 0) {
            update_segment_tree(1, 0, D_g - 1, funness_rank, dp_for_current_toy);
        }

        max_overall_happiness = max(max_overall_happiness, dp_for_current_toy);
    }

    cout << max_overall_happiness << endl;
}