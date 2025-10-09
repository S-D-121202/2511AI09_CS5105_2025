#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& visitOrder, stack<int>& topoStack) {
    visited[node] = 1;
    visitOrder.push_back(node);  // record when node is first discovered

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, adj, visited, visitOrder, topoStack);
        }
    }

    // when all neighbors processed → push onto stack (finish order)
    topoStack.push(node);
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    // Example DAG:
    // 5 → 0 ← 4
    // ↓
    // 2 → 3 → 1
    adj[5].push_back(0);
    adj[5].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(1);
    adj[4].push_back(0);
    adj[4].push_back(1);

    vector<int> visited(V, 0);
    vector<int> visitOrder;
    stack<int> topoStack;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, adj, visited, visitOrder, topoStack);
    }

    cout << "DFS Visit Order (discovery): ";
    for (int v : visitOrder)
        cout << v << " ";
    cout << "\n";

    cout << "Topological Order (reverse of finish order): ";
    while (!topoStack.empty()) {
        cout << topoStack.top() << " ";
        topoStack.pop();
    }
    cout << "\n";

    return 0;
}
