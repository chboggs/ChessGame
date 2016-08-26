// Classes for each of the pieces with move checking member functions

#include <iostream>

const int boardSize = 8;

class Piece
{
public:
    Piece(char color) : pieceColor(color) {}
    ~Piece() {}
    virtual char GetPiece() = 0;
    char GetColor() {
        return pieceColor;
    }
    bool IsLegalMove(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        Piece* dest = board[destRow][destColumn];
        if ((dest == 0) || (pieceColor != dest->GetColor())) {
            return isDestinationLegal(startRow, startColumn, destRow, destColumn, board);
        }
        return false;
    }
private:
    virtual bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) = 0;
    char pieceColor;
};

class Pawn : public Piece
{
public:
    Pawn(char color) : Piece(color) {}
    ~Pawn() {}
private:
    virtual char GetPiece() {
        return 'P';
    }
    bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        Piece* dest = board[destRow][destColumn];
        if (dest == 0) {
            // Destination square is unoccupied
            if (startRow == 1 && destRow == 3 && GetColor() == 'W') return true;
            if (startRow == 6 && destRow == 4 && GetColor() == 'B') return true;
            if (startColumn == destColumn) {
                if (GetColor() == 'W') {
                    if (destRow == startRow + 1) {
                        return true;
                    }
                }
                else {
                    if (destRow == startRow - 1) {
                        return true;
                    }
                }
            }
        }
        else {
            // Dest holds piece of opposite color
            if ((startColumn == destColumn + 1) || (startColumn == destColumn - 1)) {
                if (GetColor() == 'W') {
                    if (destRow == startRow + 1) {
                        return true;
                    }
                }
                else {
                    if (destRow == startRow - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class Knight : public Piece
{
public:
    Knight(char color) : Piece(color) {}
    ~Knight() {}
private:
    virtual char GetPiece() {
        return 'N';
    }
    bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        // Destination square is unoccupied or occupied by opposite color
        if ((startColumn == destColumn + 1) || (startColumn == destColumn - 1)) {
            if ((startRow == destRow + 2) || (startRow == destRow - 2)) {
                return true;
            }
        }
        if ((startColumn == destColumn + 2) || (startColumn == destColumn - 2)) {
            if ((startRow == destRow + 1) || (startRow == destRow - 1)) {
                return true;
            }
        }
        return false;
    }
};

class Bishop : public Piece
{
public:
    Bishop(char color) : Piece(color) {}
    ~Bishop() {}
private:
    virtual char GetPiece() {
        return 'B';
    }
    bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        if ((destColumn - startColumn == destRow - startRow) || (destColumn - startColumn == startRow - destRow)) {
            // Make sure that all between squares are empty
            int rowOffset = (destRow - startRow > 0) ? 1 : -1;
            int columnOffset = (destColumn - startColumn > 0) ? 1 : -1;
            int checkRow = startRow + rowOffset;
            int checkColumn = startColumn + columnOffset;
            for (checkRow, checkColumn; checkRow != destRow; checkRow = checkRow + rowOffset, checkColumn = checkColumn + columnOffset) {
                if (board[checkRow][checkColumn] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Rook : public Piece
{
public:
    Rook(char color) : Piece(color) {}
    ~Rook() {}
private:
    virtual char GetPiece() {
        return 'R';
    }
    bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        if (startRow == destRow) {
            // Make sure that all between squares are empty
            int columnOffset = (destColumn - startColumn > 0) ? 1 : -1;
            for (int checkColumn = startColumn + columnOffset; checkColumn != destColumn; checkColumn = checkColumn + columnOffset) {
                if (board[startRow][checkColumn] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if (destColumn == startColumn) {
            // Make sure that all between squares are empty
            int rowOffset = (destRow - startRow > 0) ? 1 : -1;
            for (int checkRow = startRow + rowOffset; checkRow != destRow; checkRow = checkRow + rowOffset) {
                if (board[checkRow][startColumn] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class Queen : public Piece
{
public:
    Queen(char color) : Piece(color) {}
    ~Queen() {}
private:
    virtual char GetPiece() {
        return 'Q';
    }
    bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        if (startRow == destRow) {
            // Make sure that all between squares are empty
            int columnOffset = (destColumn - startColumn > 0) ? 1 : -1;
            for (int checkColumn = startColumn + columnOffset; checkColumn != destColumn; checkColumn = checkColumn + columnOffset) {
                if (board[startRow][checkColumn] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if (destColumn == startColumn) {
            // Make sure that all between squares are empty
            int rowOffset = (destRow - startRow > 0) ? 1 : -1;
            for (int checkRow = startRow + rowOffset; checkRow != destRow; checkRow = checkRow + rowOffset) {
                if (board[checkRow][startColumn] != 0) {
                    return false;
                }
            }
            return true;
        }
        else if ((destColumn - startColumn == destRow - startRow) || (destColumn - startColumn == startRow - destRow)) {
            // Make sure that all between squares are empty
            int rowOffset = (destRow - startRow > 0) ? 1 : -1;
            int columnOffset = (destColumn - startColumn > 0) ? 1 : -1;
            int checkRow = startRow + rowOffset;
            int checkColumn = startColumn + columnOffset;
            for (checkRow, checkColumn; checkRow != destRow; checkRow = checkRow + rowOffset, checkColumn = checkColumn + columnOffset) {
                if (board[checkRow][checkColumn] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class King : public Piece
{
public:
    King(char color) : Piece(color) {}
    ~King() {}
private:
    virtual char GetPiece() {
        return 'K';
    }
    bool isDestinationLegal(int startRow, int startColumn, int destRow, int destColumn, Piece* board[boardSize][boardSize]) {
        int newRow = destRow - startRow;
        int newColumn = destColumn - startColumn;
        if (((newRow >= -1) && (newRow <= 1)) &&
            ((newColumn >= -1) && (newColumn <= 1))) {
            return true;
        }
        return false;
    }
};

class ChessBoard
{
public:
    Piece* board[boardSize][boardSize];

    ChessBoard() {
        for (int row = 0; row < 8; ++row) {
            for (int column = 0; column < 8; ++column) {
                board[row][column] = 0;
            }
        }
        // Allocate and place black pieces
        for (int placeCol = 0; placeCol < 8; ++placeCol) {
            board[6][placeCol] = new Pawn('B');
        }
        board[7][0] = new Rook('B');
        board[7][1] = new Knight('B');
        board[7][2] = new Bishop('B');
        board[7][3] = new King('B');
        board[7][4] = new Queen('B');
        board[7][5] = new Bishop('B');
        board[7][6] = new Knight('B');
        board[7][7] = new Rook('B');
        // Allocate and place white pieces
        for (int placeCol = 0; placeCol < 8; ++placeCol) {
            board[1][placeCol] = new Pawn('W');
        }
        board[0][0] = new Rook('W');
        board[0][1] = new Knight('W');
        board[0][2] = new Bishop('W');
        board[0][3] = new King('W');
        board[0][4] = new Queen('W');
        board[0][5] = new Bishop('W');
        board[0][6] = new Knight('W');
        board[0][7] = new Rook('W');
    }
    ~ChessBoard() {
        for (int placeRow = 0; placeRow < 8; ++placeRow) {
            for (int placeCol = 0; placeCol < 8; ++placeCol) {
                delete board[placeRow][placeCol];
                board[placeRow][placeCol] = 0;
            }
        }
    }

    void PrintBoard() {
        using namespace std;
        const int squareWidth = 4;
        const int squareHeight = 3;
        for (int row = 0; row < 8 * squareHeight; ++row) {
            int squareRow = row / squareHeight;
            // Print side border with numbering
            if (row % 3 == 1) {
                cout << '-' << (char)('1' + 7 - squareRow) << '-';
            }
            else {
                cout << "---";
            }
            // Print the chess board
            for (int column = 0; column < 8 * squareWidth; ++column) {
                int squareColumn = column / squareWidth;
                if (((row % 3) == 1) && ((column % 4) == 1 || (column % 4) == 2) && board[7 - squareRow][squareColumn] != 0) {
                    if ((column % 4) == 1) {
                        cout << board[7 - squareRow][squareColumn]->GetColor();
                    }
                    else {
                        cout << board[7 - squareRow][squareColumn]->GetPiece();
                    }
                }
                else {
                    if ((squareRow + squareColumn) % 2 == 1) {
                        cout << '*';
                    }
                    else {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
        // Print the bottom border with numbers
        for (int row = 0; row < squareHeight; ++row) {
            if (row % 3 == 1) {
                cout << "---";
                for (int column = 0; column < 8 * squareWidth; ++column) {
                    int squareColumn = column / squareWidth;
                    if ((column % 4) == 1) {
                        cout << (squareColumn + 1);
                    }
                    else {
                        cout << '-';
                    }
                }
                cout << endl;
            }
            else {
                for (int column = 1; column < 9 * squareWidth; ++column) {
                    cout << '-';
                }
                cout << endl;
            }
        }
    }

    bool IsInCheck(char color) {
        // Find the king
        int kingRow;
        int kingColumn;
        for (int row = 0; row < 8; ++row) {
            for (int column = 0; column < 8; ++column) {
                if (board[row][column] != 0) {
                    if (board[row][column]->GetColor() == color) {
                        if (board[row][column]->GetPiece() == 'K') {
                            kingRow = row;
                            kingColumn = column;
                        }
                    }
                }
            }
        }
        // Run through the opponent's pieces and see if any can take the king
        for (int row = 0; row < 8; ++row) {
            for (int column = 0; column < 8; ++column) {
                if (board[row][column] != 0) {
                    if (board[row][column]->GetColor() != color) {
                        if (board[row][column]->IsLegalMove(row, column, kingRow, kingColumn, board)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char color) {
        // Run through all pieces
        for (int row = 0; row < 8; ++row) {
            for (int column = 0; column < 8; ++column) {
                if (board[row][column] != 0) {
                    // If it is a piece of the current player, see if it has a legal move
                    if (board[row][column]->GetColor() == color) {
                        for (int moveRow = 0; moveRow < 8; ++moveRow) {
                            for (int moveColumn = 0; moveColumn < 8; ++moveColumn) {
                                if (board[row][column]->IsLegalMove(row, column, moveRow, moveColumn, board)) {
                                    // Make move and check whether king is in check
                                    Piece* tempPiece = board[moveRow][moveColumn];
                                    board[moveRow][moveColumn] = board[row][column];
                                    board[row][column] = 0;
                                    bool canMove = !IsInCheck(color);
                                    // Undo the move
                                    board[row][column] = board[moveRow][moveColumn];
                                    board[moveRow][moveColumn] = tempPiece;
                                    if (canMove) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
};