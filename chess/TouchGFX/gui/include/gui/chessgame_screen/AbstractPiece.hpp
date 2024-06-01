#pragma once

#include <gui/chessgame_screen/ChessEnums.hpp>
#include <list>
#include <memory>

#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>

using namespace touchgfx;

class AbstractPiece {
protected:
    PieceColor color; // Indicates whether the piece is white or black
    PieceType type; // Symbol representing the piece on the board
    std::unique_ptr<ScalableImage> _image; // Image of the piece

public:
    virtual ~AbstractPiece() {};

    // All moves inside the board if no other piece is blocking the way
    virtual std::list<int> PotentialMoves(const AbstractPiece* board[64], const int myPosition) const = 0;

    // Moves that are possible to make, considering the board and other pieces
    virtual std::list<int> PossibleMoves(const AbstractPiece* board[64], const int myPosition) const = 0;

    virtual PieceColor GetColor() const {
        return color;
    }

    virtual PieceType GetType() const {
        return type;
    }

    virtual ScalableImage* GetImage() const {
        return _image.get();
    }

    void Move(int position) const
    {
        int x = (position % 8) * 34;
        int y = (position / 8) * 34;

        _image->setPosition(x, y, 33, 33);

        _image->invalidate();
    }
};
