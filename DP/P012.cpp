#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

vi adj_cols(int j, int C) {
    vi neis;
    vi dj = {-1, 0, 1};
    for (int d : dj) {
        if (d + j >= 0 and d + j < C)
            neis.push_back(d + j);
    }
    return neis;
}

int tot_max_sweets(vvi M, int in_aj, int in_bj) {
    int R = M.size();
    int C = M[0].size();
    vvvi max_sweets(R, vvi(C, vi(C, 0)));
    for (int ja = 0; ja < C; ja ++) {
        for (int jb = 0; jb < C; jb ++) {
            max_sweets[R - 1][ja][jb] = M[R - 1][ja];
            if (ja != jb) max_sweets[R - 1][ja][jb] += M[R - 1][jb];
        }
    }
    for (int i = R - 2; i > - 1; i --) {
        for (int ja = 0; ja < C; ja ++) {
            vi nja = adj_cols(ja, C);
            for (int jb = 0; jb < C; jb ++) {
                int s = M[i][ja] + (ja == jb ? 0 : M[i][jb]);
                int max_s = -1;
                vi njb = adj_cols(jb, C);
                for (int _ja : nja) {
                    for (int _jb : njb)
                        max_s = max(max_s, max_sweets[i + 1][_ja][_jb]);
                }
                max_sweets[i][ja][jb] = s + max_s;
            }
        }
    }
    return max_sweets[0][in_aj][in_bj];
}

int main() {
    vvi Mat1 = {
        {2, 3, 1, 4, 2},
        {3, 4, 2, 2, 3},
        {5, 6, 3, 5, 1},
        {1, 2, 4, 1, 200},
        {3, 2, 5, 2, 1}
    };
    int A = 0;
    int B = 4;
    cout << tot_max_sweets(Mat1, A, B);
}