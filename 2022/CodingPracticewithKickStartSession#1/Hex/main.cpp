#include <bits/stdc++.h>
using namespace std;

// DFS traverse, visit all cells.
void markPath(const vector<vector<char>>& board, vector<vector<bool>>& visited, int x, int y, char chess){
    int n = board.size();
    if(x < 0 || x >= n || y < 0 || y >= n || visited[x][y] || board[x][y] != chess) return;
    visited[x][y] = true;

    // Check top left
    markPath(board, visited, x - 1, y, chess);
    // Check top right
    markPath(board, visited, x - 1, y + 1, chess);
    // Check left.
    markPath(board, visited, x, y - 1, chess);
    // check right.
    markPath(board, visited, x, y + 1, chess);
    // Check bottom-left.
    markPath(board, visited, x + 1, y - 1, chess);
    // check bottom.
    markPath(board, visited, x + 1, y, chess);
}

bool checkRedWins(const vector<vector<char>>& board){
    int n = board.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        markPath(board, visited, 0, i, 'R');
    }

    for(int i = 0; i < n; i++){
        if(visited[n - 1][i]) return true; // End of the board visited.
    }

    return false;
}

bool checkBlueWins(const vector<vector<char>>& board){
    int n = board.size();
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    for(int i = 0; i < n; i++){
        markPath(board, visited, i, 0, 'B');
    }

    for(int i = 0; i < n; i++){
        if(visited[i][n - 1]) return true; // End of the board visited.
    }

    return false;
}

string FindBoardStatus(vector<vector<char>>& board) {
    int n = board.size();
    int redCount = 0, blueCount = 0;
    for(auto& row : board){
      for(char c : row){
          if(c == 'R') redCount ++;
          else if(c == 'B') blueCount ++;
      }
    }
    
    if(abs(redCount - blueCount) > 1) return "Impossible";
    
    if(checkRedWins(board)){
        if(blueCount > redCount){ // Blue count is bigger, means blue is last step and Red could not win.
            return "Impossible";
        }

        // Check whether Red is double win: removing one red would break the win.
        for(int k = 0;k < n; k++){
            for(int l = 0;l < n; l ++){
                if(board[k][l] == 'R'){
                    board[k][l] = '.'; // Remove one Red.
                    bool redWins = !checkRedWins(board);
                    board[k][l] = 'R'; // Restore Red

                    if(redWins){ // The cross is broken, means Red wins only once.
                        return "Red wins";
                    }
                }
            }
        }

        return "Impossible"; // Couldn't break the cross by removing one Red, this means double wining.
    }
    
    if(checkBlueWins(board)){
        if(redCount > blueCount){ // Red count is bigger, means red is last step and blue could not win.
            return "Impossible";
        }

        // Check whether Blue is double win: removing one blue would break the win.
        for(int k = 0;k < n; k++){
            for(int l = 0;l < n; l ++){
                if(board[k][l] == 'B'){
                    board[k][l] = '.'; // Remove one Blue.
                    bool redWins = !checkBlueWins(board);
                    board[k][l] = 'B'; // Restore Blue

                    if(redWins){ // The cross is broken, means Blue wins only once.
                        return "Blue wins";
                    }
                }
            }
        }

        return "Impossible"; // Couldn't break the cross by removing one Blue, this means double wining.
    }

    return "Nobody wins";
}

int main() {
  int t;
  cin >> t;
  for (int tc = 1; tc <= t; ++tc) {
    int n;
    cin >> n;
    vector<vector<char>> board(n, vector<char>(n));
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        cin >> board[r][c];
      }
    }
    cout << "Case #" << tc << ": " << FindBoardStatus(board) << endl;
  }
  return 0;
}
