#include <bits/stdc++.h>
using namespace std;

void dfs(int x, int y, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    int n = grid.size();
    int m = grid[0].size();
    visited[x][y] = true;

    // 8 directions
    int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[] = {0, 0, -1, 1, -1, 1, -1, 1};

    for (int dir = 0; dir < 8; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m 
            && grid[nx][ny] == 1 && !visited[nx][ny]) {
            dfs(nx, ny, grid, visited);
        }
    }
}

int numIslands(vector<vector<int>>& grid) {
    int n = grid.size();
    if (n == 0) return 0;
    int m = grid[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                dfs(i, j, grid, visited);
                count++;
            }
        }
    }

    return count;
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };

    cout << "Number of islands: " << numIslands(grid) << endl; // Output: 5
    return 0;
}
