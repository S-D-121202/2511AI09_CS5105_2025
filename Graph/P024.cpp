#include <bits/stdc++.h>
using namespace std;

// Returns true if a cycle is detected
bool dfs(int node, vector<vector<int>>& adj, vector<int>& state, vector<int>& topo) {
    state[node] = 1; // visiting
    for (int neighbor : adj[node]) {
        if (state[neighbor] == 0) {
            if (dfs(neighbor, adj, state, topo))
                return true; // cycle detected
        }
        else if (state[neighbor] == 1) {
            return true; // cycle detected
        }
    }
    state[node] = 2; // visited
    topo.push_back(node); // record finish order
    return false;
}

// Problem I: Return order of tasks
vector<int> findTaskOrder(int n, vector<pair<int,int>>& prerequisites) {
    vector<vector<int>> adj(n);
    for (auto& p : prerequisites) adj[p.second].push_back(p.first);

    vector<int> state(n, 0), topo;
    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            if (dfs(i, adj, state, topo)) return {}; // cycle detected
        }
    }
    reverse(topo.begin(), topo.end());
    return topo;
}

// Problem II: Check if possible
bool canFinishTasks(int n, vector<pair<int,int>>& prerequisites) {
    vector<vector<int>> adj(n);
    for (auto& p : prerequisites) adj[p.second].push_back(p.first);

    vector<int> state(n, 0);
    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            vector<int> dummy;
            if (dfs(i, adj, state, dummy)) return false; // cycle detected
        }
    }
    return true;
}

int main() {
    int n = 4;
    vector<pair<int,int>> prerequisites = {{1,0},{2,0},{3,1},{3,2}};

    // Problem I
    vector<int> order = findTaskOrder(n, prerequisites);
    if(order.empty()) cout << "Impossible to finish all tasks\n";
    else {
        cout << "Task order: ";
        for(int x: order) cout << x << " ";
        cout << "\n";
    }

    // Problem II
    bool possible = canFinishTasks(n, prerequisites);
    cout << "Possible to finish all tasks? " << (possible ? "Yes" : "No") << "\n";

    return 0;
}
