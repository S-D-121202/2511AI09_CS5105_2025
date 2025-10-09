#include <bits/stdc++.h>
using namespace std;

// DFS function to detect cycle
bool dfs(int node, int parent, vector<bool> &visited, vector<int> adj[]) {
    visited[node] = true;

    for (auto neighbor : adj[node]) {
        if (!visited[neighbor]) {
            if (dfs(neighbor, node, visited, adj)) 
                return true;
        }
        // If visited and not parent → cycle exists
        else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

// Main function to check cycle in graph
bool isCycle(int V, vector<int> adj[]) {
    vector<bool> visited(V, false);

    // Graph may be disconnected, so check all components
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (dfs(i, -1, visited, adj))
                return true;
        }
    }
    return false;
}

int main() {
    int V = 5; // number of vertices
    vector<int> adj[V];

    // Example edges
    adj[0].push_back(1);
    adj[1].push_back(0);

    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(3);
    adj[3].push_back(2);

    adj[3].push_back(4);
    adj[4].push_back(3);

    adj[4].push_back(1); // introduces a cycle
    adj[1].push_back(4);

    if (isCycle(V, adj))
        cout << "Graph contains cycle" << endl;
    else
        cout << "Graph does not contain cycle" << endl;

    return 0;
}
