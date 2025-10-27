#include <bits/stdc++.h>
using namespace std;

int getMaxPathSum(vector<vector<int>> &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Base case: first row
    for (int j = 0; j < m; j++)
        dp[0][j] = matrix[0][j];

    // Build dp table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int up = matrix[i][j] + dp[i - 1][j];

            int leftDiag = matrix[i][j];
            if (j > 0) leftDiag += dp[i - 1][j - 1];
            else leftDiag += -1e9; // invalid

            int rightDiag = matrix[i][j];
            if (j < m - 1) rightDiag += dp[i - 1][j + 1];
            else rightDiag += -1e9; // invalid

            dp[i][j] = max({up, leftDiag, rightDiag});
        }
    }

    // Find the max value in the last row
    int maxi = INT_MIN;
    for (int j = 0; j < m; j++)
        maxi = max(maxi, dp[n - 1][j]);

    return maxi;
}

int main() {
    vector<vector<int>> matrix = {
        {1, 2, 10, 4},
        {100, 3, 2, 1},
        {1, 1, 20, 2},
        {1, 2, 2, 1}
    };

    cout << getMaxPathSum(matrix) << endl;
    return 0;
}
