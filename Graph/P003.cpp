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
    int row_up = -1;
    int row_do = -1;
    int col_le = -1;
    int col_ri = -1;
    vvi ret;
    if ((i < r - 1) and (i > 0)) {
        row_do = i + 1;
        row_up = i - 1;
    }
    else if (i == r - 1) {
        row_do = -1;
        row_up = i - 1;
    }
    else {
        row_do = i + 1;
        row_up = -1;
    }
    if ((j < c - 1) and (j > 0)) {
        col_le = j - 1;
        col_ri = j + 1;
    }
    else if(j == c - 1) {
        col_le = j - 1;
        col_ri = -1;
    }
    else {
        col_le = -1;
        col_ri = j + 1;
    }
    if (row_up == -1) {
        if (col_le == -1) {
            vi tup_1 = {i, col_ri};
            vi tup_2 = {row_do, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            return ret;
        }
        else if (col_ri == -1) {
            vi tup_1 = {i, col_le};
            vi tup_2 = {row_do, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            return ret;
        }
        else {
            vi tup_1 = {i, col_le};
            vi tup_2 = {i, col_ri};
            vi tup_3 = {row_do, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            ret.push_back(tup_3);
            return ret;
        }
    }
    else if (row_do == -1) {
        if (col_le == -1) {
            vi tup_1 = {i, col_ri};
            vi tup_2 = {row_up, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            return ret;
        }
        else if (col_ri == -1) {
            vi tup_1 = {i, col_le};
            vi tup_2 = {row_up, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            return ret;
        }
        else {
            vi tup_1 = {i, col_le};
            vi tup_2 = {i, col_ri};
            vi tup_3 = {row_up, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            ret.push_back(tup_3);
            return ret;
        }
    }
    else {
        if (col_le == -1) {
            vi tup_1 = {i, col_ri};
            vi tup_2 = {row_up, j};
            vi tup_3 = {row_do, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            ret.push_back(tup_3);
            return ret;
        }
        else if (col_ri == -1) {
            vi tup_1 = {i, col_le};
            vi tup_2 = {row_up, j};
            vi tup_3 = {row_do, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            ret.push_back(tup_3);
            return ret;
        }
        else {
            vi tup_1 = {i, col_le};
            vi tup_2 = {i, col_ri};
            vi tup_3 = {row_up, j};
            vi tup_4 = {row_do, j};
            ret.push_back(tup_1);
            ret.push_back(tup_2);
            ret.push_back(tup_3);
            ret.push_back(tup_4);
            return ret;
        }
    }
}

vi bfs(int st_i, int st_j, vvi &M, int r, int c) {
    int counter = 0;
    int rot_count = 0;
    mvb vis;
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            vi tup = {i, j};
            vis.insert({tup, false});
        }
    }
    Q queue;
    vi start_tup = {st_i, st_j};
    queue.push(start_tup);
    while(not queue.empty()) {
        vi index = queue.front();
        queue.pop();
        if (not vis[index]) {
            vis[index] = true;
            vvi neighbours = neighbour_finder(index[0], index[1], r, c);
            cout << "(" << index[0] << ", " << index[1] << "):";
            bool flag = false;
            for (vi nei : neighbours) {
                if (M[nei[0]][nei[1]] != 0) {
                    cout << "[" << nei[0] << ", " << nei[1] << "]  ";
                    if (not vis[nei]) {
                        if (M[nei[0]][nei[1]] == 1) {
                            M[nei[0]][nei[1]] = 2;
                            flag = true;
                        } 
                        queue.push(nei);
                    }
                }
            }
            if (flag) counter ++;
        }
    }
    for (int k = 0; k < r; k ++) {
        for (int l = 0; l < c; l ++) {
            if (M[k][l] == 2) rot_count ++;
        }
    }
    vi ret = {counter, rot_count};
    return ret;
}

int min_count(vvi &M, int r, int c) {
    int st_i = -1; 
    int st_j = -1;
    int count_0 = 0;
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            if (M[i][j] == 2) {
                st_i = i;
                st_j = j;
                break;
            }
        }
    }
    for (int k = 0; k < r; k ++) {
        for (int l = 0; l < c; l ++) {
            if (M[k][l] == 0) count_0 ++;
        }
    }
    cout << count_0 << endl; 
    if ((st_i == -1) and (st_j == -1)) return -1;
    else {
        vi result = bfs(st_i, st_j, M, r, c);
        cout << endl << result[0];
        if (result[1] == (r*c - count_0)) {
            return result[0];
        }
        else {
            cout << result[0];
            return -1;
        }
    }
}

int main() {
    int rows, cols;
    cout << " number of rows : ";
    cin >> rows;
    cout << endl << " Number of cols : ";
    cin >> cols;
    vvi Matrix;
    for (int i = 0; i < rows; i ++) {
        vi row;
        for (int j = 0; j < cols; j ++) {
            int num;
            cin >> num;
            row.push_back(num % 3);
        }
        Matrix.push_back(row);
    }
    int min_minute = min_count(Matrix, rows, cols);
    cout << " Minimum minute requered : " << min_minute;
    for (int k = 0; k < rows; k ++) {
        cout << endl;
        for (int l = 0; l < cols; l ++) {
            cout << Matrix[k][l] << " "; 
        }
    }
}