#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;

int min_energy(vi energy, int K) {
    vi energy_req;
    int l = energy.size();
    for (int i = 0; i < l; i ++)
        energy_req.push_back(0);
    for (int i = l - 1; i > -1; i --) {
        if (i == l - 1) energy_req[i] = 0;
        else {
            int m = INT32_MAX;
            if (l - 1 - i > K) {
                for (int j = i + 1; j <= (i + K); j ++) {
                    int e = abs(energy[i] - energy[j]) + energy_req[j];
                    if (e < m) m = e;
                }
            }
            else {
                for (int j = i + 1; j < l; j ++) {
                    int e = abs(energy[i] - energy[j]) + energy_req[j];
                    if (e < m) m = e;
                }
            }
            energy_req[i] = m;
        }
    }
    return energy_req[0];
}

int main() {
    vi en = {10, 20, 30, 10};
    int K = 4;
    int min_e = min_energy(en, 4);
    cout << min_e;
}