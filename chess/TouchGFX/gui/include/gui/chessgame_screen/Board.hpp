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

#include <gui/chessgame_screen/AbstractPiece.hpp>
#include <gui/chessgame_screen/ChessEnums.hpp>
#include <gui/chessgame_screen/PieceSelector.hpp>
#include <gui/chessgame_screen/SquareRenderer.hpp>
#include <gui/chessgame_screen/BoardRenderer.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>
#include <BitmapDatabase.hpp>

using namespace touchgfx;

class Board : public Container
{
public:
    Board();
    virtual ~Board();
    virtual void setupBoard();
    virtual void handleClickEvent(int position);
    virtual void serializeBoardState();

protected:
    std::array<std::unique_ptr<AbstractPiece>, 64> _board;
    PieceColor _currentPlayer;
    PieceSelector _pieceSelector;
    int _selectedPiecePosition; // Track the currently selected piece position

    touchgfx::FadeAnimator< touchgfx::Image > Check;

    virtual void MovePiece(int from, int to);

    void startFadeOutAnimation();
    void onInitialFadeAnimationEnded(const FadeAnimator<Image>& animator);
    void onFadeOutAnimationEnded(const FadeAnimator<Image>& animator);
    Callback<Board, const FadeAnimator<Image>&> initialFadeAnimationCallback;
    Callback<Board, const FadeAnimator<Image>&> fadeOutAnimationCallback;

private:
    void highlightPieceAndMoves(int position);
    void updateBoardColors(); // New method to update board colors
    bool isKingInCheck(PieceColor color); // New method to check if the king is in check

    // New variables for tracking the last move
    int _lastMoveFrom; // Track the starting position of the last move
    int _lastMoveTo;   // Track the ending position of the last move

    // Track king positions
    int _whiteKingPosition;
    int _blackKingPosition;

    SquareRenderer _squareRenderer;
    BoardRenderer _boardRenderer;
};

#endif /* BOARD_HPP */
