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

Board::Board() : _currentPlayer(PieceColor::WHITE)
{
    //setTouchable(true);
    // Create and set the position of the pieceImage to the center of the current square
    /*ScalableImage* pieceImage = new ScalableImage();
    pieceImage->setBitmap(Bitmap(BITMAP_BLACKPAWN_ID));
    pieceImage->setPosition(55, 55, 33, 33);
    _board[0] = new Pawn(PieceColor::WHITE, pieceImage);*/

    // Add the pieceImage to the board (the screen)
    /*pieceImage.setVisible(true);
    pieceImage.invalidate();*/
    /*add(*_board[0]->_image);*/

   /* _board[0]->_image->setVisible(true);
    _board[0]->_image->invalidate();*/
	setupBoard();
    setWidth(272);
    setHeight(272);
}

Board::~Board()
{
}

void Board::setupBoard() {


    //// Calculate the size of each square
    int squareWidth = BOARD_WIDTH / NUM_SQUARES;
    int squareHeight = BOARD_HEIGHT / NUM_SQUARES;


   
    //// Initialize WHITE pawns pieces
        for (int j = 0; j < NUM_SQUARES; ++j) {
            ScalableImage* pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            int centerX = (j * squareWidth) + (squareWidth / 2);
            int centerY = (squareHeight) + (squareHeight / 2);
            pieceImage->setBitmap(Bitmap(BITMAP_WHITEPAWN_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX-16, centerY-16, 33, 33);
            // Initialize a new Pawn with the calculated position
            _board[j + NUM_SQUARES] = new Pawn(PieceColor::WHITE, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[j+NUM_SQUARES]->_image);
        }
        
    //// Initialize BLACK pieces
    // Initialize BLACK pawns pieces
        for (int j = 0; j < NUM_SQUARES; ++j) {
            ScalableImage* pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            int centerX = (j * squareWidth) + (squareWidth / 2);
            int centerY = (NUM_SQUARES - 2) * squareHeight + (squareHeight / 2); // Second-to-last row
            pieceImage->setBitmap(Bitmap(BITMAP_BLACKPAWN_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Pawn with the calculated position
            _board[6 * NUM_SQUARES + j] = new Pawn(PieceColor::BLACK, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[6 * NUM_SQUARES + j]->_image);
        }

        // Initialize BLACK Bishops pieces
        for (int j = 0; j < 2; ++j) {
            ScalableImage* pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            int centerX = (2 + (j * 3)) * squareWidth + (squareWidth / 2); // Third or sixth square
            int centerY = (NUM_SQUARES - 1) * squareHeight + (squareHeight / 2); // Last row
            pieceImage->setBitmap(Bitmap(BITMAP_BLACKBISHOP_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Bishop with the calculated position
            _board[(NUM_SQUARES - 1) * NUM_SQUARES + (2 + (j * 3))] = new Bishop(PieceColor::BLACK, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[(NUM_SQUARES - 1) * NUM_SQUARES + (2 + (j * 3))]->_image);
        }

        // Initialize BLACK Knights pieces
        for (int j = 0; j < 2; ++j) {
            ScalableImage* pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            int centerX = (1 + (j * 5)) * squareWidth + (squareWidth / 2); // Second or seventh square
            int centerY = (NUM_SQUARES - 1) * squareHeight + (squareHeight / 2); // Last row
            pieceImage->setBitmap(Bitmap(BITMAP_BLACKHORSE_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Knight with the calculated position
            _board[(NUM_SQUARES - 1) * NUM_SQUARES + (1 + (j * 5))] = new Knight(PieceColor::BLACK, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[(NUM_SQUARES - 1) * NUM_SQUARES + (1 + (j * 5))]->_image);
        }

        // Initialize WHITE Bishops pieces
        for (int j = 0; j < 2; ++j) {
            ScalableImage* pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            int centerX = (2 + (j * 3)) * squareWidth + (squareWidth / 2); // Third or sixth square
            int centerY = squareHeight / 2; // First row
            pieceImage->setBitmap(Bitmap(BITMAP_WHITEBISHOP_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Bishop with the calculated position
            _board[2 + (j * 3)] = new Bishop(PieceColor::WHITE, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[2 + (j * 3)]->_image);
        }

        // Initialize WHITE Knights pieces
        for (int j = 0; j < 2; ++j) {
            ScalableImage* pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            int centerX = (1 + (j * 5)) * squareWidth + (squareWidth / 2); // Second or seventh square
            int centerY = squareHeight / 2; // First row
            pieceImage->setBitmap(Bitmap(BITMAP_WHITEHORSE_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Knight with the calculated position
            _board[1 + (j * 5)] = new Knight(PieceColor::WHITE, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[1 + (j * 5)]->_image);
        }

        // Initialize BLACK Queen piece
        ScalableImage* pieceImage = new ScalableImage();
        // Calculate the position of the center of the current square
        int centerX = (3 * squareWidth) + (squareWidth / 2); // Fourth square
        int centerY = (NUM_SQUARES - 1) * squareHeight + (squareHeight / 2); // Last row
        pieceImage->setBitmap(Bitmap(BITMAP_BLACKQUEEN_ID));
        // Set the position of the pieceImage to the center of the current square
        pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
        // Initialize a new Queen with the calculated position
        _board[(NUM_SQUARES - 1) * NUM_SQUARES + 3] = new Queen(PieceColor::BLACK, pieceImage);
        // Add the pieceImage to the board (the screen)
        add(*_board[(NUM_SQUARES - 1) * NUM_SQUARES + 3]->_image);

        // Initialize BLACK King piece
        pieceImage = new ScalableImage();
        // Calculate the position of the center of the current square
        centerX = (4 * squareWidth) + (squareWidth / 2); // Fifth square
        centerY = (NUM_SQUARES - 1) * squareHeight + (squareHeight / 2); // Last row
        pieceImage->setBitmap(Bitmap(BITMAP_BLACKKING_ID));
        // Set the position of the pieceImage to the center of the current square
        pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
        // Initialize a new King with the calculated position
        _board[(NUM_SQUARES - 1) * NUM_SQUARES + 4] = new King(PieceColor::BLACK, pieceImage);
        // Add the pieceImage to the board (the screen)
        add(*_board[(NUM_SQUARES - 1) * NUM_SQUARES + 4]->_image);

        // Initialize BLACK Rooks pieces
        for (int j = 0; j < 2; ++j) {
            pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            centerX = (j == 0 ? 0 : (NUM_SQUARES - 1) * squareWidth) + (squareWidth / 2); // First or last square
            centerY = (NUM_SQUARES - 1) * squareHeight + (squareHeight / 2); // Last row
            pieceImage->setBitmap(Bitmap(BITMAP_BLACKROOK_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Rook with the calculated position
            _board[(NUM_SQUARES - 1) * NUM_SQUARES + (j == 0 ? 0 : 7)] = new Rook(PieceColor::BLACK, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[(NUM_SQUARES - 1) * NUM_SQUARES + (j == 0 ? 0 : 7)]->_image);
        }



        // Initialize pawns (already done in previous loop)
        // Initialize WHITE Queen piece
        pieceImage = new ScalableImage();
        // Calculate the position of the center of the current square
        centerX = (3 * squareWidth) + (squareWidth / 2); // Fourth square
        centerY = squareHeight / 2; // First row
        pieceImage->setBitmap(Bitmap(BITMAP_WHITEQUEEN_ID));
        // Set the position of the pieceImage to the center of the current square
        pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
        // Initialize a new Queen with the calculated position
        _board[3] = new Queen(PieceColor::WHITE, pieceImage);
        // Add the pieceImage to the board (the screen)
        add(*_board[3]->_image);

        // Initialize WHITE King piece
        pieceImage = new ScalableImage();
        // Calculate the position of the center of the current square
        centerX = (4 * squareWidth) + (squareWidth / 2); // Fifth square
        centerY = squareHeight / 2; // First row
        pieceImage->setBitmap(Bitmap(BITMAP_WHITEKING_ID));
        // Set the position of the pieceImage to the center of the current square
        pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
        // Initialize a new King with the calculated position
        _board[4] = new King(PieceColor::WHITE, pieceImage);
        // Add the pieceImage to the board (the screen)
        add(*_board[4]->_image);

        // Initialize WHITE Rooks pieces
        for (int j = 0; j < 2; ++j) {
            pieceImage = new ScalableImage();
            // Calculate the position of the center of the current square
            centerX = (j == 0 ? 0 : 7) * squareWidth + (squareWidth / 2); // First or last square
            centerY = squareHeight / 2; // First row
            pieceImage->setBitmap(Bitmap(BITMAP_WHITEROOK_ID));
            // Set the position of the pieceImage to the center of the current square
            pieceImage->setPosition(centerX - 16, centerY - 16, 33, 33);
            // Initialize a new Rook with the calculated position
            _board[(j == 0 ? 0 : 7)] = new Rook(PieceColor::WHITE, pieceImage);
            // Add the pieceImage to the board (the screen)
            add(*_board[(j == 0 ? 0 : 7)]->_image);
        }




}

void Board::handleClickEvent(int position)
{
    // Check if the clicked position is valid
    if (position < 0 || position >= NUM_SQUARES * NUM_SQUARES) {
		return;
	}

	// Get the piece at the clicked position
	AbstractPiece* piece = _board[position];
    if (piece == nullptr) {
		return;
	}

	// Check if the piece belongs to the current player
    if (piece->GetColor() != _currentPlayer) {
		return;
	}

	// Get the possible moves for the piece
	std::list<int> possibleMoves = piece->PossibleMoves(_board, position);

    ScalableImage* image = new ScalableImage();
           image->setBitmap(Bitmap(BITMAP_WHITEHORSE_ID));
          image->setPosition(60, 60, 33, 33);

           _board[18] = new Knight(PieceColor::WHITE, image);
       
           add(*_board[18]->_image);

           _board[18]->_image->setVisible(true);
           _board[18]->_image->invalidate();


	//// Highlight the possible moves
 //   for (int move : possibleMoves) {
 //       // Set the image of the possible move to the white horse
 //       ScalableImage* image = new ScalableImage();
 //       image->setBitmap(Bitmap(BITMAP_WHITEHORSE_ID));
 //       image->setPosition(55, 55, 33, 33);

 //       _board[move] = new Knight(PieceColor::WHITE, image);
 //   
 //       add(*_board[move]->_image);
  
		// Highlight the move
		// _board[move]->highlight();
	//}
}

