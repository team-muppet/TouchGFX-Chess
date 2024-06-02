#include <gui/chessgame_screen/Board.hpp>
#include <gui/chessgame_screen/Pawn.hpp>
#include <gui/chessgame_screen/Rook.hpp>
#include <gui/chessgame_screen/Knight.hpp>
#include <gui/chessgame_screen/Bishop.hpp>
#include <gui/chessgame_screen/Queen.hpp>
#include <gui/chessgame_screen/King.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/widgets/canvas/PainterABGR2222.hpp>

#define BOARD_HEIGHT 272
#define BOARD_WIDTH 272
#define NUM_SQUARES 8

Board::Board()
    : _currentPlayer(PieceColor::WHITE), _pieceSelector(this), _selectedPiecePosition(-1)
{
    setupBoard();
    setWidth(272);
    setHeight(272);
}

Board::~Board() {}

void Board::setupBoard() {
    // Initialize BLACK pawns
    for (int j = 0; j < NUM_SQUARES; ++j) {
        int position = j + NUM_SQUARES;
        addPiece(std::make_unique<Pawn>(PieceColor::BLACK, position, this), position);
    }

    // Initialize WHITE pawns
    for (int j = 0; j < NUM_SQUARES; ++j) {
        int position = 6 * NUM_SQUARES + j;
        addPiece(std::make_unique<Pawn>(PieceColor::WHITE, position, this), position);
    }

    // Initialize other pieces
    // WHITE Bishops
    int bishopPositions[] = { 2, 5 };
    for (int j = 0; j < 2; ++j) {
        int position = (NUM_SQUARES - 1) * NUM_SQUARES + bishopPositions[j];
        addPiece(std::make_unique<Bishop>(PieceColor::WHITE, position, this), position);
    }

    // BLACK Bishops
    for (int j = 0; j < 2; ++j) {
        int position = bishopPositions[j];
        addPiece(std::make_unique<Bishop>(PieceColor::BLACK, position, this), position);
    }

    // WHITE Knights
    int knightPositions[] = { 1, 6 };
    for (int j = 0; j < 2; ++j) {
        int position = (NUM_SQUARES - 1) * NUM_SQUARES + knightPositions[j];
        addPiece(std::make_unique<Knight>(PieceColor::WHITE, position, this), position);
    }

    // BLACK Knights
    for (int j = 0; j < 2; ++j) {
        int position = knightPositions[j];
        addPiece(std::make_unique<Knight>(PieceColor::BLACK, position, this), position);
    }

    // WHITE Queen
    int position = (NUM_SQUARES - 1) * NUM_SQUARES + 3;
    addPiece(std::make_unique<Queen>(PieceColor::WHITE, position, this), position);

    // BLACK Queen
    position = 3;
    addPiece(std::make_unique<Queen>(PieceColor::BLACK, position, this), position);

    // WHITE King
    position = (NUM_SQUARES - 1) * NUM_SQUARES + 4;
    addPiece(std::make_unique<King>(PieceColor::WHITE, position, this), position);

    // BLACK King
    position = 4;
    addPiece(std::make_unique<King>(PieceColor::BLACK, position, this), position);

    // WHITE Rooks
    int rookPositions[] = { 0, 7 };
    for (int j = 0; j < 2; ++j) {
        position = (NUM_SQUARES - 1) * NUM_SQUARES + rookPositions[j];
        addPiece(std::make_unique<Rook>(PieceColor::WHITE, position, this), position);
    }

    // BLACK Rooks
    for (int j = 0; j < 2; ++j) {
        position = rookPositions[j];
        addPiece(std::make_unique<Rook>(PieceColor::BLACK, position, this), position);
    }
}

void Board::handleClickEvent(int position) {
    if (position < 0 || position >= NUM_SQUARES * NUM_SQUARES) {
        return;
    }

    auto& piece = _board[position];
    if (_selectedPiecePosition == -1) {
        if (piece && piece->GetColor() == _currentPlayer) {
            _selectedPiecePosition = position;
            highlightPieceAndMoves(position);
        }
    }
    else {
        if (position == _selectedPiecePosition) {
            _pieceSelector.deselectPiece();
            _selectedPiecePosition = -1;
        }
        else if (_pieceSelector.isPossibleMove(position)) {
            MovePiece(_selectedPiecePosition, position);
            _pieceSelector.deselectPiece();
            _selectedPiecePosition = -1;
            _currentPlayer = (_currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
        }
        else {
            _pieceSelector.deselectPiece();
            if (piece && piece->GetColor() == _currentPlayer) {
                _selectedPiecePosition = position;
                highlightPieceAndMoves(position);
            }
            else {
                _selectedPiecePosition = -1;
            }
        }
    }
}

void Board::MovePiece(int from, int to) {
    _board[from]->Move(to);
    _board[to] = nullptr;
    _board[to] = std::move(_board[from]);
    _board[from] = nullptr;
}

void Board::addPiece(std::unique_ptr<AbstractPiece> piece, int position) {
    _board[position] = std::move(piece);
}

void Board::highlightPieceAndMoves(int position) {
    auto& piece = _board[position];
    if (!piece) {
        return;
    }

    std::list<int> possibleMoves = piece->PossibleMoves(_board.data(), position);
    _pieceSelector.selectPiece(position, possibleMoves);
}
