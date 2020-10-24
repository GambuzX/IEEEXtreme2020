#include <iostream>
#include <vector>

using namespace std;

void print_board(const vector<vector<char>> &board) {
    for(size_t i = 0; i < board.size(); i++) {
        for(size_t j = 0; j < board.size(); j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

int main() {
    string s;
    int N, M;
    cin >> s >> N >> M;
    
    string r1, r2;
    r1 = s.substr(0, 5);
    r2 = s.substr(6, 5);
    
    vector<vector<char>> board(N, vector<char>(N, 0));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> board[i][j];
        }
    }
    
    for(int g = 0; g < M; g++) {
       vector<pair<int,int>> to_change;
       
       // determine values to change
       for(int row = 0; row < N; row++) {
            for(int col = 0; col < N; col++) {
               int l,r,u,d;
               l = col == 0 ? N-1 : col-1;
               r = col == N-1 ? 0 : col+1;
               u = row == 0 ? N-1 : row-1;
               d = row == N-1 ? 0 : row+1;
               
               // check alive neighbours
               vector<pair<int,int>> positions = {{row, l}, {row, r}, {u, col}, {d, col}};
               int alive_count = 0;
               for(const pair<int,int> &p : positions)
                    if (board[p.first][p.second] == '1')
                        alive_count++;
                
                // check rule
                if (board[row][col] == '0') {
                    if (r1[alive_count] == '1')
                        to_change.push_back({row, col});
                }
                else {
                    if (r2[alive_count] != '1')
                        to_change.push_back({row, col});
                }
               
           }
       }
       
       // update values
       for(const pair<int,int> &p : to_change) {
           char prev = board[p.first][p.second];
           board[p.first][p.second] = (prev == '0' ? '1' : '0');
       }
    }
    
    print_board(board);
    
    return 0;
}