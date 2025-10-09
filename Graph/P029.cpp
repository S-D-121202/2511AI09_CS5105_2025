#include <bits/stdc++.h>
using namespace std;

// DFS-based Topological Sort
void topoSort(int node, vector<vector<pair<int,int>>>& adj, vector<int>& visited, stack<int>& st) {
    visited[node] = 1;
    for (auto &[neighbor, weight] : adj[node]) {
        if (!visited[neighbor]) topoSort(neighbor, adj, visited, st);
    }
    st.push(node);
}

vector<int> shortestPathDAG(int V, vector<vector<pair<int,int>>>& adj) {
    vector<int> visited(V, 0);
    stack<int> st;

    // Topological sort
    for (int i = 0; i < V; i++) {
        if (!visited[i]) topoSort(i, adj, visited, st);
    }

    vector<int> dist(V, INT_MAX);
    int source = 0;
    dist[source] = 0;

    // Relax edges in topological order
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (dist[u] != INT_MAX) { // Only relax from reachable nodes
            for (auto &[v, wt] : adj[u]) {
                if (dist[u] + wt < dist[v]) dist[v] = dist[u] + wt;
            }
        }
    }

    // Replace INT_MAX with -1 for unreachable nodes
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) dist[i] = -1;
    }

    return dist;
}

int main() {
    int V = 6;
    vector<vector<pair<int,int>>> adj(V);

    // Example weighted DAG edges
    // Edge format: {destination, weight}
    adj[0] = {{1, 2}, {4, 1}};
    adj[1] = {{2, 3}, {4, 2}};
    adj[2] = {{3, 6}};
    adj[4] = {{2, 2}, {5, 4}};
    adj[5] = {{3, 1}};

    vector<int> dist = shortestPathDAG(V, adj);

    cout << "Shortest distances from node 0: ";
    for (int d : dist) cout << d << " ";
    cout << "\n";

    return 0;
}
