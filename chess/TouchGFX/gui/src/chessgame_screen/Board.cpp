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

Board::Board() : _currentPlayer(PieceColor::WHITE) {
    setupBoard();
    setWidth(272);
    setHeight(272);
}

Board::~Board() {}

void Board::setupBoard() {
    // Initialize WHITE pawns
    for (int j = 0; j < NUM_SQUARES; ++j) {
        int position = j + NUM_SQUARES;
        _board[position] = new Pawn(PieceColor::WHITE, position, this);
    }

    // Initialize BLACK pawns
    for (int j = 0; j < NUM_SQUARES; ++j) {
        int position = 6 * NUM_SQUARES + j;
        _board[position] = new Pawn(PieceColor::BLACK, position, this);
    }

    // Initialize other pieces
    // BLACK Bishops
    int bishopPositions[] = { 2, 5 };
    for (int j = 0; j < 2; ++j) {
        int position = (NUM_SQUARES - 1) * NUM_SQUARES + bishopPositions[j];
        _board[position] = new Bishop(PieceColor::BLACK, position, this);
    }

    // WHITE Bishops
    for (int j = 0; j < 2; ++j) {
        int position = bishopPositions[j];
        _board[position] = new Bishop(PieceColor::WHITE, position, this);
    }

    // BLACK Knights
    int knightPositions[] = { 1, 6 };
    for (int j = 0; j < 2; ++j) {
        int position = (NUM_SQUARES - 1) * NUM_SQUARES + knightPositions[j];
        _board[position] = new Knight(PieceColor::BLACK, position, this);
    }

    // WHITE Knights
    for (int j = 0; j < 2; ++j) {
        int position = knightPositions[j];
        _board[position] = new Knight(PieceColor::WHITE, position, this);
    }

    // BLACK Queen
    int position = (NUM_SQUARES - 1) * NUM_SQUARES + 3;
    _board[position] = new Queen(PieceColor::BLACK, position, this);

    // WHITE Queen
    position = 3;
    _board[position] = new Queen(PieceColor::WHITE, position, this);

    // BLACK King
    position = (NUM_SQUARES - 1) * NUM_SQUARES + 4;
    _board[position] = new King(PieceColor::BLACK, position, this);

    // WHITE King
    position = 4;
    _board[position] = new King(PieceColor::WHITE, position, this);

    // BLACK Rooks
    int rookPositions[] = { 0, 7 };
    for (int j = 0; j < 2; ++j) {
        position = (NUM_SQUARES - 1) * NUM_SQUARES + rookPositions[j];
        _board[position] = new Rook(PieceColor::BLACK, position, this);
    }

    // WHITE Rooks
    for (int j = 0; j < 2; ++j) {
        position = rookPositions[j];
        _board[position] = new Rook(PieceColor::WHITE, position, this);
    }
}

void Board::handleClickEvent(int position) {
    if (position < 0 || position >= NUM_SQUARES * NUM_SQUARES) {
        return;
    }

    AbstractPiece* piece = _board[position];
    if (piece == nullptr) {
        return;
    }

    /*if (piece->GetColor() != _currentPlayer) {
        return;
    }*/

    AbstractPiece const** const_board = const_cast<AbstractPiece const**>(_board);

    std::list<int> possibleMoves = piece->PossibleMoves(const_board, position);



    // Tests


    /*_board[position] = new Rook(PieceColor::WHITE, position);
    auto image = _board[position]->GetImage();
    add(*image);


    image->invalidate();*/

    /*piece->Move(++position);

    this->invalidate();*/
}
