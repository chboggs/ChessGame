// Chess 
// Author: Christopher Boggs
// Description: A two player chess game which prints out the board every move!

#include <iostream>
#include "PiecesAndBoard.cpp"

using namespace std;


bool IsGameOver(ChessBoard &board, char playerTurn) {
	// Check that the current player can move
	// If not, we have a stalemate or checkmate
	bool canMove(false);
	canMove = board.CanMove(playerTurn);
	if (!canMove) {
		if (board.IsInCheck(playerTurn)) {
            playerTurn = (playerTurn == 'W') ? 'B' : 'W';
			std::cout << "Checkmate, " << playerTurn << " Wins!" << std::endl;
		} else {
			std::cout << "Stalemate!" << std::endl;
		}
	}
	return !canMove;
}

int main() {
    ChessBoard gameBoard;
    ChessBoard checkBoard;
    char playerTurn('W');
    bool isValidMove = false;
    while (!IsGameOver(checkBoard, playerTurn)) {
        bool validMove = false;
        gameBoard.PrintBoard();
        // Get input and convert to coordinates
        cout << playerTurn << "'s Move: ";
        int startMove;
        cin >> startMove;
        int startRow = (startMove / 10) - 1;
        int startColumn = (startMove % 10) - 1;
        cout << "To: ";
        int endMove;
        cin >> endMove;
        int endRow = (endMove / 10) - 1;
        int endColumn = (endMove % 10) - 1;
        // Check that the indices are in range
        // and that the source and destination are different
        if ((startRow >= 0 && startRow <= 7) && (startColumn >= 0 && startColumn <= 7) && (endRow >= 0 && endRow <= 7) &&
            (endColumn >= 0 && endColumn <= 7)) {
            // Additional checks for legality
            Piece* currentPiece = gameBoard.board[startRow][startColumn];
            // Check that the piece is the correct color
            if ((currentPiece != 0) && (currentPiece->GetColor() == playerTurn)) {
                // Check that the destination is a valid destination
                if (currentPiece->IsLegalMove(startRow, startColumn, endRow, endColumn, gameBoard.board)) {
                    // Make the move
                    Piece* tempSquare = gameBoard.board[endRow][endColumn];
                    gameBoard.board[endRow][endColumn] = gameBoard.board[startRow][startColumn];
                    gameBoard.board[startRow][startColumn] = 0;
                    // Make sure that the current player is not in check
                    if (!gameBoard.IsInCheck(playerTurn)) {
                        delete tempSquare;
                        validMove = true;
                    }
                    else { // Undo the last move
                        gameBoard.board[startRow][startColumn] = gameBoard.board[endRow][endColumn];
                        gameBoard.board[endRow][endColumn] = tempSquare;
                    }
                }
            }
        }
        if (!validMove) {
            cout << "Invalid Move!" << endl;
        }
        if (validMove) playerTurn = (playerTurn == 'W') ? 'B' : 'W';
        checkBoard = gameBoard;
    }
	return 0;
}