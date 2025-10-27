#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vb = vector<bool>;
using vvb = vector<vb>;

int match_decide(string s1, string s2) {
    int l1 = s1.size();
    int l2 = s2.size();
    vvb flag(l1 + 1, vb(l2 + 1, false));
    flag[0][0] = true;
    for (int j = 1; j <= l2; j ++) 
        flag[0][j] = false;
    for (int i = 1; i <= l1; i ++) {
        if (s1[i - 1] == '*')
            flag[i][0] = true;
        else flag[i][0] = false;
    }
    for (int i = 1; i <= l1; i ++) {
        for (int j = 1; j <= l2; j ++) {
            if (s1[i - 1] == s2[j - 1] or s1[i - 1] == '?') 
                flag[i][j] = flag[i - 1][j - 1];
            else if (s1[i - 1] == '*') 
                flag[i][j] = flag[i - 1][j] or flag[i][j - 1];
            else flag[i][j] = false;
        }
    }
    return flag[l1][l2];
}

int main() {
    string s1 = "ab?e";
    string s2 = "abcde";
    cout << match_decide(s1, s2);
}
