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

using namespace touchgfx;

class Board : public Container
{
public:
    Board();
    virtual ~Board();
    virtual void setupBoard();
    virtual void handleClickEvent(int position);

protected:
    std::array<std::unique_ptr<AbstractPiece>, 64> _board;
    PieceColor _currentPlayer;
    PieceSelector _pieceSelector;

    virtual void MovePiece(int from, int to);
    void addPiece(std::unique_ptr<AbstractPiece> piece, int position);

private:
    void highlightPieceAndMoves(int position);
};

#endif /* BOARD_HPP */
