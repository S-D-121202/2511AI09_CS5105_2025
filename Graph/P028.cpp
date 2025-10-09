#include <bits/stdc++.h>
using namespace std;

vector<int> shortestPathUnitGraph(int V, vector<vector<int>>& adj) {
    vector<int> distance(V, -1);
    queue<int> q;

    int source = 0;
    distance[source] = 0;
    q.push(source);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (distance[v] == -1) { // not visited
                distance[v] = distance[u] + 1;
                q.push(v);
            }
        }
    }

    return distance;
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    // Example undirected graph
    adj[0] = {1, 2};
    adj[1] = {0, 3};
    adj[2] = {0, 3, 4};
    adj[3] = {1, 2, 5};
    adj[4] = {2};
    adj[5] = {3};

    vector<int> dist = shortestPathUnitGraph(V, adj);

    cout << "Shortest distances from node 0: ";
    for (int d : dist) cout << d << " ";
    cout << "\n";

    return 0;
}
