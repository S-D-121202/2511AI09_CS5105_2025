#include <bits/stdc++.h>
using namespace std;

struct Cell {
    int x, y, dist;
};

bool isValid(int x, int y, int n, int m, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    return (x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 1 && !visited[x][y]);
}

int shortestPath(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dest) {
    int n = grid.size();
    int m = grid[0].size();

    // If source or destination is blocked
    if (grid[src.first][src.second] == 0 || grid[dest.first][dest.second] == 0)
        return -1;

    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // Movement directions: up, down, left, right
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    queue<Cell> q;
    q.push({src.first, src.second, 0});
    visited[src.first][src.second] = true;

    while (!q.empty()) {
        Cell cur = q.front();
        q.pop();

        // Destination reached
        if (cur.x == dest.first && cur.y == dest.second)
            return cur.dist;

        // Explore all 4 directions
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];

            if (isValid(nx, ny, n, m, grid, visited)) {
                visited[nx][ny] = true;
                q.push({nx, ny, cur.dist + 1});
            }
        }
    }

    // No path found
    return -1;
}

int main() {
    vector<vector<int>> grid = {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {0, 1, 0, 1},
        {1, 1, 1, 1}
    };

    pair<int,int> src = {0, 0};
    pair<int,int> dest = {3, 3};

    int result = shortestPath(grid, src, dest);

    if (result != -1)
        cout << "Shortest path length = " << result << endl;
    else
        cout << "No path exists" << endl;

    return 0;
}
