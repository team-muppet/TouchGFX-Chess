#pragma once

#include "AbstractPiece.hpp"

class Pawn : public AbstractPiece {
public:
    Pawn(PieceColor color, ScalableImage*image) {
        this->color = color;
        this->type = PieceType::PAWN;
        this->_image = image;

        //_image->setVisible(true);
        //_image->invalidate();
        //add(this->_image); // Add the pieceImage to the board (the screen)
    }

    virtual ~Pawn() {}

    std::list<int> PotentialMoves(const AbstractPiece* board[64], const int myPosition) override {
        // Implementation for potential moves of a pawn
        // Dummy implementation, replace with actual logic
        std::list<int> moves;
        // Example logic: add positions one step forward
        moves.push_back(myPosition + (color == PieceColor::WHITE ? 8 : -8));
        return moves;
    }

    std::list<int> PossibleMoves(AbstractPiece* board[64], const int myPosition) override {
        // Implementation for possible moves of a pawn
        // Dummy implementation, replace with actual logic
        std::list<int> moves;
        // Example logic: add positions one step forward if unoccupied
        if (board[myPosition + (color == PieceColor::WHITE ? 8 : -8)] == nullptr) {
            moves.push_back(myPosition + (color == PieceColor::WHITE ? 8 : -8));
        }
        return moves;
    }
};
