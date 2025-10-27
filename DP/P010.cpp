#include <bits/stdc++.h>
using namespace std;

int minimumPathSum(vector<vector<int>> &triangle) {
    int n = triangle.size();
    vector<vector<int>> dp = triangle; // Copy triangle to initialize dp

    // Start from second last row and move upwards
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            int down = triangle[i][j] + dp[i + 1][j];
            int diag = triangle[i][j] + dp[i + 1][j + 1];
            dp[i][j] = min(down, diag);
        }
    }

    // Top cell now contains the minimum total path sum
    return dp[0][0];
}

int main() {
    vector<vector<int>> triangle = {
        {1},
        {2, 3},
        {3, 6, 7},
        {8, 9, 6, 10}
    };

    cout << minimumPathSum(triangle) << endl; // Output: 16
    return 0;
}
