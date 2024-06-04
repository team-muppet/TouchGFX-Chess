#include <gui/chessgame_screen/Board.hpp>
#include <rapidjson.h>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include <string>
#include <gui/common/Snackbar.hpp>
#include <algorithm> // For std::find
#include <list> // For std::list

#define BOARD_HEIGHT 272
#define BOARD_WIDTH 272
#define NUM_SQUARES 8

const colortype CAPTURE_MOVE_COLOR = Color::getColorFromRGB(255, 69, 0);  // Soft Red/Orange
const colortype LAST_MOVE_COLOR = Color::getColorFromRGB(144, 238, 144); // Light Green
const colortype KING_CHECK_COLOR = Color::getColorFromRGB(255, 182, 193); // Light Red

Board::Board()
    : _currentPlayer(PieceColor::WHITE),
    _selectedPiecePosition(-1),
    _lastMoveFrom(-1),
    _lastMoveTo(-1),
    _whiteKingPosition(-1),
    _blackKingPosition(-1),
    _squareRenderer(),
    _boardRenderer(),
    _pieceSelector()
{
    setWidth(480);
    setHeight(272);
    add(_squareRenderer);
    add(_pieceSelector);
    add(_boardRenderer);
	_gameStateSerializer = GameStateSerializer();

    setupBoard();
}

Board::~Board() {}

void Board::setupBoard() {
    _boardRenderer.setupBoard(_board);
    for (int i = 0; i < NUM_SQUARES * NUM_SQUARES; ++i) {
        auto& piece = _board[i];
        if (piece) {
            if (piece->GetType() == PieceType::KING) {
                if (piece->GetColor() == PieceColor::WHITE) {
                    _whiteKingPosition = i;
                }
                else {
                    _blackKingPosition = i;
                }
            }
        }
    }

    _selectedPiecePosition = -1;
    _lastMoveFrom = -1;
    _lastMoveTo = -1;

    updateBoardColors(); // Ensure the board is updated after setup
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
            updateBoardColors();
        }
        else if (_pieceSelector.isPossibleMove(position)) {
            MovePiece(_selectedPiecePosition, position);
            _pieceSelector.deselectPiece();
            _selectedPiecePosition = -1;
            _currentPlayer = (_currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
            updateBoardColors();

            if (isKingInCheck(PieceColor::WHITE) != -1 || isKingInCheck(PieceColor::BLACK) != -1) {
                new Snackbar(this, BITMAP_CHECKIMAGE_ID, 86, 116);
            }

            if (hasCheckmate(_currentPlayer)) {
                new Snackbar(this, BITMAP_CHECKMATEIMAGE_ID, 86, 116);
                // Add additional logic for checkmate if needed, like ending the game
            }

			// Check if pawn promotion is possible
            if (piece->GetType() == PieceType::PAWN && (position < 8 || position >= 56)) {
				_boardRenderer.promotePawn(_board, position);
            }
        }
        else {
            _pieceSelector.deselectPiece();
            if (piece && piece->GetColor() == _currentPlayer) {
                _selectedPiecePosition = position;
                highlightPieceAndMoves(position);
            }
            else {
                _selectedPiecePosition = -1;
                updateBoardColors();
            }
        }
    }
}

void Board::MovePiece(int from, int to) {
    // Ensure the piece at 'from' is moved to its new position internally
    _board[from]->Move(to);

    // If there is a piece at the destination 'to', remove it from the container
    if (_board[to] != nullptr) {
        _board[to] = nullptr;
        _squareRenderer.updateSquareColor(to, CAPTURE_MOVE_COLOR); // Highlight the capture move
    }

    // Move the piece from 'from' to 'to'
    _board[to] = std::move(_board[from]);
    _board[from] = nullptr;

    // Update the king position if a king is moved
    if (_board[to] && _board[to]->GetType() == PieceType::KING) {
        if (_board[to]->GetColor() == PieceColor::WHITE) {
            _whiteKingPosition = to;
        }
        else {
            _blackKingPosition = to;
        }
    }

    // Store the last move positions
    _lastMoveFrom = from;
    _lastMoveTo = to;

    // Update the board colors
    updateBoardColors();

	_board[to]->SetMoved(); // Set the piece as moved
}

void Board::saveGame(int _gameNumber)
{
	_savedGames[_gameNumber] = _gameStateSerializer.SerializeGameState(_board, _currentPlayer);
}

void Board::highlightPieceAndMoves(int position) {
    auto& piece = _board[position];
    if (!piece) {
        return;
    }

    std::list<int> possibleMoves = piece->PossibleMoves(_board.data(), position);
    std::list<int> validMoves = filterValidMoves(possibleMoves, position);
    std::list<int> captureMoves;

    // Identify capture moves within valid moves
    for (int pos : validMoves) {
        if (_board[pos] != nullptr && _board[pos]->GetColor() != piece->GetColor()) {
            captureMoves.push_back(pos);
        }
    }

    _pieceSelector.selectPiece(position, validMoves, captureMoves);

    // Update board colors to highlight valid moves and captures
    updateBoardColors();
}

