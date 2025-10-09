#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, vector<vector<int>>& adj, vector<int>& state) {
    state[node] = 1; // mark as visiting

    for (int neighbor : adj[node]) {
        if (state[neighbor] == 0) {
            if (dfs(neighbor, adj, state))
                return true; // cycle found
        }
        else if (state[neighbor] == 1) {
            return true; // back edge found → cycle
        }
    }

    state[node] = 2; // mark as fully visited
    return false;
}

bool hasCycle(int V, vector<vector<int>>& adj) {
    vector<int> state(V, 0); // 0=unvisited, 1=visiting, 2=visited

    for (int i = 0; i < V; i++) {
        if (state[i] == 0) {
            if (dfs(i, adj, state))
                return true;
        }
    }
    return false;
}

int main() {
    int V = 4;
    vector<vector<int>> adj(V);

    // Example:
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0); // cycle: 0 → 1 → 2 → 0
    adj[2].push_back(3);

    if (hasCycle(V, adj))
        cout << "Cycle detected\n";
    else
        cout << "No cycle\n";

    return 0;
}

