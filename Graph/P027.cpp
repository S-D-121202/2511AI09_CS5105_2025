#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<int>& visited, string& order) {
    visited[node] = 1;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) dfs(neighbor, adj, visited, order);
    }
    order += (char)(node + 'a'); // append after all neighbors processed
}

string alienOrder(vector<string>& words, int k) {
    vector<vector<int>> adj(k);
    int N = words.size();

    // Build graph edges
    for (int i = 0; i < N - 1; i++) {
        string w1 = words[i], w2 = words[i + 1];
        int len = min(w1.size(), w2.size());
        for (int j = 0; j < len; j++) {
            if (w1[j] != w2[j]) {
                adj[w1[j] - 'a'].push_back(w2[j] - 'a');
                break; // only the first mismatch matters
            }
        }
    }

    // DFS Topological Sort
    vector<int> visited(k, 0);
    string order;
    for (int i = 0; i < k; i++) {
        if (!visited[i]) dfs(i, adj, visited, order);
    }

    reverse(order.begin(), order.end());
    return order;
}

int main() {
    vector<string> words = {"baa","abcd","abca","cab","cad"};
    int k = 4; // a,b,c,d

    string result = alienOrder(words, k);
    cout << "Alien dictionary order: " << result << "\n";

    return 0;
}
