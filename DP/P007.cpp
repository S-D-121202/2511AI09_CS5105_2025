#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int total_ways(int N, int M) {
    vvi grid;
    for (int i = 0; i < N; i ++) {
        vi row;
        for (int j = 0; j < M; j ++)
            row.push_back(0);
        grid.push_back(row);
    }
    grid[0][0] = 1;
    for (int j = 1; j < M; j ++)
        grid[0][j] = grid[0][j - 1];
    for (int i = 1; i < N; i ++)
        grid[i][0] = grid[i - 1][0];
    for (int i = 1; i < N; i ++)
        for (int j = 1; j < M; j ++) 
            grid[i][j] = grid[i - 1][j] + grid[i][j - 1];
    return grid[N - 1][M - 1];
}

int main() {
    int M = 3;
    int N = 2;
    cout << total_ways(M, N);
}