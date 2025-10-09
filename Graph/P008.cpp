#include<iostream>
#include<bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

struct compare {
    bool operator()(vi &p1, vi &p2) {
        return p1[2] > p2[2];
    }
};

using pq = priority_queue<vi, vvi, compare>;

vvi adj_finder(int x, int y, int r, int c) {
    vvi ret;
    vi dx = {-1, 1, 0, 0};
    vi dy = {0, 0, -1, 1};
    for (int i = 0; i < 4 ; i ++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 and nx < r and ny >= 0 and ny < c) {
            vi t = {nx, ny};
            ret.push_back(t);
        }
    }
    return ret;
}

vvi min_matrix_calc(int **M, int rows, int cols) {
    vvi min_matrix;
    pq prior_q;
    for (int i = 0; i < rows; i ++) {
        vi row;
        for (int j = 0; j < cols; j ++) {
            row.push_back(int(1e9));
        }
        min_matrix.push_back(row);
    }
    min_matrix[0][0] = 0;
    vi start = {0, 0, 0};
    prior_q.push(start);
    while (not prior_q.empty()) {
        vi tp = prior_q.top();
        prior_q.pop();
        vvi neighbours = adj_finder(tp[0], tp[1], rows, cols);
        for (vi index : neighbours) {
            if (min_matrix[index[0]][index[1]] > min_matrix[tp[0]][tp[1]] + abs(M[index[0]][index[1]] - M[tp[0]][tp[1]])) {
                min_matrix[index[0]][index[1]] = min_matrix[tp[0]][tp[1]] + abs(M[index[0]][index[1]] - M[tp[0]][tp[1]]);
                vi n = {index[0], index[1], min_matrix[index[0]][index[1]]};
                prior_q.push(n);
            }
        }
    }
    return min_matrix;
}

int main() {
    int rows, cols;
    cout << " Number of row : ";
    cin >> rows;
    cout << " Number of columnm : ";
    cin >> cols;
    int **Matrix = new int*[rows];
    for (int i = 0; i < rows; i ++)
        Matrix[i] = new int[cols];
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j ++) {
            cout << " Enter value of cell " << "[" << i << "," << j << "] : ";
            cin >> Matrix[i][j];
        }
    }
    vvi min_matrix = min_matrix_calc(Matrix, rows, cols);
    for (int i = 0; i < rows; i ++) {
        cout << endl;
        for (int j = 0; j < cols; j ++) {
            cout << min_matrix[i][j];
        }
    }
}