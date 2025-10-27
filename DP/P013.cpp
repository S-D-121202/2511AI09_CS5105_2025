#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvb = vector<vector<bool>>;

bool subset_sum_check(vi arr, int K) {
    int l = arr.size();
    vvb flag(l, vector<bool>(K + 1, false));
    for (int i = 0; i < l; i ++)
        flag[i][0] = true;
    if (arr[0] <= K) flag[0][arr[0]] = true;
    for (int i = 1; i < l; i ++) {
        for (int j = 1; j <= K; j ++) {
            if (arr[i] <= j) {
                bool not_pick = flag[i - 1][j];
                bool pick = flag[i - 1][K - j];
                flag[i][j] = pick or not_pick;
            }
            else flag[i][j] = flag[i - 1][j];
        }
    }
    return flag[l - 1][K];
}

int main() {
    vi arr = {1, 2, 3, 4};
    cout << subset_sum_check(arr, 4);
}