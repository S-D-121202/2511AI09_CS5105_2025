#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<pair<int,int>> q;

        // Push all boundary land cells into the queue
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if((i == 0 || j == 0 || i == n-1 || j == m-1) && grid[i][j] == 1) {
                    q.push({i,j});
                    vis[i][j] = 1;
                }
            }
        }

        // Directions: up, down, left, right
        int drow[] = {-1, 1, 0, 0};
        int dcol[] = {0, 0, -1, 1};

        // BFS traversal to mark reachable land
        while(!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for(int k = 0; k < 4; k++) {
                int nr = r + drow[k];
                int nc = c + dcol[k];
                if(nr >= 0 && nr < n && nc >= 0 && nc < m 
                   && !vis[nr][nc] && grid[nr][nc] == 1) {
                    vis[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }

        // Count unvisited land cells (enclaves)
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] == 1 && !vis[i][j]) {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};

int main() {
    vector<vector<int>> grid = {
        {0,0,0,0},
        {1,0,1,0},
        {0,1,1,0},
        {0,0,0,0}
    };
    
    Solution sol;
    cout << sol.numEnclaves(grid) << endl; // Output: 3
    return 0;
}