void Board::resetGame()
{
	_currentPlayer = PieceColor::WHITE;
    for (auto& piece : _board) {
        piece.reset();  // This sets the unique_ptr to nullptr
    }
    updateBoardColors();
}

void Board::loadGame(int _gameNumber)
{
    std::array<std::unique_ptr<AbstractPiece>, 64> tmpboard = _gameStateSerializer.DeserializeBoardState(_savedGames[_gameNumber], _boardRenderer);
	_currentPlayer = _gameStateSerializer.DeserializeCurrentPlayer(_savedGames[_gameNumber]);

	_boardRenderer.setupSavedBoard(_board, tmpboard);
	updateBoardColors();
}

void Board::updateBoardColors() {
    // Reset all squares to their default colors
    _squareRenderer.resetSquareColors();

    // Highlight the last move
    if (_lastMoveFrom >= 0 && _lastMoveFrom < 64) {
        _squareRenderer.updateSquareColor(_lastMoveFrom, LAST_MOVE_COLOR);
    }
    if (_lastMoveTo >= 0 && _lastMoveTo < 64) {
        _squareRenderer.updateSquareColor(_lastMoveTo, LAST_MOVE_COLOR);
    }

    // Highlight capture moves
    for (int pos : _pieceSelector.getCaptureMoves()) {
        _squareRenderer.updateSquareColor(pos, CAPTURE_MOVE_COLOR);
    }

    // Check if any king is in check and highlight the checking piece
    int whiteKingCheckPosition = isKingInCheck(PieceColor::WHITE);
    int blackKingCheckPosition = isKingInCheck(PieceColor::BLACK);
    if (whiteKingCheckPosition != -1) {
        _squareRenderer.updateSquareColor(whiteKingCheckPosition, KING_CHECK_COLOR); // Light Red
    }
    if (blackKingCheckPosition != -1) {
        _squareRenderer.updateSquareColor(blackKingCheckPosition, KING_CHECK_COLOR); // Light Red
    }

    // Invalidate the board to trigger a redraw
    invalidate();
}

int Board::isKingInCheck(PieceColor color) {
    int kingPosition = (color == PieceColor::WHITE) ? _whiteKingPosition : _blackKingPosition;

    if (kingPosition == -1) {
        return -1; // King not found, should not happen
    }

    // Check if any opponent piece can move to the king's position
    for (int i = 0; i < NUM_SQUARES * NUM_SQUARES; ++i) {
        auto& piece = _board[i];
        if (piece && piece->GetColor() != color) {
            std::list<int> possibleMoves = piece->PossibleMoves(_board.data(), i);
            if (std::find(possibleMoves.begin(), possibleMoves.end(), kingPosition) != possibleMoves.end()) {
                return i; // Return the position of the checking piece
            }
        }
    }

    return -1; // No check
}

bool Board::wouldMoveCauseCheck(int from, int to) {
    // Temporarily move the piece
    std::unique_ptr<AbstractPiece> tempPiece = std::move(_board[to]);
    _board[to] = std::move(_board[from]);
    _board[from] = nullptr;

    // Update king position if the king is moved
    if (_board[to] && _board[to]->GetType() == PieceType::KING) {
        if (_board[to]->GetColor() == PieceColor::WHITE) {
            _whiteKingPosition = to;
        }
        else {
            _blackKingPosition = to;
        }
    }

    bool isInCheck = isKingInCheck(_currentPlayer) != -1;

    // Undo the move
    _board[from] = std::move(_board[to]);
    _board[to] = std::move(tempPiece);

    // Restore king position if the king was moved
    if (_board[from] && _board[from]->GetType() == PieceType::KING) {
        if (_board[from]->GetColor() == PieceColor::WHITE) {
            _whiteKingPosition = from;
        }
        else {
            _blackKingPosition = from;
        }
    }

    return isInCheck;
}

bool Board::hasLegalMoves(PieceColor color) {
    for (int i = 0; i < NUM_SQUARES * NUM_SQUARES; ++i) {
        auto& piece = _board[i];
        if (piece && piece->GetColor() == color) {
            std::list<int> possibleMoves = piece->PossibleMoves(_board.data(), i);
            std::list<int> validMoves = filterValidMoves(possibleMoves, i);
            if (!validMoves.empty()) {
                return true;
            }
        }
    }
    return false;
}

bool Board::hasCheckmate(PieceColor color) {
    if (isKingInCheck(color) != -1 && !hasLegalMoves(color)) {
        return true;
    }
    return false;
}

std::list<int> Board::filterValidMoves(const std::list<int>& possibleMoves, int from) {
    std::list<int> validMoves;
    for (int to : possibleMoves) {
        if (!wouldMoveCauseCheck(from, to)) {
            validMoves.push_back(to);
        }
    }
    return validMoves;
}
