#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;

using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using miv = map<int, vi>;
using st = stack<int>;

miv adj_list_gen(vi vertex_list, vvi edge_list) {
    miv adj_list;
    for (int v : vertex_list) {
        vi neighbours;
        adj_list.insert({v, neighbours});
    }
    for (vi edge : edge_list) {
        adj_list[edge[0]].push_back(edge[1]);
        adj_list[edge[1]].push_back(edge[0]);
    }
    return adj_list;
}

void dfs(int start, miv adj_list, st &stack, vb &vis) {
    stack.push(start);
    cout << start << " : ";
    while (not stack.empty()) {
        int top = stack.top();
        stack.pop();
        if (not vis[top - 1]) {
            cout << "[ " << top << ", " << vis[top - 1] << " ]";
            vis[top - 1] = true;
        }
        for(int v : adj_list[top]) {
            if (not vis[v - 1]) {
                stack.push(v);    
            }
        }
    }
}

int count_component(miv adj_list, vi vertex_list) {
    st stack;
    int count = 0;
    vb visited;
    int l = vertex_list.size();
    for (int i = 0; i < l; i ++) {
        visited.push_back(false);
    }
    for (int v : vertex_list) {
        if (not visited[v - 1]) {
            dfs(v, adj_list, stack, visited);
            visited[v - 1] = true;
            count ++;
        }
    }
    return count;
}

int main() {
    int v_num, count;
    vi vertex;
    vvi Edges;
    miv adj_list;
    cout << " number of vertex : ";
    cin >> v_num;
    for(int i = 0; i < v_num; i ++) {
        vertex.push_back(i + 1);
    }
    int max_e = (v_num*(v_num - 1)) / 2;
    for (int i = 0; i < max_e; i ++) {
        int v1, v2;
        vi tup;
        cout << endl << "edge " << i + 1 << " : " << endl;
        cin >> v1;
        if (v1 == -1) break;
        cin >> v2;
        tup = {v1, v2};
        Edges.push_back(tup);
    }
    adj_list = adj_list_gen(vertex, Edges);
    for(const auto &pair: adj_list) {
        cout << endl << pair.first << " : ";
        for (int e : pair.second) cout << e;
    }
    cout << endl;
    count = count_component(adj_list, vertex);
    cout << " Number of connected components : " << count;
}
