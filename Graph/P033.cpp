#include <bits/stdc++.h>
using namespace std;

vector<int> bellmanFord(int V, int E, vector<vector<int>>& edges, int S) {
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V-1; i++) {
        for (auto &edge : edges) {
            int u = edge[0], v = edge[1], wt = edge[2];
            if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Optional: check for negative weight cycles
    for (auto &edge : edges) {
        int u = edge[0], v = edge[1], wt = edge[2];
        if (dist[u] != INT_MAX && dist[u] + wt < dist[v]) {
            cout << "Graph contains negative weight cycle\n";
            break;
        }
    }

    return dist;
}

int main() {
    int V = 5, E = 8;
    vector<vector<int>> edges = {
        {0,1,-1},{0,2,4},{1,2,3},{1,3,2},
        {1,4,2},{3,2,5},{3,1,1},{4,3,-3}
    };
    int S = 0;

    vector<int> dist = bellmanFord(V, E, edges, S);

    cout << "Shortest distances from node " << S << ": ";
    for (int d : dist) cout << d << " ";
    cout << "\n";
}
