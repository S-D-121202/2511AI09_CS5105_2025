#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vb = vector<bool>;
using vvb = vector<vb>;

int subset_sum_check(vi arr, int K) {
    int l = arr.size();
    vvb flag(l, vb(K + 1, false));
    for (int i = 0; i < l; i ++)
        flag[i][0] = true;
    if (arr[0] <= K) flag[0][arr[0]] = true;
    for (int i = 1; i < l; i ++) {
        for (int j = 1; j <= K; j ++) {
            if (arr[i] == j) flag[i][j] = true;
            else {
                bool not_pick = flag[i - 1][j];
                bool pick = flag[i - 1][K - j];
                flag[i][j] = pick or not_pick;
            }
        }
    }
    int mark_sum = K;
    for (int j = K; j > -1; j --) {
        if (flag[l - 1][j]) {
            mark_sum = j;
            break;
        }
    }
    return K - 2*mark_sum;
}

int main() {
    vi arr = {1, 2, 3, 4};
    int sum = 0;
    for (int i = 0; i < arr.size(); i ++)
        sum += arr[i];
    // from here just like subset target sum checking problem...
    cout << subset_sum_check(arr, sum);
}