#include <gui/chessgame_screen/Board.hpp>
#include <rapidjson.h>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include <string>

#define BOARD_HEIGHT 272
#define BOARD_WIDTH 272
#define NUM_SQUARES 8

const colortype CAPTURE_MOVE_COLOR = Color::getColorFromRGB(255, 69, 0);  // Soft Red/Orange
const colortype LAST_MOVE_COLOR = Color::getColorFromRGB(144, 238, 144); // Light Green

Board::Board()
    : _currentPlayer(PieceColor::WHITE), _selectedPiecePosition(-1), _lastMoveFrom(-1), _lastMoveTo(-1), _squareRenderer(), _pieceSelector(), _boardRenderer()
{
    setWidth(272);
    setHeight(272);
    add(_squareRenderer); // Add the square renderer first
    add(_pieceSelector); // Add the piece selector second
    add(_boardRenderer); // Add the board renderer last

    setupBoard();
}

Board::~Board() {}

void Board::setupBoard() {
    _boardRenderer.setupBoard(_board);
    updateBoardColors(); // Ensure the board is updated after setup
}

void Board::handleClickEvent(int position) {
    serializeBoardState();
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
            updateBoardColors(); // Update the board colors
        }
        else if (_pieceSelector.isPossibleMove(position)) {
            MovePiece(_selectedPiecePosition, position);
            _pieceSelector.deselectPiece();
            _selectedPiecePosition = -1;
            _currentPlayer = (_currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
            updateBoardColors(); // Update the board colors
        }
        else {
            _pieceSelector.deselectPiece();
            if (piece && piece->GetColor() == _currentPlayer) {
                _selectedPiecePosition = position;
                highlightPieceAndMoves(position);
            }
            else {
                _selectedPiecePosition = -1;
                updateBoardColors(); // Update the board colors
            }
        }
    }
}

void Board::serializeBoardState() {
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    // Serialize the board
    rapidjson::Value boardArray(rapidjson::kArrayType);
    for (const auto& piece : _board) {
        if (piece) {
            rapidjson::Value pieceObject(rapidjson::kObjectType);
            pieceObject.AddMember("type", static_cast<int>(piece->GetType()), allocator);
            pieceObject.AddMember("color", static_cast<int>(piece->GetColor()), allocator);
            boardArray.PushBack(pieceObject, allocator);
        }
        else {
            boardArray.PushBack(rapidjson::Value(rapidjson::kNullType), allocator);
        }
    }
    document.AddMember("board", boardArray, allocator);
    document.AddMember("currentPlayer", static_cast<int>(_currentPlayer), allocator);

    // Convert JSON document to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    int size = buffer.GetSize();

    std::string serializedBoard = buffer.GetString();
    std::string serializedBoards(serializedBoard, size);
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

    // Store the last move positions
    _lastMoveFrom = from;
    _lastMoveTo = to;

    // Update the board colors
    updateBoardColors();
}

void Board::highlightPieceAndMoves(int position) {
    auto& piece = _board[position];
    if (!piece) {
        return;
    }

    std::list<int> possibleMoves = piece->PossibleMoves(_board.data(), position);
    std::list<int> captureMoves;

    // Identify capture moves
    for (int pos : possibleMoves) {
        if (_board[pos] != nullptr && _board[pos]->GetColor() != piece->GetColor()) {
            captureMoves.push_back(pos);
        }
    }

    _pieceSelector.selectPiece(position, possibleMoves, captureMoves);

    // Update board colors to highlight possible moves and captures
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

    // Invalidate the board to trigger a redraw
    invalidate();
}
