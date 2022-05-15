#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> directions = {{0, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 0}, {1, -1}}; // From 0 -> size(), circle from the left clockwise.

bool tracePathFromNorthWest(const vector<vector<char>>& colorBoard, unordered_set<int> & pathHash){
    int n = colorBoard.size();
    int x = 0, y = 0, next = 4; // Start from 0, 0, the next element is the index of directions, directions[4] = {1, 0}
    while(x < n && y < n) { // Either x or y will reach to the other end.
        pathHash.insert(x * 1000 + y); // Use hash to get interception faster.
        int nextX = x + directions[next].first;
        int nextY = y + directions[next].second;

        if(colorBoard[nextX][nextY] == 'C') {
            x = nextX;
            y = nextY;
            next = (next - 1 + directions.size()) % directions.size(); // direction changed anti-clockwise

            if(y >= n - 1) return true;
            if(x >= n - 1 && y == 0) return false;
        }
        else {
            next = (next + 1) % directions.size(); // direction changed clockwise
        }
    }

    return y >= n - 1;
}

bool tracePathFromSouthWest(const vector<vector<char>>& colorBoard, unordered_set<int> & pathHash){
    int n = colorBoard.size();
    int x = n - 1, y = 0, next = 2; // Start from n -1, 0, the next element is the index of directions, directions[2] = {-1, 1}
    while(x >= 0 && y < n) { // Either x or y will reach to the other end.
        pathHash.insert(x * 1000 + y); // Use hash to get interception faster.
        int nextX = x + directions[next].first;
        int nextY = y + directions[next].second;

        if(colorBoard[nextX][nextY] == 'C') {
            x = nextX;
            y = nextY;
            next = (next + 1) % directions.size(); // direction changed clockwise

            if(y >= n - 1) return true;
            if(x <= 0 && y == 0) return false;
        }
        else {
            next = (next - 1 + directions.size()) % directions.size(); // direction changed anti-clockwise
        }
    }

    return y >= n - 1;
}

enum class Status{Impossible, Win, NotWin};
Status checkGameStatus(const vector<vector<char>>& colorBoard){
    int n = colorBoard.size();
    unordered_set<int> topPath;
    if(tracePathFromNorthWest(colorBoard, topPath)){
        unordered_set<int> bottomPath;
        tracePathFromSouthWest(colorBoard, bottomPath);

        for(int n : topPath){
            if(bottomPath.find(n) != bottomPath.end()){
                return Status::Win;// The two paths intercepted, means this is the only way to win.
            }
        }

        return Status::Impossible; // No interception, meaning deleting any chess won't break the win.
    }

    return Status::NotWin;
}

string FindBoardStatus(const vector<vector<char>>& board) {
    int n = board.size();
    int redCount = 0, blueCount = 0;
    // Extend the board by 1 on each side, in order to reduce the code lines, we put the different color on separate board.
    vector<vector<char>> blueBoard(n + 2, vector<char>(n + 2, '.'));
    vector<vector<char>> redBoard(n + 2, vector<char>(n + 2, '.'));
    for(int i = 0;i < n + 2; i ++){
        for(int j = 0;j < n + 2; j ++){
            if(j == 0 || j == n + 1){// First column and last column is the color we need to check, so we can always go through the column.
                blueBoard[i][j] = 'C';
                redBoard[i][j] = 'C';
            }
            else if(i != 0 && i != n + 1) { // The actual board is in the middle.
                if(board[i - 1][j - 1] == 'B'){
                    blueBoard[i][j] = 'C'; // Use the same character for Blue & Red, so that we can use the same code to check it.
                    blueCount ++;
                }
                
                if(board[j - 1][i - 1] == 'R'){ // Rotate the Red for easier checking.
                    redBoard[i][j] = 'C'; // Use the same character for Blue & Red, so that we can use the same code to check it.
                    redCount ++;
                }
            }
        }
    }

    if(abs(redCount - blueCount) > 1) return "Impossible"; // One color has two more steps.

    Status blueStatus = checkGameStatus(blueBoard);
    if(blueStatus == Status::Win) {
        if(blueCount >= redCount) return "Blue wins"; // Only equal steps or bigger steps can this color wins.
        else return "Impossible";
    }
    else if(blueStatus == Status::Impossible) return "Impossible";
    
    Status redStatus = checkGameStatus(redBoard);
    if(redStatus == Status::Win) {
        if(redCount >= blueCount) return "Red wins";  // Only equal steps or bigger steps can this color wins.
        else return "Impossible";
    }
    else if(redStatus == Status::Impossible) return "Impossible";

    return "Nobody wins";
}

int main() {
    ifstream fin("ts2_input.txt");
    ofstream fout("output.txt");
    // auto& fin = cin;
    // auto& fout = cout;
  int t;
  fin >> t;
  for (int tc = 1; tc <= t; ++tc) {
    int n;
    fin >> n;
    vector<vector<char>> board(n, vector<char>(n));
    for (int r = 0; r < n; ++r) {
      for (int c = 0; c < n; ++c) {
        fin >> board[r][c];
      }
    }
    fout << "Case #" << tc << ": " << FindBoardStatus(board) << endl;
  }
  return 0;
}
