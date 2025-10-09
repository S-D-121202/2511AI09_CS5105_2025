#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Recursive DFS function
void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& result) {
    visited[node] = true;
    result.push_back(node);

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, result);
        }
    }
}

// DFS traversal function
vector<int> dfsTraversal(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> result;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited, result);
        }
    }

    return result;
}

// Example usage
int main() {
    int n = 5; // Number of nodes (0 to 4)
    vector<vector<int>> adj(n);

    // Edges (undirected)
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 4};
    adj[3] = {1};
    adj[4] = {2};

    vector<int> traversal = dfsTraversal(n, adj);

    cout << "DFS Traversal: ";
    for (int node : traversal) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
