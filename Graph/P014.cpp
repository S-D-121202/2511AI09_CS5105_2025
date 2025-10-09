#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to check for cycle in an undirected graph using BFS
bool isCyclicBFS(int start, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<pair<int, int>> q; // {node, parent}
    visited[start] = true;
    q.push({start, -1});

    while (!q.empty()) {
        int node = q.front().first;
        int parent = q.front().second;
        q.pop();

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push({neighbor, node});
            } else if (neighbor != parent) {
                // If visited and not parent, cycle exists
                return true;
            }
        }
    }
    return false;
}

// Main function to check for cycle in all components
bool containsCycle(int V, vector<vector<int>>& adj) {
    vector<bool> visited(V, false);

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            if (isCyclicBFS(i, adj, visited))
                return true;
        }
    }
    return false;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adj(V);
    cout << "Enter edges (u v):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Since the graph is undirected
    }

    if (containsCycle(V, adj))
        cout << "Graph contains a cycle." << endl;
    else
        cout << "Graph does not contain a cycle." << endl;

    return 0;
}
