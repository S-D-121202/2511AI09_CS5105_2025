#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int total_ways_calc(vvi Grid) {
    int R = Grid.size();
    int C = Grid[0].size();
    if (Grid[0][0] == -1 or Grid[R - 1][C - 1] == -1) 
        return 0;
    else {
        vvi tot_ways(R, vi(C, 0));
        tot_ways[0][0] = 1;
        for (int i = 1; i < R; i ++) {
            if (Grid[i][0] == -1) {
                tot_ways[i][0] = 0;
            }
            else {
                tot_ways[i][0] = tot_ways[i - 1][0];
            }
        }
        for (int j = 1; j < C; j ++) {
            if (Grid[0][j] == -1) tot_ways[0][j] = 0;
            else tot_ways[0][j] = tot_ways[0][j - 1];
        }
        for (int i = 1; i < R; i ++) {
            for (int j = 1; j < C; j ++) {
                if (Grid[i][j] == -1) tot_ways[i][j] = 0;
                else tot_ways[i][j] = tot_ways[i - 1][j] + tot_ways[i][j - 1];
            }
        }
        return tot_ways[R - 1][C - 1] ;
    }
}

int main() {
    vvi G(3, vi(3, 0));
    G[1][0 ] = -1;
    //cout << total_ways_calc(G);
}