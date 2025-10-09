#include<iostream>
#include<bits/stdc++.h>

using namespace std;

using p = pair<int, int>;
using vi = vector<int>;
using vp = vector<p>;
using miv = map<int, vi>;
using mii = map<int, int>;
using S = stack<int>;

miv adj_list_gen(vp edges, int num_node) {
    miv adj_list;
    for (int i = 0; i < num_node; i ++) {
        vi lst;
        adj_list.insert({i + 1, lst});
    }
    for (p e : edges) {
        adj_list[e.first].push_back(e.second);
        adj_list[e.second].push_back(e.first);
    } 
    return adj_list;
}

bool dfs(int x, S stack, miv adj_list, int num_node, mii &col) {
    stack.push(x);
    int colour = 1;
    bool flag = true;
    while (not stack.empty() and flag) {
        int tp = stack.top();
        stack.pop();
        if (col[tp] == 0) {
            col[tp] = colour;
            for (int i : adj_list[tp]) {
                if (col[i] == 0) {
                    stack.push(i);
                }
                else if (col[i] == col[tp]) {
                    flag = false;
                    break;
                }
            }
            colour = 3 - colour;
        }
    }
    return flag;
}

bool colouring(miv adj_lst, int num_node) {
    mii coloured;
    for (int i = 0; i < num_node; i ++) {
        coloured.insert({i + 1, 0});
    }
    S stack;
    bool res = true;
    for (int i = 0; i < num_node; i ++) {
        if (coloured[i + 1] == 0) {
            res = res and dfs(i + 1, stack, adj_lst, num_node, coloured);
            if (not res) break;
        }
    }
    return res;
}

int main() {
    int num_node;
    cout << " Number of nodes in graph : ";
    cin >> num_node;
    vp Edges;
    int max_edges = (num_node*(num_node - 1)) / 2;
    for (int i = 0 ; i < max_edges; i ++) {
        int x, y;
        cout << i + 1 << " Edge : " << endl;
        cout << " enter 1st node val : ";
        cin >> x;
        if (x == -1) break;
        else {
            cout << " enter 2nd node val : ";
            cin >> y;
            p e = {x, y};
            Edges.push_back(e);
        }
    }
    miv adj_lst = adj_list_gen(Edges, num_node);
    bool res = colouring(adj_lst, num_node);
    if (res)
        cout << " graph is bipartite. ";
    else
        cout << " Not bipartite. ";
}