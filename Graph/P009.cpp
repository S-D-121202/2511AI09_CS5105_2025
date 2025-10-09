#include<iostream>
#include<bits/stdc++.h>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using mivv = map<int, vvi>;
using mii = map<int, int>;

struct comparator {
    bool operator()(vi &t1, vi &t2) {
        return t1[1] > t2[1]; 
    }
};

using pq = priority_queue<vi, vvi, comparator>;

mivv adj_lst_gen(vvi roads, int node_count) {
    mivv adj_lst;
    for (int i = 0; i < node_count; i ++) {
        vvi lst;
        adj_lst.insert({i + 1, lst});
    }
    for (vi road : roads) {
        vi t1, t2;
        t1 = {road[1], road[2]};
        adj_lst[road[0]].push_back(t1);
        t2 = {road[0], road[2]};
        adj_lst[road[1]].push_back(t2);
    }
    return adj_lst;
}

mii ways_counting(int src, vvi roads, int node_count) {
    mivv adj_lst = adj_lst_gen(roads, node_count);
    mii min_dist, ways;
    for (int i = 0; i < node_count; i ++) {
        min_dist.insert({i + 1, int(1e9)});
        ways.insert({i + 1, 0});
    }
    min_dist[src] = 0;
    ways[src] = 1;
    pq queue;
    vi start = {src, 0};
    queue.push(start);
    while (not queue.empty()) {
        vi tp = queue.top();
        queue.pop();
        int n = tp[0];
        for (vi adj : adj_lst[n]) {
            if (min_dist[adj[0]] > min_dist[n] + adj[2]) {
                min_dist[adj[0]] = min_dist[n] + adj[2];
                ways[adj[0]] = ways[n];
                queue.push({adj[0], min_dist[adj[0]]});
            }
            else if (min_dist[adj[0]] == min_dist[n] + adj[2]) {
                ways[adj[0]] += ways[n];
            }
            else continue;
        }
    }
    return ways;
}

int main() {
    vvi roads;
    int node_count;
    cout << " Number of junctions : ";
    cin >> node_count;
    int road_count_max = (node_count*(node_count - 1)) / 2;
    for (int i = 0; i < road_count_max; i ++) {
        int si, di, time;
        cout << endl << " Road " << i + 1 << " : " << endl;
        cout << " 1st junction : ";
        cin >> si;
        if (si == -1) break;
        else {
            cout << " 2nd junction : ";
            cin >> di;
            cout << " Time requere : ";
            cin >> time;
            vi road = {si, di, time};
            roads.push_back(road);
        }
    }
    int src, dst;
    cout << " Source junction : ";
    cin >> src;
    cout << " Destination junction : ";
    cin >> dst;
    mii ways = ways_counting(src, roads, node_count);
    for (const auto & pair : ways) {
        cout << pair.first << " : " << pair.second << endl;
    }
}
