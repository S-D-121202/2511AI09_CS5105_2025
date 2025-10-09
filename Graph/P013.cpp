#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int rows = image.size();
        int cols = image[0].size();
        int originalColor = image[sr][sc];

        if (originalColor == newColor) return image;

        queue<pair<int,int>> q;
        q.push({sr, sc});
        image[sr][sc] = newColor;

        int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for (auto& d : directions) {
                int nr = r + d[0];
                int nc = c + d[1];

                if (nr >= 0 && nc >= 0 && nr < rows && nc < cols && image[nr][nc] == originalColor) {
                    image[nr][nc] = newColor;
                    q.push({nr, nc});
                }
            }
        }
        return image;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> image = {{1,1,1}, {1,1,0}, {1,0,1}};
    int sr = 1, sc = 1, newColor = 2;

    vector<vector<int>> result = sol.floodFill(image, sr, sc, newColor);

    for (auto& row : result) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    return 0;
}

