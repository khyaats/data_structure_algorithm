#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <limits>

using namespace std;

typedef pair<long long, int> PLI;
const long long INF = 1e18;

vector<vector<PLI>> graphForPlaces;

vector<long long> dijkstraAlgorithm(int start, int n) {
    vector<long long> distance(n, INF);
    priority_queue<PLI, vector<PLI>, greater<PLI>> placesQueue;

    distance[start] = 0;
    placesQueue.push({ 0, start });

    while (!placesQueue.empty()) {
        auto [d, u] = placesQueue.top();
        placesQueue.pop();

        if (d > distance[u]) continue;

        for (auto [w, v] : graphForPlaces[u]) {
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                placesQueue.push({ distance[v], v });
            }
        }
    }
    return distance;
}

int main() {
    int n, m;
    cin >> n >> m;

    graphForPlaces.resize(n);

    int p;
    cin >> p;

    vector<int> places(p);
    for (int i = 0; i < p; i++) {
        cin >> places[i];
    }

    int t;
    cin >> t;
    int timeInSeconds = t * 60;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long l;
        cin >> u >> v >> l;
        graphForPlaces[u].emplace_back(l, v);
        graphForPlaces[v].emplace_back(l, u);
    }

    // Finding maximum shortest distance between any pair of places
    long long maximumDistance = 0;
    for (int i = 0; i < p; i++) {
        vector<long long> distance = dijkstraAlgorithm(places[i], n);
        for (int j = 0; j < p; j++) 
            if (i != j) 
                maximumDistance = max(maximumDistance, distance[places[j]]);
    }

    // Calculate the speed
    double speed = (double)maximumDistance / timeInSeconds;
    cout << fixed << setprecision(3) << speed << endl;
    return 0;
}