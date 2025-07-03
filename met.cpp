#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];
int n;

// BFS to find farthest node and its distance
pair<int, int> bfs(int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthestNode = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : tree[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthestNode]) {
                    farthestNode = v;
                }
            }
        }
    }

    return { farthestNode, dist[farthestNode] };
}

int main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // First BFS to find one endpoint of the diameter
    int nodeA = bfs(1).first;
    // Second BFS to get the diameter
    int diameter = bfs(nodeA).second;

    // Radius = ceil(diameter / 2)
    cout << (diameter + 1) / 2 << endl;
    return 0;
}
