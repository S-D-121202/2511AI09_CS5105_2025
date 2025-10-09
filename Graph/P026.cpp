#include <bits/stdc++.h>
using namespace std;

// Returns true if node is part of a cycle or leads to a cycle
bool dfs(int node, vector<vector<int>>& adj, vector<int>& color) {
    if (color[node] == 1) return true;  // visiting → cycle found
    if (color[node] == 2) return false; // already safe
    if (color[node] == 3) return true;  // already known unsafe

    color[node] = 1; // mark as visiting
    for (int neighbor : adj[node]) {
        if (dfs(neighbor, adj, color)) {
            color[node] = 3; // unsafe
            return true;
        }
    }
    color[node] = 2; // safe
    return false;
}

vector<int> eventualSafeNodes(int V, vector<vector<int>>& adj) {
    vector<int> color(V, 0);
    vector<int> safeNodes;

    for (int i = 0; i < V; i++) {
        if (!dfs(i, adj, color)) {
            safeNodes.push_back(i);
        }
    }
    return safeNodes; // already in ascending order
}

int main() {
    int V = 7;
    vector<vector<int>> adj = {
        {1,2}, {2,3}, {5}, {0}, {5}, {}, {}
    };

    vector<int> safe = eventualSafeNodes(V, adj);
    cout << "Safe nodes: ";
    for (int x : safe) cout << x << " ";
    cout << "\n";

    return 0;
}
