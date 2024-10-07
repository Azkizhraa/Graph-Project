#include <iostream>
#include <vector>

#define N 5
// 5 5 square 
// 2 2 start position

using namespace std;

// All possible moves for a knight
int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

// Function to check if the move is valid
bool isValid(int x, int y, vector<vector<int>> &board) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Recursive function to solve the Knight's Tour problem
bool solveKTUtil(int x, int y, int movei, vector<vector<int>> &board, vector<pair<int, int>> &path) {
    if (movei == N * N) {
        return true; // All squares are visited
    }

    // Try all possible moves for the knight
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (isValid(nextX, nextY, board)) {
            board[nextX][nextY] = movei;
            path.push_back({nextX, nextY});
            if (solveKTUtil(nextX, nextY, movei + 1, board, path)) {
                return true;
            } else {
                // Backtrack if the move doesn't lead to a solution
                board[nextX][nextY] = -1;
                path.pop_back();
            }
        }
    }

    return false;
}

// Function to solve the Knight's Tour problem
bool solveKnightTour(int startX, int startY) {
    // Initialize the chessboard
    vector<vector<int>> board(N, vector<int>(N, -1));
    vector<pair<int, int>> path;

    // Place the knight at the starting position
    board[startX][startY] = 0;
    path.push_back({startX, startY});

    // Solve the Knight's Tour problem
    if (!solveKTUtil(startX, startY, 1, board, path)) {
        cout << "Solution does not exist" << endl;
        return false;
    } else {
        // Print the path as coordinates
        for (const auto &p : path) {
            cout << p.first << " " << p.second << endl;
        }
    }

    return true;
}

int main() {
    // Starting position (2, 2)
    int startX = 2, startY = 2;

    // Solve the Knight's Tour from the starting position
    solveKnightTour(startX, startY);

    return 0;
}
