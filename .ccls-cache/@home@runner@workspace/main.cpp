//Tic-Tac-Toe Program

#include <iostream>
using namespace std;

// Constants
const int boardSize = 3;
const char emptyCell = '*';
const char player1Token = 'X';
const char player2Token = 'O';

// Board state constants
const int statePlay = 0;
const int stateTie = 1;
const int stateXWin = 2;
const int stateOWin = 3;

// Win check result constants
const int resultSpaceLeft = 0;
const int resultNoSpace = 1;
const int resultWinner = 2;

// Function Prototypes
void initializeBoard(char board[boardSize][boardSize]);
void displayBoard(const char board[boardSize][boardSize]);
void placeToken(char token, char board[boardSize][boardSize]);
void getLocation(int &row, int &col, const char board[boardSize][boardSize]);
int getBoardState(char token, const char board[boardSize][boardSize]);
int checkForWinner(char token, const char board[boardSize][boardSize]);

// ---------------- Main Function ------------------
int main() {
    char board[boardSize][boardSize];
    int boardState = statePlay;

    initializeBoard(board);
    displayBoard(board);

    while (boardState == statePlay) {
        // Player 1
        placeToken(player1Token, board);
        displayBoard(board);
        boardState = getBoardState(player1Token, board);
        if (boardState != statePlay) break;

        // Player 2
        placeToken(player2Token, board);
        displayBoard(board);
        boardState = getBoardState(player2Token, board);
    }

    // Final result
    if (boardState == stateXWin)
        cout << "Player 1 (X) wins!" << endl;
    else if (boardState == stateOWin)
        cout << "Player 2 (O) wins!" << endl;
    else if (boardState == stateTie)
        cout << "It's a tie!" << endl;

    return 0;
}

// 1. Initialize the board with '*'
void initializeBoard(char board[boardSize][boardSize]) {
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            board[i][j] = emptyCell;
}

// 2. Display the board with row and column headers (1–3)
void displayBoard(const char board[boardSize][boardSize]) {
    cout << "   1 2 3" << endl;
    for (int i = 0; i < boardSize; ++i) {
        cout << i + 1 << "  ";
        for (int j = 0; j < boardSize; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// 3. Place a token on the board
void placeToken(char token, char board[boardSize][boardSize]) {
    int row, col;
    cout << "Player " << (token == player1Token ? "1 (X)" : "2 (O)") << "'s turn:" << endl;
    getLocation(row, col, board);
    board[row][col] = token;
}

// 4. Prompt and validate location input
void getLocation(int &row, int &col, const char board[boardSize][boardSize]) {
    while (true) {
        cout << "Enter row (1–3): ";
        cin >> row;
        cout << "Enter column (1–3): ";
        cin >> col;

        row -= 1;
        col -= 1;

        if (row >= 0 && row < boardSize && col >= 0 && col < boardSize) {
            if (board[row][col] == emptyCell)
                return;
            else
                cout << "That cell is already taken. Try again." << endl;
        } else {
            cout << "Invalid input. Please enter numbers between 1 and 3." << endl;
        }
    }
}

// 5. Determine the current board state
int getBoardState(char token, const char board[boardSize][boardSize]) {
    int result = checkForWinner(token, board);

    if (result == resultWinner)
        return (token == player1Token) ? stateXWin : stateOWin;
    else if (result == resultNoSpace)
        return stateTie;
    else
        return statePlay;
}

// 6. Check win conditions or available space
int checkForWinner(char token, const char board[boardSize][boardSize]) {
    // Check rows and columns
    for (int i = 0; i < boardSize; ++i) {
        if ((board[i][0] == token && board[i][1] == token && board[i][2] == token) ||
            (board[0][i] == token && board[1][i] == token && board[2][i] == token)) {
            return resultWinner;
        }
    }

    // Check diagonals
    if ((board[0][0] == token && board[1][1] == token && board[2][2] == token) ||
        (board[0][2] == token && board[1][1] == token && board[2][0] == token)) {
        return resultWinner;
    }

    // Check for remaining empty cells
    for (int i = 0; i < boardSize; ++i)
        for (int j = 0; j < boardSize; ++j)
            if (board[i][j] == emptyCell)
                return resultSpaceLeft;

    return resultNoSpace;
}