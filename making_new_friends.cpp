#include <iostream>
#include <vector>
#include <algorithm> // For std::sort, std::min
#include <numeric>   // For std::iota, used in DSU initialization

// Structure to represent a potential friendship (an edge in the graph)
struct Edge {
    int u_node_idx; // Index of the first student
    int v_node_idx; // Index of the second student
    int cost;       // Candies needed to form this friendship (min of shyness of the two)
};

// Custom comparator function for sorting edges by their cost in ascending order
bool compareEdges(const Edge& a, const Edge& b) {
    return a.cost < b.cost;
}

// Disjoint Set Union (DSU) data structure to manage connected components of students
struct DSU {
    std::vector<int> parent;
    std::vector<int> component_size; // Used for union-by-size heuristic

    // Constructor: Initializes DSU for n elements (students)
    DSU(int n) {
        parent.resize(n);
        // Initially, each student is in their own component (parent of self)
        std::iota(parent.begin(), parent.end(), 0);
        component_size.assign(n, 1); // Each component initially has size 1
    }

    // Finds the representative (root) of the set containing student v
    // Applies path compression for efficiency
    int find_set(int v) {
        if (v == parent[v]) // If v is the root of its own set
            return v;
        // Path compression: make v point directly to the root
        return parent[v] = find_set(parent[v]);
    }

    // Unites the sets containing students u and v
    // Returns true if u and v were in different sets (and thus merged), false otherwise
    bool unite_sets(int u, int v) {
        u = find_set(u); // Find representative for u
        v = find_set(v); // Find representative for v

        if (u != v) { // If u and v are in different components
            // Union by size: attach the root of the smaller tree to the root of the larger tree
            if (component_size[u] < component_size[v])
                std::swap(u, v); // Ensure u is the larger (or equal size) component's root

            parent[v] = u; // Make u the parent of v's root
            component_size[u] += component_size[v]; // Update size of the merged component
            return true; // Merge occurred
        }
        return false; // u and v were already in the same component
    }
};

int main() {
    // Optimize C++ standard streams for faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int r, c; // Number of rows and columns in the classroom
    std::cin >> r >> c;

    // Read the shyness level for each student
    std::vector<std::vector<int>> shyness(r, std::vector<int>(c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            std::cin >> shyness[i][j];
        }
    }

    // Generate all potential edges (friendships between adjacent students)
    std::vector<Edge> edges;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            // Map 2D coordinates (i,j) to a 1D node index
            int current_node_idx = i * c + j;

            // Potential friendship with the student to the right
            if (j + 1 < c) { // If there is a student to the right
                int right_node_idx = i * c + (j + 1);
                // Cost is the minimum of the shyness values of the two students
                int cost = std::min(shyness[i][j], shyness[i][j + 1]);
                edges.push_back({ current_node_idx, right_node_idx, cost });
            }

            // Potential friendship with the student below
            if (i + 1 < r) { // If there is a student below
                int bottom_node_idx = (i + 1) * c + j;
                // Cost is the minimum of the shyness values of the two students
                int cost = std::min(shyness[i][j], shyness[i + 1][j]);
                edges.push_back({ current_node_idx, bottom_node_idx, cost });
            }
        }
    }

    // Sort all potential edges by their cost in non-decreasing order (Kruskal's algorithm step)
    std::sort(edges.begin(), edges.end(), compareEdges);

    int num_total_nodes = r * c;

    // If there's only one student (or zero, though constraints say r,c >= 1),
    // no candies are needed as they are already "connected" (trivially).
    if (num_total_nodes <= 1) {
        std::cout << 0 << std::endl;
        return 0;
    }

    // Initialize DSU structure for all students
    DSU dsu(num_total_nodes);
    long long total_minimum_candies = 0; // Use long long for sum of costs
    int edges_count_in_mst = 0;          // Counter for edges added to the MST

    // Kruskal's algorithm: Iterate through sorted edges
    for (const auto& edge : edges) {
        // If the two students connected by this edge are in different components
        if (dsu.unite_sets(edge.u_node_idx, edge.v_node_idx)) {
            total_minimum_candies += edge.cost; // Add cost of this edge to total
            edges_count_in_mst++;               // Increment count of edges in MST

            // If MST is complete (connected all N nodes with N-1 edges)
            if (edges_count_in_mst == num_total_nodes - 1) {
                break; // Stop, as further edges are not needed
            }
        }
    }

    // Output the minimum total candies required
    std::cout << total_minimum_candies << std::endl;

    return 0;
}