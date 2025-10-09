#include<iostream>
#include<vector>
#include<map>

using namespace std;

map<int, vector<int>> adj_list_gen(vector<int> vertices, vector<vector<int>> edges) {
    map<int, vector<int>> adj_list;
    int edge_nums = edges.size();
    for (int v : vertices) {
        vector<int> neighbours;
        adj_list.insert({v, neighbours});
    }
    for (vector<int> e : edges) {
        adj_list[e[0]].push_back(e[1]);
        adj_list[e[1]].push_back(e[0]);
    }
    return adj_list;
}

void bfs(int v, map<int, vector<int>> adj_list, vector<bool>& vis, vector<int>& queue, vector<int>& ret) {
    queue.push_back(v);
    while (not queue.empty()) {
        int v = queue.front();
        queue.erase(queue.begin());
        if (not vis[v - 1]) {
            ret.push_back(v);
            cout << v << " ";
            vis[v - 1] = true;
        }
        for (int nei : adj_list[v]) {
            if (not vis[nei - 1]) {
                queue.push_back(nei);
            }
        }
    }
}

vector<int> bfs_list_gen(map<int, vector<int>> adj_list, vector<int> V) {
    vector<int> queue, ret;
    vector<bool> visited;
    int l = adj_list.size();
    for (int i = 0; i < l; i ++) {
        visited.push_back(false);
    }
    for (int v : V) {
        if (not visited[v - 1]) {
            bfs(v, adj_list, visited, queue, ret);
            visited[v - 1] = true;
        }
    }
    return ret;
}

int main() {
    vector<int> V;
    vector<vector<int>> E;
    int num;
    cout << "Number of vrtices : ";
    cin >> num;
    for (int i = 0; i < num; i ++) {
        V.push_back(i + 1);
    }
    int max_edges = (num*(num - 1)) / 2;
    for(int j = 0; j < max_edges; j ++) {
        cout << " Edge " << (j + 1); 
        int v_1, v_2;
        cout << " 1st Vertex Number : ";
        cin >> v_1;
        cout << " 2nd Vertex Number : ";
        cin >> v_2;
        if ((v_1 == -1) or (v_2 == -1)) {
            break;
        }
        vector<int> tup = {v_1, v_2};
        E.push_back(tup);
    }
    int edge_num = E.size();
    for (int k = 0; k < edge_num; k ++) {
        cout << "(" << E[k][0] << ", " << E[k][1] << ")";
    }
    map<int, vector<int>> adj_list = adj_list_gen(V, E);
    for (const auto &pair: adj_list) {
        cout << endl << pair.first << " : ";
        for (int v : pair.second) cout << v;
    }
    vector<int> result = bfs_list_gen(adj_list, V);
    cout << " BFS traversal : ";
    for (int e : result) {
        cout << e << " ";
    }
}

