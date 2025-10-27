#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;

int tot_max_sum(vi arr) {
    int l = arr.size();
    vi max_sum;
    for (int i = 0; i < l; i ++) {
        max_sum.push_back(0);
    }
    max_sum[0] = arr[0];
    max_sum[1] = max(max_sum[0], arr[1]);
    for (int i = 2; i < l; i ++) {
        max_sum[i] = max(max_sum[i - 1], arr[i] + max_sum[i - 2]);
    }
    return max_sum[l - 1];
}

int main () {
    vi arr = {1, 2, 4};
    int TMS = tot_max_sum(arr);
    cout << TMS;
}