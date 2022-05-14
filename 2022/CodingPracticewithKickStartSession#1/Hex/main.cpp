#include <bits/stdc++.h>
using namespace std;

// Return column index if it reached to other end, otherwise return -1;
int checkRedDFS(const vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited){
    int n = board.size();

    if(x == n - 1 && board[x][y] == 'R') return y; // Reached to the other end.

    auto checkNeighbor = [&board, &visited, n](int x, int y){
        if(x < 0 || x >= n || y < 0 || y >= n) return -1;
        if(!visited[x][y] && board[x][y] == 'R'){
            visited[x][y] = true;
            return checkRedDFS(board, x, y, visited);
        }

        return -1;
    };

    // Check left.
    int temp = checkNeighbor(x, y - 1);
    if(temp != -1) return temp;
    // check right.
    temp = checkNeighbor(x, y + 1);
    if(temp != -1) return temp;
    
    // Check bottom-left.
    temp = checkNeighbor(x + 1, y - 1);
    if(temp != -1) return temp;
    // check bottom.
    return checkNeighbor(x + 1, y);
}

// Return row index if it reached to other end, otherwise return -1;
int checkBlueDFS(const vector<vector<char>>& board, int x, int y, vector<vector<bool>>& visited){
    int n = board.size();

    if(y == n - 1 && board[x][y] == 'B') return x; // Reached to the other end.

    auto checkNeighbor = [&board, &visited, n](int x, int y){
        if(x < 0 || x >= n || y < 0 || y >= n) return -1;
        if(!visited[x][y] && board[x][y] == 'B'){
            visited[x][y] = true;
            return checkBlueDFS(board, x, y, visited);
        }

        return -1;
    };

    // Check left.
    int temp = checkNeighbor(x - 1, y);
    if(temp != -1) return temp;
    // check right.
    temp = checkNeighbor(x + 1, y);
    if(temp != -1) return temp;
    
    // Check bottom-left.
    temp = checkNeighbor(x - 1, y + 1);
    if(temp != -1) return temp;
    // check bottom.
    return checkNeighbor(x, y + 1);
}

string FindBoardStatus(const vector<vector<char>>& board) {
    int n = board.size();
    int redCount = 0, blueCount = 0;
    for(auto& row : board){
      for(char c : row){
          if(c == 'R') redCount ++;
          else if(c == 'B') blueCount ++;
      }
    }
    
    if(abs(redCount - blueCount) > 1) return "Impossible";
    
    int redWinEnd = -1;
    for(int i = 0;i < n; i++){
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        if(redWinEnd != -1) visited[n - 1][redWinEnd] = true; // To avoid end at the same spot.

        int end = checkRedDFS(board, 0, i, visited);
        if(end != -1){ // Win this one.
            if(redWinEnd != -1) return "Impossible"; // Win twice.
            redWinEnd = end;
        }
    }
    
    
    int blueWinEnd = -1;
    for(int i = 0;i < n; i++){
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        if(blueWinEnd != -1) visited[blueWinEnd][n - 1] = true;
        int end = checkBlueDFS(board, i, 0, visited);
        if(end != -1){ // Win this one.
            if(blueWinEnd != -1) return "Impossible"; // Win twice.
            blueWinEnd = end;
        }
    }

    if(redWinEnd != -1 && blueWinEnd != -1){
        return "Impossible"; // Double win.
    }
    else if(redWinEnd != -1){
        return "Red wins";
    }
    else if(blueWinEnd != -1){
        return "Blue wins";
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
