#ifndef BOARD_HPP
#define BOARD_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/canvas/Circle.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <stdlib.h>
#include <array>
#include <memory>
#include <utility>

#include <gui/chessgame_screen/AbstractPiece.hpp>
#include <gui/chessgame_screen/ChessEnums.hpp>
#include <gui/chessgame_screen/PieceSelector.hpp>
#include <gui/chessgame_screen/SquareRenderer.hpp>
#include <gui/chessgame_screen/BoardRenderer.hpp>
#include <gui/common/GameStateSerializer.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <touchgfx/containers/Container.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Callback.hpp>
#include <gui/chessgame_screen/BoardState.hpp>
#include <gui/chessgame_screen/BoardStateModel.hpp>

using namespace touchgfx;

class Board : public Container
{
public:
    Board();
    virtual ~Board();
    virtual void setupBoard();
    virtual void handleClickEvent(int position);

    // save and load game functions
    virtual void saveGame(int _gameNumber);
    virtual void loadGame(int _gameNumber);
    virtual void resetGame();

    void setPlayerTurnCallback(touchgfx::GenericCallback<PieceColor>* callback);
    PieceColor getPlayerTurn();

protected:
    BoardState _boardState;
    BoardStateModel _boardStateModel;

    touchgfx::FadeAnimator<touchgfx::Image> Check;
    virtual void MovePiece(int from, int to);

private:
    void highlightPieceAndMoves(int position);
    void updateBoardColors();
    int isKingInCheck(PieceColor color);
    bool wouldMoveCauseCheck(int from, int to);
    bool hasLegalMoves(PieceColor color);
    bool hasCheckmate(PieceColor color);
    std::list<int> filterValidMoves(const std::list<int>& possibleMoves, int from);

    SquareRenderer _squareRenderer;
    BoardRenderer _boardRenderer;
    PieceSelector _pieceSelector;
    GameStateSerializer _gameStateSerializer;

    std::string _savedGames[3];

    touchgfx::GenericCallback<PieceColor>* playerTurnCallback; // Player turn callback
};

#endif /* BOARD_HPP */
