#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;

int min_energy(vi energy) {
    vi energy_req;
    for (int i = 0; i < energy.size(); i ++) 
        energy_req.push_back(0);
    int last = energy.size() - 1;
    for (int i = last - 1; i > -1; i --) {
        if (i == last - 1)
            energy_req[i] = abs(energy[i] - energy[i + 1]);
        else 
            energy_req[i] = min(abs(energy[i] - energy[i + 1]) + energy_req[i + 1], abs(energy[i] - energy[i + 2]) + energy_req[i + 2]);
    }
    return energy_req[0];
}

int main() {
    vi en = {10, 20, 30, 10};
    int min_e = min_energy(en);
    cout << min_e;
}