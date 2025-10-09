#include <bits/stdc++.h>
using namespace std;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    vector<vector<pair<int,int>>> adj(n);
    for (auto &f : flights) {
        int u = f[0], v = f[1], w = f[2];
        adj[u].push_back({v, w});
    }

    // Min-heap: (cost, city, stops)
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    pq.push({0, src, 0});

    vector<int> bestCost(n, INT_MAX); // best cost to reach a city with <= stops
    vector<int> bestStops(n, INT_MAX); // stops to reach city with best cost

    while (!pq.empty()) {
        auto [cost, u, stops] = pq.top(); pq.pop();

        if (u == dst) return cost; // reached destination

        if (stops > K) continue; // exceeded allowed stops

        for (auto &[v, w] : adj[u]) {
            int newCost = cost + w;
            // Push to queue if we haven't reached v cheaper OR with fewer stops
            if (newCost < bestCost[v] || stops < bestStops[v]) {
                bestCost[v] = newCost;
                bestStops[v] = stops;
                pq.push({newCost, v, stops + 1});
            }
        }
    }

    return -1; // no valid path
}

int main() {
    int n = 4;
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,3,100},{0,2,500}};
    int src = 0, dst = 3, K = 2;

    int ans = findCheapestPrice(n, flights, src, dst, K);
    cout << "Cheapest price: " << ans << "\n"; // Output: 300
}
