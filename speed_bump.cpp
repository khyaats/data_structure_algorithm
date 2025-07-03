#include <iostream>
#include <vector>
#include <queue>      // For std::priority_queue
#include <tuple>      // For std::tuple and std::get
#include <limits>     // For std::numeric_limits
#include <utility>    // For std::pair, std::make_pair
#include <functional> // For std::greater

// Using a large integer value to represent infinity for costs
const int INF = std::numeric_limits<int>::max();

// Structure to represent an edge in the graph
struct Edge {
    int to;       // Destination node
    int bumps;    // Number of speed bumps on this edge
    int distance; // Length of this edge
};

// Type alias for the state stored in the priority queue:
// {total_bumps_so_far, total_distance_so_far, node_id}
using State = std::tuple<int, int, int>;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of locations (0 to n-1)
    int m; // Number of roads
    std::cin >> n >> m;

    // Adjacency list to store the graph
    // adj[u] contains a vector of Edges originating from u
    std::vector<std::vector<Edge>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c, d;
        std::cin >> u >> v >> c >> d; // u, v are locations; c is bumps; d is distance
        // Roads are bi-directional
        adj[u].push_back({ v, c, d });
        adj[v].push_back({ u, c, d });
    }

    // min_costs[i] stores a pair: {min_bumps_to_i, min_distance_for_those_bumps_to_i}
    std::vector<std::pair<int, int>> min_costs(n, { INF, INF });

    // Priority queue for Dijkstra's. Stores States.
    // Uses std::greater to make it a min-priority queue.
    // std::tuple comparison is lexicographical by default (sorts by first element, then second, etc.),
    // which is exactly what we need for {bumps, distance}.
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    // Starting from home (node 0)
    // The problem statement guarantees n >= 1.
    if (n > 0) { // Check to prevent access to min_costs[-1] if n was 0
        min_costs[0] = { 0, 0 }; // 0 bumps, 0 distance to reach home from itself
        pq.push({ 0, 0, 0 });    // Push initial state: {bumps, distance, node_id}
    }
    else { // n=0 case, though constraints say n>=1
        std::cout << "0 0" << std::endl; // Or appropriate error/empty output
        return 0;
    }


    while (!pq.empty()) {
        // Get the state with the lexicographically smallest cost
        State current_state_tuple = pq.top();
        pq.pop();

        int current_bumps = std::get<0>(current_state_tuple);
        int current_dist = std::get<1>(current_state_tuple);
        int u = std::get<2>(current_state_tuple);

        // If we've found a better path to u already, skip this one.
        // std::pair comparison is also lexicographical.
        if (std::make_pair(current_bumps, current_dist) > min_costs[u]) {
            continue;
        }

        // Explore neighbors of u
        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int edge_bumps = edge.bumps;
            int edge_dist = edge.distance;

            // Calculate cost to reach v through u and this edge
            int new_bumps_to_v = current_bumps + edge_bumps;
            int new_dist_to_v = current_dist + edge_dist;

            std::pair<int, int> new_cost_to_v = { new_bumps_to_v, new_dist_to_v };

            // If this path to v is better (lexicographically) than any found so far
            if (new_cost_to_v < min_costs[v]) {
                min_costs[v] = new_cost_to_v;
                pq.push({ new_bumps_to_v, new_dist_to_v, v });
            }
        }
    }

    // The university is at location n-1.
    // Problem guarantees connectivity, so a path will be found.
    // If n=1, university is node 0, min_costs[0] is {0,0}.
    if (n > 0) {
        std::cout << min_costs[n - 1].first << " " << min_costs[n - 1].second << std::endl;
    }
    // If n was 0, already handled.

    return 0;
}