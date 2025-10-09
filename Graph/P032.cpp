#include <bits/stdc++.h>
using namespace std;

int minimumMultiplications(vector<int>& arr, int start, int end) {
    const int MOD = 100000;
    vector<int> distance(MOD, -1);
    queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        if (curr == end) return distance[curr]; // reached end

        for (int x : arr) {
            int next = (1LL * curr * x) % MOD; // use long long to prevent overflow
            if (distance[next] == -1) {
                distance[next] = distance[curr] + 1;
                q.push(next);
            }
        }
    }

    return -1; // unreachable
}

int main() {
    vector<int> arr = {2, 5, 7};
    int start = 3, end = 30;

    int steps = minimumMultiplications(arr, start, end);
    cout << "Minimum steps: " << steps << "\n"; // Output: 2 (3*5=15, 15*2=30)
}
