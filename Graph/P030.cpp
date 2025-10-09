#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<vector<pair<int,int>>>& adj, int S) {
    vector<int> distance(V, INT_MAX);
    distance[S] = 0;

    // Min-heap: (distance, node)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, S});

    while (!pq.empty()) {
        auto [distU, u] = pq.top(); pq.pop();

        // Skip if we already found a better distance
        if (distU > distance[u]) continue;

        for (auto &[v, wt] : adj[u]) {
            if (distance[u] + wt < distance[v]) {
                distance[v] = distance[u] + wt;
                pq.push({distance[v], v});
            }
        }
    }

    return distance;
}

int main() {
    int V = 5;
    int S = 0;

    // Weighted undirected graph
    vector<vector<pair<int,int>>> adj(V);
    auto addEdge = [&](int u, int v, int w){
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // because undirected
    };

    addEdge(0, 1, 2);
    addEdge(0, 4, 1);
    addEdge(1, 2, 4);
    addEdge(1, 3, 7);
    addEdge(4, 2, 3);
    addEdge(2, 3, 1);

    vector<int> dist = dijkstra(V, adj, S);

    cout << "Shortest distances from node " << S << ": ";
    for (int d : dist) cout << d << " ";
    cout << "\n";

    return 0;
}
