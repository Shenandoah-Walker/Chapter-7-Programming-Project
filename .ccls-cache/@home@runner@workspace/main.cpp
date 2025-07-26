//Tic-Tac-Toe Program

#include <iostream>
using namespace std;

//Initialize constants for board states and assign values to them. These constants will be used to determine the state of the game.
const int PLAY = 0;
const int TIE = 1;
const int X_WINS = 2;
const int O_WINS = 3;

//Initialize constants to check for winner and assign values to them. These constants will be used to determine if there is a winner or if there are spaces left on the board.
const int SPACE_LEFT = 0;
const int NO_SPACE = 1;
const int WINNER = 2;

// Declare the board as a 2D array of characters
char board[3][3];

// Function prototypes

/*
Function: initializeBoard
Purpose: Initializes the board with asterisks (*) to represent empty spaces.
Parameters: None
Returns: None
Preconditions: None
Postconditions: 
 - The board is initialized with asterisks (*) to represent empty spaces.
*/
void initializeBoard();

/*
Function: displayBoard
Purpose: Displays the board.
Parameters: None
Returns: None
Preconditions: None
Postconditions: The board is displayed.
*/
void displayBoard();

/*
Function: placeToken
Purpose: Places a token on the board.
Parameters: 
 - token: The token to place on the board.
Returns: None
Preconditions: None
Postconditions: The token is placed on the board.
*/
void placeToken(char token);

/*
Function: getLocation
Purpose: Gets the location of the token from the user.
Parameters:
 - row: The row number where the token will be placed.
 - col: The column number where the token will be placed.
Returns: None
Preconditions: None
Postconditions: The row and column numbers are set to the location of the token.
*/
void getLocation(int& row, int& col);

/*
Function: getBoardState
Purpose: Gets the state of the board.
Parameters:
 - token: The token to check for a winner.
Returns: The state of the board.
Preconditions: None
Postconditions: The state of the board is returned.
*/
int getBoardState(char token);

/*
Function: checkForWinner
Purpose: Checks if there is a winner and if there are spaces left on the board.
Parameters:
 - token: The token to check for a winner.
Returns: The state of the board.
Preconditions: None
Postconditions: The state of the board is returned.
*/
int checkForWinner(char token);


int main() {
    int boardState = PLAY;
    char player1_token = 'X';
    char player2_token = 'O';

    // Initialize and display the empty board, then prompt the user to hit enter to continue
    initializeBoard();
    displayBoard();
    cout << endl << "(Hit enter to continue)";
    cin.get();
    cout << endl << endl;

    while (boardState == PLAY) {

        // Player 1's turn
        cout << "Player 1's turn" << endl;
        placeToken(player1_token);
        displayBoard();
        boardState = getBoardState(player1_token);

        if (boardState == X_WINS) {
            break;
        }

        if (boardState == PLAY) {
            // Player 2's turn
            cout << "Player 2's turn" << endl;
            placeToken(player2_token);
            displayBoard();
            boardState = getBoardState(player2_token);
        }
    }

    // Declare the winner or tie
    if (boardState == X_WINS) {
        cout << "Player 1 wins" << endl;
    }
    else if (boardState == O_WINS) {
        cout << "Player 2 wins" << endl;
    }
    else if (boardState == TIE) {
        cout << "Tie" << endl;
    }

    return 0;
}
//Use the initializeBoard function to initialize the board with asterisks (*) to represent empty spaces. 
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = '*';
        }
    }
}

//Use the displayBoard function to display the board.
void displayBoard() {
    cout << "    1   2   3" << endl;
    cout << "   -----------" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "|" << (i + 1) << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << "   ";
        }

        if (i < 2) cout << " " << endl;
    }
    cout << endl;
}

//Use the placeToken function to place a token on the board.
void placeToken(char token) {
    int row, col;
    getLocation(row, col);
    board[row][col] = token;
}

//Use the getLocation function to get the location of the token from the user.
void getLocation(int& row, int& col) {
    bool validLocation = false;

    //Loop until a valid location is entered
    while (!validLocation) {
        // Prompt user for to enter the row number where he or she would like to place a token.
        do {
            cout << "Enter row number (must be 1, 2, or 3): ";
            cin >> row;
            //Ensure that the row number entered is between 1 and 3.
            if (row < 1 || row > 3) {
                cout << "Row must be between 1 and 3. Please enter a different row number." << endl;
            }
        } while (row < 1 || row > 3);

        //Prompt user to enter the column number where he or she would like to place a token.
        do {
            cout << "Enter column number (must be 1, 2, or 3): ";
            cin >> col;
            //Ensure that the column number entered is between 1 and 3.
            if (col < 1 || col > 3) {
                cout << "Column must be between 1 and 3. Please enter a different row number." << endl;
            }
        } while (col < 1 || col > 3);

        //Because the board is 0-based (It is an array), 1 must be subtracted from both the row numbers and the column numbers entered by the user to get the correct index.
        row--;
        col--;

        //Check if the space is empty. If it is, set validLocation to true. If it is not, prompt the user to enter a different row and column number.
        if (board[row][col] == '*') {
            validLocation = true;
        }
        else {
            cout << "That space is already taken. Please choose another space that is empty, desigated by an asterisk (*)." << endl;

    //Convert back to 1-based indexing for the next iteration. This is necessary because the row and column numbers are decremented by 1 to get the correct index.
            row++;
            col++;
        }
    }
}

int getBoardState(char token) {
    int state = checkForWinner(token);

    if (state == WINNER) {
        if (token == 'X') {
            return X_WINS;
        }
        else {
            return O_WINS;
        }
    }
    else if (state == NO_SPACE) {
        return TIE;
    }
    else {
        return PLAY;
    }
}

//Use the checkForWinner function to check if there is a winner and if there are spaces left on the board.
int checkForWinner(char token) {

    //Check rows.
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == token && board[i][1] == token && board[i][2] == token) {
            return WINNER;
        }
    }

    //Check columns.
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == token && board[1][j] == token && board[2][j] == token) {
            return WINNER;
        }
    }

    //Check diagonals.
    if (board[0][0] == token && board[1][1] == token && board[2][2] == token) {
        return WINNER;
    }
    if (board[0][2] == token && board[1][1] == token && board[2][0] == token) {
        return WINNER;
    }

    //Check for available spaces.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '*') {
                return SPACE_LEFT;
            }
        }
    }

    //If there is no winner and there are no spaces left, return NO_SPACE.
    return NO_SPACE;
}
