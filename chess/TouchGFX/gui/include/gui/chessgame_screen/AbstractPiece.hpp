#pragma once

#include <gui/chessgame_screen/ChessEnums.hpp>
#include <list>

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>

using namespace touchgfx;

class AbstractPiece {
protected:
    PieceColor color; // Indicates whether the piece is white or black
    PieceType type; // Symbol representing the piece on the board
    //ZoomAnimationImage* _image; // Image of the piece

public:
    virtual ~AbstractPiece() {};

    //All moves inside the board if no other piece is blocking the way
    virtual std::list<int> PotentialMoves(const AbstractPiece* board[64], const int myPosition) = 0;

    //Moves that are possible to make, considering the board and other pieces
    virtual std::list<int> PossibleMoves(AbstractPiece* board[64], const int myPosition) = 0;


    virtual PieceColor GetColor() const {
		return color;
	}
    
    virtual PieceType GetType() const {
		return type;
	}
    ScalableImage* _image;
    virtual ScalableImage GetImage() const {
        return *_image;
    }
};