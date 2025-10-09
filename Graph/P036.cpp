#include <bits/stdc++.h>
using namespace std;

int primMST(int V, vector<vector<pair<int,int>>>& adj) {
    vector<int> key(V, INT_MAX); // minimum weight to include node in MST
    vector<bool> inMST(V, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int src = 0;
    key[src] = 0;
    pq.push({0, src});

    int mstWeight = 0;

    while (!pq.empty()) {
        auto [wt, u] = pq.top(); pq.pop();

        if (inMST[u]) continue; // skip if already included
        inMST[u] = true;
        mstWeight += wt;

        for (auto &[v, w] : adj[u]) {
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({w, v});
            }
        }
    }

    return mstWeight;
}

int main() {
    int V = 5;
    vector<vector<pair<int,int>>> adj(V);

    auto addEdge = [&](int u, int v, int w){
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    };

    addEdge(0, 1, 2);
    addEdge(0, 3, 6);
    addEdge(1, 2, 3);
    addEdge(1, 3, 8);
    addEdge(1, 4, 5);
    addEdge(2, 4, 7);
    addEdge(3, 4, 9);

    int mstWeight = primMST(V, adj);
    cout << "Sum of MST weights: " << mstWeight << "\n"; // Output: 16
}
