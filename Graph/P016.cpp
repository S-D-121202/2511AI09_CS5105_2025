#include <iostream>
#include <vector>
using namespace std;

void dfs(int row, int col, vector<vector<char>>& mat, vector<vector<bool>>& visited) {
    int n = mat.size();
    int m = mat[0].size();
    visited[row][col] = true;

    int dx[] = {-1, 1, 0, 0}; // directions: up, down, left, right
    int dy[] = {0, 0, -1, 1};

    for (int dir = 0; dir < 4; ++dir) {
        int newRow = row + dx[dir];
        int newCol = col + dy[dir];

        if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m &&
            mat[newRow][newCol] == 'O' && !visited[newRow][newCol]) {
            dfs(newRow, newCol, mat, visited);
        }
    }
}

void replaceSurroundedRegions(vector<vector<char>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    // Step 1: Mark all 'O's connected to boundary
    for (int i = 0; i < n; ++i) {
        if (mat[i][0] == 'O' && !visited[i][0])
            dfs(i, 0, mat, visited);
        if (mat[i][m - 1] == 'O' && !visited[i][m - 1])
            dfs(i, m - 1, mat, visited);
    }

    for (int j = 0; j < m; ++j) {
        if (mat[0][j] == 'O' && !visited[0][j])
            dfs(0, j, mat, visited);
        if (mat[n - 1][j] == 'O' && !visited[n - 1][j])
            dfs(n - 1, j, mat, visited);
    }

    // Step 2: Replace all unvisited 'O's with 'X'
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (mat[i][j] == 'O' && !visited[i][j])
                mat[i][j] = 'X';
}

int main() {
    int N, M;
    cout << "Enter number of rows and columns: ";
    cin >> N >> M;

    vector<vector<char>> mat(N, vector<char>(M));
    cout << "Enter matrix elements (O/X):" << endl;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            cin >> mat[i][j];

    replaceSurroundedRegions(mat);

    cout << "Modified Matrix:" << endl;
    for (const auto& row : mat) {
        for (char ch : row)
            cout << ch << " ";
        cout << endl;
    }

    return 0;
}
