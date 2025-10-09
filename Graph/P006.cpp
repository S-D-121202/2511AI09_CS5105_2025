#include<iostream>
#include<bits\stdc++.h>

using namespace std;
using vi = vector<int>;
using miv = map<int, vi>;
using pii = pair<int, int>;
using vp = vector<pii>;
using mii = map<int, int>;
using vvi = vector<vi>;
using mivp = map<int, vp>;
using mib = map<int, bool>;

struct compare {
    bool operator()(pii& p1, pii& p2) {
        return p1.second > p2.second; 
    }
};

using pq = priority_queue<pii, vp, compare>;

mivp adj_lst_gen(int tot_n, vvi edges) {
    mivp adj_lst;
    for (int i = 0; i < tot_n; i ++) {
        vp lst;
        adj_lst.insert({i + 1, lst});
    }
    for (vi e : edges) {
        pii n_w = {e[1], e[2]};
        adj_lst[e[0]].push_back(n_w);
        pii n_w_rev = {e[0], e[2]};
        adj_lst[e[1]].push_back(n_w_rev);
    }
    return adj_lst;
}

mii min_dist_calc(int src, int tot_n, mivp adj_lst) {
    pq queue;
    mii min_dist;
    for (int i = 0; i < tot_n; i ++) {
        if (i + 1 != src) {
            min_dist.insert({i + 1, (int)1e9});
        }
    }
    min_dist.insert({src, 0});
    pii src_dist = {src, 0};
    for (const auto &pair : min_dist) {
        cout << endl << "( " <<pair.first << " ," << pair.second << " )"; 
    }
    queue.push(src_dist);
    while (not queue.empty()) {
        pii min_pair = queue.top();
        cout << endl << "( " << min_pair.first << " , " << min_pair.second << " )";
        queue.pop();
        for (pii near : adj_lst[min_pair.first]) {
            if (min_dist[near.first] > min_dist[min_pair.first] + near.second) {
                min_dist[near.first] = min_dist[min_pair.first] + near.second;
                pii updated_near = {near.first, min_dist[near.first]};
                queue.push(updated_near);
            }
        }
    }
    return min_dist;
}

int main() {
    int tot_n;
    cout << " Number of total nodes : ";
    cin >> tot_n;
    vvi Edges;
    int tot_edges = (tot_n*(tot_n - 1))/2;
    for (int i = 0; i < tot_edges; i ++) {
        int x, y, w;
        cout << endl << " edge " << i + 1 << endl;
        cout << " 1st node : ";
        cin >> x;
        if (x == -1) break;
        else {
            cout << " 2nd node : ";
            cin >> y;
            cout << " edge_weight : ";
            cin >> w;
            vi e = {x, y, w};
            Edges.push_back(e);
        }
    }
    mivp adj_lst = adj_lst_gen(tot_n, Edges);
    for (const auto &pair : adj_lst) {
        cout << endl << pair.first;
        for (pii t : pair.second) {
            cout << "(" << t.first << " ," << t.second << ")";
        }
    }
    mii min_dist = min_dist_calc(1, tot_n, adj_lst);
    for (const auto &pair : min_dist) {
        cout << endl << pair.first << " : " << pair.second << endl;
    }
}
