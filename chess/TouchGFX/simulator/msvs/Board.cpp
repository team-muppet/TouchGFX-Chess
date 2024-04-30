#include <gui/chessgame_screen/Board.hpp>
#include "gui/chessgame_screen/Pawn.hpp" // Include concrete piece classes
#include "gui/chessgame_screen/Rook.hpp"
#include "gui/chessgame_screen/Knight.hpp"
#include "gui/chessgame_screen/Bishop.hpp"
#include "gui/chessgame_screen/Queen.hpp"
#include "gui/chessgame_screen/King.hpp"
#include <BitmapDatabase.hpp>

#define BOARD_HEIGHT 272
#define BOARD_WIDTH 272
#define NUM_SQUARES 8

Board::Board()
{
}

Board::~Board()
{
}

void Board::setupBoard() {
    // Clear the board first
    //clearBoard(); make this function

    //// Calculate the size of each square
    //int squareWidth = BOARD_WIDTH / NUM_SQUARES;
    //int squareHeight = BOARD_HEIGHT / NUM_SQUARES;


    //// Initialize WHITE pieces
    //// Initialize WHITE pieces
    //for (int i = 0; i < NUM_SQUARES; ++i) {
    //    for (int j = 0; j < NUM_SQUARES; ++j) {
    //        ScalableImage pieceImage;
    //        // Calculate the position of the center of the current square
    //        int centerX = (i * squareWidth) + (squareWidth / 2);
    //        int centerY = (j * squareHeight) + (squareHeight / 2);

    //        // Set the position of the pieceImage to the center of the current square
    //        pieceImage.setPosition(centerX - (pieceImage.getWidth() / 2), centerY - (pieceImage.getHeight() / 2), pieceImage.getWidth(), pieceImage.getHeight());

    //        add(pieceImage); // Add the pieceImage to the board (the screen)
    //        // Initialize a new Pawn with the calculated position
    //        _board[i * NUM_SQUARES + j] = new Pawn(PieceColor::WHITE);
    //    }
    //}

        // Clear the board first
        // clearBoard(); // You may implement this function later

        // Calculate the size of each square
        int squareWidth = BOARD_WIDTH / NUM_SQUARES;
        int squareHeight = BOARD_HEIGHT / NUM_SQUARES;

        // Initialize WHITE pieces
        for (int i = 0; i < NUM_SQUARES; ++i) {
            for (int j = 0; j < NUM_SQUARES; ++j) {
                // Calculate the position of the center of the current square
                int centerX = (i * squareWidth) + (squareWidth / 2);
                int centerY = (j * squareHeight) + (squareHeight / 2);

                // Create and set the position of the pieceImage to the center of the current square
                ScalableImage* pieceImage = new ScalableImage();
                pieceImage->setPosition(centerX - (pieceImage->getWidth() / 2), centerY - (pieceImage->getHeight() / 2), 33, 33);

                // Add the pieceImage to the board (the screen)
                add(*pieceImage);

                // Initialize a new Pawn with the calculated position
                _board[i * NUM_SQUARES + j] = new Pawn(PieceColor::WHITE);
            }
        }



    _board[0 * 8 + 0] = new Rook(PieceColor::WHITE);
    _board[0 * 8 + 1] = new Knight(PieceColor::WHITE);
    _board[0 * 8 + 2] = new Bishop(PieceColor::WHITE);
    _board[0 * 8 + 3] = new Queen(PieceColor::WHITE);
    _board[0 * 8 + 4] = new King(PieceColor::WHITE);
    _board[0 * 8 + 5] = new Bishop(PieceColor::WHITE);
    _board[0 * 8 + 6] = new Knight(PieceColor::WHITE);
    _board[0 * 8 + 7] = new Rook(PieceColor::WHITE);

    // Initialize BLACK pieces
    for (int i = 0; i < 8; ++i) {
        _board[6 * 8 + i] = new Pawn(PieceColor::BLACK); // BLACK pawns at second-to-last row
    }
    _board[7 * 8 + 0] = new Rook(PieceColor::BLACK);
    _board[7 * 8 + 1] = new Knight(PieceColor::BLACK);
    _board[7 * 8 + 2] = new Bishop(PieceColor::BLACK);
    _board[7 * 8 + 3] = new Queen(PieceColor::BLACK);
    _board[7 * 8 + 4] = new King(PieceColor::BLACK);
    _board[7 * 8 + 5] = new Bishop(PieceColor::BLACK);
    _board[7 * 8 + 6] = new Knight(PieceColor::BLACK);
    _board[7 * 8 + 7] = new Rook(PieceColor::BLACK);
}

