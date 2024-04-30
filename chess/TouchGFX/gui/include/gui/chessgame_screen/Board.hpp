#ifndef BOARD_HPP
#define BOARD_HPP

#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ZoomAnimationImage.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <stdlib.h>

#include <gui/chessgame_screen/AbstractPiece.hpp>
#include <gui/chessgame_screen/ChessEnums.hpp>

using namespace touchgfx;

class Board : public Container
{
public:
	Board();

	virtual ~Board();

	virtual void setupBoard();

	virtual void handleClickEvent(int position);

protected:

	AbstractPiece* _board[64];

	PieceColor _currentPlayer;
	
};


#endif /* BOARD_HPP */