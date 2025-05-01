#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    // Main function to solve the Sudoku
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

    // Function to check if placing a number is valid
    bool isValid(const vector<vector<char>>& board, int row, int col, char num) {
        for (int i = 0; i < 9; ++i) {
            // Check row
            if (board[row][i] == num) 
                return false;
            // Check column
            if (board[i][col] == num) 
                return false;
            // Check 3x3 subgrid
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num)
                return false;
        }
        return true;
    }

private:
    // Recursive function to solve the Sudoku
    bool solve(vector<vector<char>>& board) {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (board[row][col] == '.') { // Empty cell
                    for (char num = '1'; num <= '9'; ++num) {
                        if (isValid(board, row, col, num)) {
                            board[row][col] = num; // Place the number
                            if (solve(board)) {   // Recursive call
                                return true;
                            }
                            board[row][col] = '.'; // Backtrack
                        }
                    }
                    return false; // No number fits here, backtrack
                }
            }
        }
        return true; // Solved
    }
};

// Function to display the Sudoku board
void displayBoard(const vector<vector<char>>& board) {
    cout << "  +-------+-------+-------+" << endl;
    for (int row = 0; row < 9; ++row) {
        cout << "  | ";
        for (int col = 0; col < 9; ++col) {
            cout << (board[row][col] == '.' ? '.' : board[row][col]) << " ";
            if ((col + 1) % 3 == 0) cout << "| ";
        }
        cout << endl;
        if ((row + 1) % 3 == 0) cout << "  +-------+-------+-------+" << endl;
    }
}

// Function for manual solving of Sudoku
void manualSolve(vector<vector<char>>& board, Solution& solution) {
    while (true) {
        displayBoard(board);
        cout << "Enter the row (1-9), column (1-9), and number (1-9) to insert (or 0 to quit): ";
        int row, col;
        char num;
        cin >> row;
        if (row == 0) break; // Quit
        cin >> col >> num;

        // Convert to zero-based indexing
        row -= 1;
        col -= 1;

        if (row < 0 || row >= 9 || col < 0 || col >= 9 || num < '1' || num > '9') {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        if (board[row][col] != '.') {
            cout << "Cell already filled. Try a different cell." << endl;
            continue;
        }

        if (!solution.isValid(board, row, col, num)) {
            cout << "Invalid move! " << num << " cannot be placed at row " << row + 1 << ", column " << col + 1 << "." << endl;
            continue;
        }

        board[row][col] = num;
        cout << "Number placed successfully!" << endl;

        // Check if board is fully solved
        bool solved = true;
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] == '.') {
                    solved = false;
                    break;
                }
            }
        }
        if (solved) {
            cout << "Congratulations! You solved the Sudoku!" << endl;
            break;
        }
    }
}

int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    Solution solution;
    cout << "Welcome to the Sudoku Solver!" << endl;
    cout << "Please enter your name: ";
    string name;
    getline(cin, name);
    cout << "Hello, " << name << "! Let's solve some Sudoku puzzles!" << endl;

    cout << "Choose an option:\n1. Solve automatically\n2. Solve manually\nYour choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        solution.solveSudoku(board);
        cout << "Solved Sudoku board:" << endl;
        displayBoard(board);
    } else if (choice == 2) {
        manualSolve(board, solution);
    } else {
        cout << "Invalid choice. Exiting the program." << endl;
    }

    cout << "Thank you for using Sudoku Solver, " << name << "! Have a great day!" << endl;
    return 0;
}
