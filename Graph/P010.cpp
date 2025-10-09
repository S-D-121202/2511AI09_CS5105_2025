#include <iostream>
#include <vector>

using namespace std;

class DSU {
public:
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    bool unionSets(int x, int y) {
        int px = find(x);
        int py = find(y);

        if (px == py)
            return false; // Redundant edge

        // Union by rank
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

int makeConnected(int n, vector<vector<int>>& edges) {
    if (edges.size() < n - 1)
        return -1; // Not enough edges to connect all nodes

    DSU dsu(n);
    int extraEdges = 0;

    for (auto& edge : edges) {
        if (!dsu.unionSets(edge[0], edge[1])) {
            extraEdges++; // Redundant edge
        }
    }

    // Count connected components
    int components = 0;
    for (int i = 0; i < n; ++i) {
        if (dsu.find(i) == i)
            components++;
    }

    int operationsNeeded = components - 1;
    return (extraEdges >= operationsNeeded) ? operationsNeeded : -1;
}

int main() {
    // Example usage
    int n = 4;
    vector<vector<int>> edges = {{0,1},{0,2},{1,2}};
    
    cout << makeConnected(n, edges) << endl; // Output: 1

    return 0;
}


