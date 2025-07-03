#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int depthFirstSearch(int node, const vector<vector<int>>& adjescent, vector<bool>& visited) {
    visited[node] = true;
    int size = 1;

    for (int neighbor : adjescent[node])
        if (!visited[neighbor])
            size += depthFirstSearch(neighbor, adjescent, visited);

    return size;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    
    //Reading parent information
    vector<int> parent(n, -1);
    for (int i = 1; i < n; i++)
        cin >> parent[i];

    // Read traitors information
    unordered_set<int> traitorSet;
    for (int i = 0; i < m; i++) {
        int traitors;
        cin >> traitors;
        traitorSet.insert(traitors);
    }

    // Build adjacency list (excluding traitors)
    vector<vector<int>> adjescent(n);
    for (int i = 1; i < n; i++) {
        if (traitorSet.count(i) || traitorSet.count(parent[i]))
            continue; 
        adjescent[parent[i]].push_back(i);
        adjescent[i].push_back(parent[i]);
    }

    int max_component_size = 0;
    vector<bool> visited(n, false);

    for (int traitors : traitorSet) 
        visited[traitors] = true;

    // Finding all the connected components
    for (int i = 0; i < n; i++) 
        if (!visited[i]) {
            int component_size = depthFirstSearch(i, adjescent, visited);
            max_component_size = max(max_component_size, component_size);
        }

    cout << max_component_size << endl; //PRinting 

    return 0;
}