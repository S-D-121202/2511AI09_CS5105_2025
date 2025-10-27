#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int subset_count(vi arr, int K) {
    int l = arr.size();
    vvi tot_count(l, vi(K + 1, 0));
    for (int i = 0; i < l; i ++) tot_count[i][0] += 1;
    if (arr[0] <= K) tot_count[0][arr[0]] += 1;
    for (int i = 1; i < l; i ++) {
        for (int j = 0; j <= K; j ++) {
            if (arr[i] <= j) tot_count[i][j] = tot_count[i - 1][j] + tot_count[i - 1][j - arr[i]];
            else tot_count[i][j] = tot_count[i - 1][j];
        }
    }
    return tot_count[l - 1][K];
} 

int main() {
    vi arr = {1, 2, 2, 3};
    int K = 3;
    cout << subset_count(arr, K);
}