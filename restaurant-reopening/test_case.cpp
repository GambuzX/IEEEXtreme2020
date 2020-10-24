#include <iostream>
#include <vector>

using namespace std;

bool can_reach_stairs(const vector<vector<char>> &floor_map, int row, int col, vector<vector<bool>>& seen) {
    if (row < 0 || row >= floor_map.size() || col < 0 || col >= floor_map[0].size()) return false;
    if (seen[row][col]) return false;
    if (floor_map[row][col] == '#' || floor_map[row][col] == 't') return false;
    if (floor_map[row][col] == 'S') return true;
    
    seen[row][col] = true;
    vector<pair<int,int>> positions = {{row, col-1}, {row, col+1}, {row-1, col}, {row+1, col}};
    for(const pair<int,int>& p : positions) {
        if (can_reach_stairs(floor_map, p.first, p.second, seen)) return true;
    }
    return false;
}

bool can_reach_stairs(const vector<vector<char>> &floor_map, int row, int col) {
    vector<vector<bool>> seen(floor_map.size(), vector<bool>(floor_map[0].size(), false));
    return can_reach_stairs(floor_map, row, col, seen);
}

bool can_insert(vector<vector<char>> &floor_map, int row, int col) {
    if(floor_map[row][col] != '.') return false;
    int l,r,u,d;
    l = col-1;
    r = col == floor_map[0].size()-1 ? -1 : col+1;
    u = row-1;
    d = row == floor_map.size()-1 ? -1 : row+1;
   
    vector<pair<int,int>> positions = {{row, l}, {row, r}, {u, col}, {d, col}};
    for (const pair<int,int> &p : positions) {
        if (p.first == -1 || p.second == -1) continue;
        if (floor_map[p.first][p.second] == '#') continue;
        if (floor_map[p.first][p.second] == 't') return false;
        if (floor_map[p.first][p.second] == 'S') return false;
        
        floor_map[row][col] = 't';  // temporary insert
        bool can_reach = can_reach_stairs(floor_map, p.first, p.second);
        floor_map[row][col] = '.';
        if (!can_reach) return false;
    }
    return true;
}

int main() {
    int T, R, C;
    cin >> T;
    
    for(int i = 0; i < T; i++) {
        cin >> R >> C;
        vector<vector<char>> floor_map(R, vector<char>(C, '.'));
        for(int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                cin >> floor_map[r][c];
            }
        }
        
        int chairs = 0;
        for(int row = 0; row < R; row++) {
            for (int col = 0; col < C; col++) {
                char pos = floor_map[row][col];
                if (pos == 'S' || pos == '#') continue;
                
                if (can_insert(floor_map, row, col)) {
                    floor_map[row][col] = 't';
                    int l,r,u,d;
                    l = col - 1;
                    r = col == floor_map[0].size()-1 ? -1 : col+1;
                    u = row-1;
                    d = row == floor_map.size()-1 ? -1 : row+1;
                   
                    // count chairs
                    vector<pair<int,int>> positions = {{row, l}, {row, r}, {u, col}, {d, col}};
                    for(const pair<int,int>& p : positions) {
                        if(p.first == -1 || p.second == -1) continue;
                        if(floor_map[p.first][p.second] == '.')
                            chairs++;
                    }
                }
            }
        }
        /*for(int row = 0; row < R; row++) {
            for (int col = 0; col < C; col++) {
                cout << floor_map[row][col];
            }
            cout << endl;
        }*/
        
        cout << chairs << endl;
    }
}