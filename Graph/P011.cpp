#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class DSU {
public:
    unordered_map<int, int> parent;

    int find(int x) {
        if (!parent.count(x))
            parent[x] = x;
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Path compression
        return parent[x];
    }

    void unionSets(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py)
            parent[px] = py;
    }
};

int removeStones(vector<vector<int>>& stones) {
    DSU dsu;
    const int OFFSET = 10001;  // To differentiate rows and columns

    for (auto& stone : stones) {
        int row = stone[0];
        int col = stone[1] + OFFSET;  // Shift columns to avoid collision with rows
        dsu.unionSets(row, col);
    }

    // Count unique roots (connected components)
    unordered_set<int> uniqueRoots;
    for (auto& stone : stones) {
        int row = stone[0];
        uniqueRoots.insert(dsu.find(row));
    }

    // Max stones removed = total stones - connected components
    return stones.size() - uniqueRoots.size();
}

int main() {
    vector<vector<int>> stones = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};
    cout << removeStones(stones) << endl;  // Output: 5
    return 0;
}
