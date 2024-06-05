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
    : _squareRenderer(),
    _boardRenderer(),
    _pieceSelector(),
    playerTurnCallback(nullptr) // Initialize callback to nullptr
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

void Board::setupBoard()
{
    _boardRenderer.setupBoard(_boardState.getBoard());
    for (int i = 0; i < NUM_SQUARES * NUM_SQUARES; ++i)
    {
        auto& piece = _boardState.getBoard()[i];
        if (piece)
        {
            if (piece->GetType() == PieceType::KING)
            {
                if (piece->GetColor() == PieceColor::WHITE)
                {
                    _boardState.setWhiteKingPosition(i);
                }
                else
                {
                    _boardState.setBlackKingPosition(i);
                }
            }
        }
    }

    updateBoardColors(); // Ensure the board is updated after setup
}

void Board::handleClickEvent(int position)
{
    if (position < 0 || position >= NUM_SQUARES * NUM_SQUARES)
    {
        return;
    }

    auto& piece = _boardState.getBoard()[position];
    if (_boardState.getLastMoveFrom() == -1)
    {
        if (piece && piece->GetColor() == _boardState.getCurrentPlayer())
        {
            _boardState.setLastMoveFrom(position);
            highlightPieceAndMoves(position);
        }
    }
    else
    {
        if (position == _boardState.getLastMoveFrom())
        {
            _pieceSelector.deselectPiece();
            _boardState.setLastMoveFrom(-1);
            updateBoardColors();
        }
        else if (_pieceSelector.isPossibleMove(position))
        {
            MovePiece(_boardState.getLastMoveFrom(), position);
            _pieceSelector.deselectPiece();
            //_boardState.setLastMoveFrom(-1);
            _boardState.setCurrentPlayer(
                (_boardState.getCurrentPlayer() == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE);
            updateBoardColors();

            if (playerTurnCallback && playerTurnCallback->isValid())
            {
                playerTurnCallback->execute(_boardState.getCurrentPlayer()); // Notify the view about the player turn change
            }

            if (_boardState.isKingInCheck(PieceColor::WHITE) != -1 || _boardState.isKingInCheck(PieceColor::BLACK) != -1)
            {
                new Snackbar(this, BITMAP_CHECKIMAGE_ID, 86, 116);
            }

            if (_boardState.hasCheckmate(_boardState.getCurrentPlayer()))
            {
                new Snackbar(this, BITMAP_CHECKMATEIMAGE_ID, 86, 116);
                // Add additional logic for checkmate if needed, like ending the game
            }

            // Check if pawn promotion is possible
            if (piece->GetType() == PieceType::PAWN && (position < 8 || position >= 56))
            {
                _boardRenderer.promotePawn(_boardState.getBoard(), position);
            }

			//// Check if the game is a draw
			//if (!_boardState.hasLegalMoves(PieceColor::WHITE) && !_boardState.hasLegalMoves(PieceColor::BLACK))
			//{
			//	Snackbar* drawSnackbar = new Snackbar(this, BITMAP_DRAWIMAGE_ID, 86, 116);
   //         }
			//check if move is castling move the move the rook
			if (piece->GetType() == PieceType::KING && abs(_boardState.getLastMoveFrom() - position) == 2)
			{
				int rookPosition = -1;
				int rookDestination = -1;
				if (position == 2)
				{
					rookPosition = 0;
					rookDestination = 3;
				}
				else if (position == 6)
				{
					rookPosition = 7;
					rookDestination = 5;
				}
				else if (position == 58)
				{
					rookPosition = 56;
					rookDestination = 59;
				}
				else if (position == 62)
				{
					rookPosition = 63;
					rookDestination = 61;
				}
				if (rookPosition != -1 && rookDestination != -1)
				{
					MovePiece(rookPosition, rookDestination);
				}
			}

        }
        else
        {
            _pieceSelector.deselectPiece();
            if (piece && piece->GetColor() == _boardState.getCurrentPlayer())
            {
                _boardState.setLastMoveFrom(position);
                highlightPieceAndMoves(position);
            }
            else
            {
                _boardState.setLastMoveFrom(-1);
                updateBoardColors();
            }
        }
    }
}

void Board::MovePiece(int from, int to)
{
    // Ensure the piece at 'from' is moved to its new position internally
    _boardState.getBoard()[from]->Move(to);

    // If there is a piece at the destination 'to', remove it from the container
    if (_boardState.getBoard()[to] != nullptr)
    {
        _boardState.getBoard()[to] = nullptr;
        _squareRenderer.updateSquareColor(to, CAPTURE_MOVE_COLOR); // Highlight the capture move
    }

    // Move the piece from 'from' to 'to'
    _boardState.getBoard()[to] = std::move(_boardState.getBoard()[from]);
    _boardState.getBoard()[from] = nullptr;

    // Update the king position if a king is moved
    if (_boardState.getBoard()[to] && _boardState.getBoard()[to]->GetType() == PieceType::KING)
    {
        if (_boardState.getBoard()[to]->GetColor() == PieceColor::WHITE)
        {
            _boardState.setWhiteKingPosition(to);
        }
        else
        {
            _boardState.setBlackKingPosition(to);
        }
    }

    // Store the last move positions
    _boardState.setLastMoveFrom(from);
    _boardState.setLastMoveTo(to);

    // Update the board colors
    updateBoardColors();

    _boardState.getBoard()[to]->SetMoved(); // Set the piece as moved
}

void Board::saveGame(int _gameNumber)
{
    _boardStateModel.setBoard(_boardState.getBoard());
    _boardStateModel.setCurrentPlayer(_boardState.getCurrentPlayer());
    _savedGames[_gameNumber] = _gameStateSerializer.SerializeGameState(_boardStateModel);
}

void Board::highlightPieceAndMoves(int position)
{
    auto& piece = _boardState.getBoard()[position];
    if (!piece)
    {
        return;
    }

    std::list<int> possibleMoves = piece->PossibleMoves(_boardState.getBoard().data(), position);
    std::list<int> validMoves = _boardState.filterValidMoves(possibleMoves, position);
    std::list<int> captureMoves;

    // Identify capture moves within valid moves
    for (int pos : validMoves)
    {
        if (_boardState.getBoard()[pos] != nullptr && _boardState.getBoard()[pos]->GetColor() != piece->GetColor())
        {
            captureMoves.push_back(pos);
        }
    }

    _pieceSelector.selectPiece(position, validMoves, captureMoves);

    // Update board colors to highlight valid moves and captures
    updateBoardColors();
}

void Board::resetGame()
{
    _boardState.reset();
    updateBoardColors();
}

void Board::loadGame(int _gameNumber)
{
    _boardStateModel = _gameStateSerializer.DeserializeGameState(_savedGames[_gameNumber], _boardRenderer);
    _boardState.setBoard(std::move(_boardStateModel.getBoard()));
    _boardState.setCurrentPlayer(_boardStateModel.getCurrentPlayer());

    updateBoardColors();
}

void Board::updateBoardColors()
{
    // Reset all squares to their default colors
    _squareRenderer.resetSquareColors();

    // Highlight the last move
    if (_boardState.getLastMoveFrom() >= 0 && _boardState.getLastMoveFrom() < 64)
    {
        _squareRenderer.updateSquareColor(_boardState.getLastMoveFrom(), LAST_MOVE_COLOR);
    }
    if (_boardState.getLastMoveTo() >= 0 && _boardState.getLastMoveTo() < 64)
    {
        _squareRenderer.updateSquareColor(_boardState.getLastMoveTo(), LAST_MOVE_COLOR);
    }

    // Highlight capture moves
    for (int pos : _pieceSelector.getCaptureMoves())
    {
        _squareRenderer.updateSquareColor(pos, CAPTURE_MOVE_COLOR);
    }

    // Check if any king is in check and highlight the checking piece
    int whiteKingCheckPosition = _boardState.isKingInCheck(PieceColor::WHITE);
    int blackKingCheckPosition = _boardState.isKingInCheck(PieceColor::BLACK);
    if (whiteKingCheckPosition != -1)
    {
        _squareRenderer.updateSquareColor(whiteKingCheckPosition, KING_CHECK_COLOR); // Light Red
    }
    if (blackKingCheckPosition != -1)
    {
        _squareRenderer.updateSquareColor(blackKingCheckPosition, KING_CHECK_COLOR); // Light Red
    }

    // Invalidate the board to trigger a redraw
    invalidate();
}

void Board::setPlayerTurnCallback(touchgfx::GenericCallback<PieceColor>* callback)
{
    playerTurnCallback = callback;
}

PieceColor Board::getPlayerTurn()
{
    return _boardState.getCurrentPlayer();
}
