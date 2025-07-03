#include <iostream>
#include <vector>
#include <algorithm>

// Global-like variables for DFS functions for convenience.
// In a class structure, these would be member variables.
int N_nodes_global;
std::vector<std::vector<int>> adj_orig_global_graph;
std::vector<std::vector<int>> adj_rev_global_graph;
std::vector<bool> visited_dfs_global;
int last_finished_node_in_dfs1;       // Stores the candidate capital from Pass 1
int count_nodes_reachable_in_dfs2;    // Stores result for Pass 2
std::vector<int> collected_capital_cities; // Stores result for Pass 3

// Pass 1: DFS on G_rev to find the last finished node.
// This node is a candidate for being a mother vertex in G_rev.
void find_last_finished_node_dfs(int u) {
    visited_dfs_global[u] = true;
    for (int v : adj_rev_global_graph[u]) {
        if (!visited_dfs_global[v]) {
            find_last_finished_node_dfs(v);
        }
    }
    last_finished_node_in_dfs1 = u; // u finishes now.
}

// Pass 2: DFS on G_rev starting from candidate_capital_node.
// Counts how many nodes are reachable from it.
void count_reachable_nodes_dfs(int u) {
    visited_dfs_global[u] = true;
    count_nodes_reachable_in_dfs2++;
    for (int v : adj_rev_global_graph[u]) {
        if (!visited_dfs_global[v]) {
            count_reachable_nodes_dfs(v);
        }
    }
}

// Pass 3: DFS on G_orig starting from candidate_capital_node.
// Collects all nodes reachable from it in G_orig. These are the capital cities.
void collect_actual_capitals_dfs(int u) {
    visited_dfs_global[u] = true;
    collected_capital_cities.push_back(u);
    for (int v : adj_orig_global_graph[u]) {
        if (!visited_dfs_global[v]) {
            collect_actual_capitals_dfs(v);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int m_edges;
    std::cin >> N_nodes_global >> m_edges;

    adj_orig_global_graph.resize(N_nodes_global + 1);
    adj_rev_global_graph.resize(N_nodes_global + 1);

    for (int k = 0; k < m_edges; ++k) {
        int u, v;
        std::cin >> u >> v;
        adj_orig_global_graph[u].push_back(v);
        adj_rev_global_graph[v].push_back(u); // Edge for the reversed graph
    }

    // Pass 1: Find a candidate capital city.
    // This will be the last node finished in a DFS traversal of G_rev.
    visited_dfs_global.assign(N_nodes_global + 1, false);
    if (N_nodes_global > 0) { // Initialize if there's at least one node
        last_finished_node_in_dfs1 = 1;
    }
    for (int i = 1; i <= N_nodes_global; ++i) {
        if (!visited_dfs_global[i]) {
            find_last_finished_node_dfs(i);
        }
    }
    int candidate_capital_node = last_finished_node_in_dfs1;

    // Pass 2: Verify if the candidate can reach all other nodes in G_rev.
    visited_dfs_global.assign(N_nodes_global + 1, false);
    count_nodes_reachable_in_dfs2 = 0;
    if (N_nodes_global > 0) {
        count_reachable_nodes_dfs(candidate_capital_node);
    }

    if (count_nodes_reachable_in_dfs2 < N_nodes_global) {
        // Candidate cannot reach all nodes, so no capital city exists.
        std::cout << 0 << std::endl;
        std::cout << std::endl; // Empty line for the list, as per problem format.
    }
    else {
        // Pass 3: The candidate is a capital. Find all other capitals.
        // These are nodes reachable from candidate_capital_node in G_orig.
        visited_dfs_global.assign(N_nodes_global + 1, false);
        collected_capital_cities.clear();
        if (N_nodes_global > 0) {
            collect_actual_capitals_dfs(candidate_capital_node);
        }

        std::sort(collected_capital_cities.begin(), collected_capital_cities.end());

        std::cout << collected_capital_cities.size() << std::endl;
        for (size_t i = 0; i < collected_capital_cities.size(); ++i) {
            std::cout << collected_capital_cities[i] << (i == collected_capital_cities.size() - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    return 0;
}