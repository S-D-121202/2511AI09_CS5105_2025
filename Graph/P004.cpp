#include<iostream>
#include<vector>
#include<queue>
#include<map>

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using mvb = map<vi, bool>;
using Q = queue<vi>;

vvi neighbour_finder(int i, int j, int r, int c) {
    vvi ret;
    int i_up = -1;
    int i_do = -1;
    int j_le = -1;
    int j_ri = -1;
    if ((0 < i) and (i < r - 1)) {
        i_up = i - 1;
        i_do = i + 1;
    }
    else if (i == 0) i_do = i + 1;
    else i_up = i - 1;
    if ((0 < j) and (j < c - 1)) {
        j_le = j - 1;
        j_ri = j + 1;
    }
    else if (j == 0) j_ri = j + 1;
    else j_le = j - 1;
    if (i_up != -1) {
        vi t_up = {i_up, j};
        ret.push_back(t_up);
    }
    if (i_do != -1) {
        vi t_do = {i_do, j};
        ret.push_back(t_do);
    }
    if (j_le != -1) {
        vi t_le = {i, j_le};
        ret.push_back(t_le);
    }
    if (j_ri != -1) {
        vi t_ri = {i, j_ri};
        ret.push_back(t_ri);
    }
    return ret;
}

vvi dist_count(vvi M, int r, int c) {
    mvb visited;
    vvi starts;
    vvi dist(r, vi(c, 0));
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            vi tup = {i, j};
            if (M[i][j] == 1) {
                starts.push_back(tup);
                dist[i][j] = 0;
            } 
            visited.insert({tup, false});
        }
    }
    Q q;
    for (vi st : starts) {
        q.push(st);
    }
    while (not q.empty()) {
        vi index = q.front();
        q.pop();
        if (not visited[index]) {
            cout << "[" << index[0] << index[1] << "]" << " : ";
            visited[index] = true;
            vvi neighbours = neighbour_finder(index[0], index[1], r, c);
            for (vi neighbour : neighbours) {
                cout << "[" << neighbour[0] << neighbour[1] << "]";
                if (not visited[neighbour]) {
                    int x = neighbour[0];
                    int y = neighbour[1];
                    if (M[x][y] == 0)
                        if (dist[x][y] == 0) {
                            dist[x][y] = dist[index[0]][index[1]] + 1;
                        }
                        else {
                            if (dist[x][y] > (dist[index[0]][index[1]] + 1)) {
                                dist[x][y] = dist[index[0]][index[1]] + 1;
                            }
                        }
                    q.push(neighbour);
                }
                cout << endl;
            }
        }
    }
    return dist;
}

int main() {
    int rows, cols, i, j;
    cout << " Number of rows : ";
    cin >> rows;
    cout << " Number of columns : ";
    cin >> cols;
    cout << endl;
    cout << " Enter the matrix : ";
    vvi Matrix;
    for(i = 0; i < rows; i ++) {
        vi row;
        for (j = 0; j < cols; j ++) {
            int x;
            cin >> x;
            row.push_back(x);
        }
        Matrix.push_back(row);
    }
    vvi distance = dist_count(Matrix, rows, cols);
    cout << " distance_Matrix  : " << endl;
    for (i = 0; i < rows; i ++) {
        cout << endl;
        for (j = 0; j < cols; j ++) {
            cout << distance[i][j] << " ";
        }
    }  
}