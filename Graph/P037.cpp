#include <bits/stdc++.h>
using namespace std;

// Union-Find (Disjoint Set)
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i=0; i<n; i++) parent[i]=i;
    }

    int find(int x) {
        if(parent[x]!=x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if(px == py) return false;

        if(rank[px] < rank[py]) parent[px] = py;
        else if(rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};

int kruskalMST(int V, vector<vector<int>>& edges) {
    // edges: {u, v, weight}
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){
        return a[2] < b[2];
    });

    DSU dsu(V);
    int mstWeight = 0;
    vector<pair<int,int>> mstEdges;

    for(auto &e : edges) {
        int u = e[0], v = e[1], w = e[2];
        if(dsu.unite(u,v)) {
            mstWeight += w;
            mstEdges.push_back({u,v});
        }
    }

    // Optionally print MST edges
    // for(auto &[u,v]: mstEdges) cout << u << " - " << v << "\n";

    return mstWeight;
}

int main() {
    int V = 5;
    vector<vector<int>> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8}, {1,4,5}, {2,4,7}, {3,4,9}
    };

    int mstWeight = kruskalMST(V, edges);
    cout << "Sum of MST weights: " << mstWeight << "\n"; // Output: 16
}
