#pragma once

#include "AbstractPiece.hpp"

class Queen : public AbstractPiece {
public:
    Queen(PieceColor color, ScalableImage* image) {
        this->color = color;
        this->type = PieceType::QUEEN;
        this->_image = image;
    }

    std::list<int> PotentialMoves(const AbstractPiece* board[64], const int myPosition) override {
        // Implementation for potential moves of a QUEEN
        // Dummy implementation, replace with actual logic
        std::list<int> moves;
        // Example logic: add positions one step forward
        moves.push_back(myPosition + (color == PieceColor::WHITE ? 8 : -8));
        return moves;
    }

    std::list<int> PossibleMoves(AbstractPiece* board[64], const int myPosition) override {
        // Implementation for possible moves of a QUEEN
        // Dummy implementation, replace with actual logic
        std::list<int> moves;
        // Example logic: add positions one step forward if unoccupied
        if (board[myPosition + (color == PieceColor::WHITE ? 8 : -8)] == nullptr) {
            moves.push_back(myPosition + (color == PieceColor::WHITE ? 8 : -8));
        }
        return moves;
    }
};
