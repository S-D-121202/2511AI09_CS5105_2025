#include<iostream>
#include<bits\stdc++.h>
#define inf = INT32_MAX;

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int tot_min_cost(vvi Grid) {
    int R = Grid.size();
    int C = Grid[0].size();
    vvi min_cost(R, vi(C, 0));
    if (Grid[0][0] == -1 or Grid[R - 1][C - 1] == -1)
        return -1;
    else {
        min_cost[0][0] = Grid[0][0];
        for (int i = 1; i < R; i ++) {
            if (Grid[i][0] == -1) min_cost[i][0] = INT32_MAX;
            else if(min_cost[i - 1][0] == INT32_MAX) min_cost[i][0] = INT32_MAX;
            else min_cost[i][0] = min_cost[i - 1][0] + Grid[i][0];
        }
        for (int j = 1; j < C; j ++) {
            if (Grid[0][j] == -1) min_cost[0][j] = INT32_MAX;
            else if(min_cost[0][j - 1] == INT32_MAX) min_cost[0][j] = INT32_MAX;
            else min_cost[0][j] = min_cost[0][j - 1] + Grid[0][j];
        }
        for (int i = 1; i < R; i ++) {
            for (int j = 1; j < C; j ++) {
                if (Grid[i][j] == -1) min_cost[i][j] = INT32_MAX;
                else {
                    int t = (min_cost[i - 1][j] == INT32_MAX) ? INT32_MAX : min_cost[i - 1][j] + Grid[i][j];
                    int l = (min_cost[i][j - 1] == INT32_MAX) ? INT32_MAX : min_cost[i][j - 1] + Grid[i][j];
                    min_cost[i][j] = min(t, l);
                }
            }
        }
        int ret = (min_cost[R - 1][C - 1] == INT32_MAX) ? -1 : min_cost[R - 1][C - 1];
        return ret;
    }
}

int main() {
    vvi G = {
        {1, 2, 3},
        {-1, 4, -1},
        {1, -1, 3}
    };
    cout << tot_min_cost(G);
}