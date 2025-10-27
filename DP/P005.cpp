#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;

int max_rob(vi arr) {
    vi tot1, tot2;
    int l = arr.size();
    for (int i = 0; i < l - 1; i ++) {
        tot1.push_back(0);
        tot2.push_back(0);
    }
    tot1[0] = arr[0];
    tot2[0] = arr[1];
    tot1[1] = max(tot1[0], arr[1]);
    tot2[1] = max(tot2[0], arr[2]);
    for (int i = 2; i < l - 1; i ++) {
        tot1[i] = max(tot1[i - 1], arr[i] + tot1[i - 2]);
        tot2[i] = max(tot2[i - 1], arr[i + 1] + tot2[i - 2]);
    }
    return max(tot1[l - 2], tot2[l - 2]);
}

int main() {
    vi arr = {2, 1, 4, 9};
    int TMS = max_rob(arr);
    cout << TMS;
}