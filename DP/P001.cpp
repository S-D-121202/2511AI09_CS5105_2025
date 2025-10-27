#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;

int total_ways(int N) {
    vi ways;
    for (int i = 0; i <= N; i ++) 
        ways.push_back(0);
    ways[N] = 1;
    for (int i = N - 1; i > -1; i --) {
        if (i == N - 1) 
            ways[i] = ways[i + 1];
        else 
            ways[i] = ways[i + 1] + ways[i + 2];
    }
    return ways[0];
}

int main() {
    cout << " Number of stairs : ";
    int n;
    cin >> n;
    int ways = total_ways(n);
    cout << " Number of total ways to reach stair case " << n << " is : " << ways;
}