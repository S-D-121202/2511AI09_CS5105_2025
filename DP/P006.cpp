#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int max_tot_points(vvi points) {
    int l = points.size();
    vvi max_points(l, vi(3, 0));
    for (int j = 0; j < 3; j ++) max_points[0][j] = points[0][j];
    for (int i = 1; i < l; i ++) {
        for(int j = 0; j < 3; j ++) {
            max_points[i][j] = -1;
            for (int k = 0; k < 3; k ++) 
                if (k != j) 
                    max_points[i][j] = max(max_points[i][j], max_points[i - 1][k] + points[i][k]);
        }
    }
    int tot_max = -1;
    for (int j = 0; j < 3; j ++) 
        tot_max = max(tot_max, max_points[l - 1][j]);
    return tot_max;
}

int main() {
    vvi points = {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90}
    };
    cout << max_tot_points(points);
}