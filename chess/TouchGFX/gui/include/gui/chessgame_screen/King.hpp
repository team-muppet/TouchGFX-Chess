#pragma once

#include "AbstractPiece.hpp"
#include <BitmapDatabase.hpp>

class King : public AbstractPiece {
public:
    King(PieceColor color, int position, Container* container)
        : AbstractPiece(color, PieceType::KING, Bitmap(color == PieceColor::WHITE ? BITMAP_WHITEKING_ID : BITMAP_BLACKKING_ID))
    {
        container->add(*_image);
        Move(position);
    }

    std::list<int> PotentialMoves(const std::unique_ptr<AbstractPiece> board[64], const int myPosition) const override {
        // Implementation for potential moves of a KING
        std::list<int> moves;
        int directions[8] = { -9, -8, -7, -1, 1, 7, 8, 9 }; // King can move one square in any direction

        for (int dir : directions) {
            int pos = myPosition + dir;
            // Check if the move is within bounds
            if (pos >= 0 && pos < 64 && !((myPosition % 8 == 0 && (dir == -9 || dir == -1 || dir == 7)) || (myPosition % 8 == 7 && (dir == -7 || dir == 1 || dir == 9)))) {
                moves.push_back(pos);
            }
        }

        return moves;
    }

    std::list<int> PossibleMoves(const std::unique_ptr<AbstractPiece> board[64], const int myPosition) const override {
        // Implementation for possible moves of a KING
        std::list<int> potentialMoves = PotentialMoves(board, myPosition);
        std::list<int> possibleMoves;

        for (int move : potentialMoves) {
            // Add logic to check for valid moves considering other pieces
            if (board[move] == nullptr || board[move]->GetColor() != this->color) {
                possibleMoves.push_back(move);
            }
        }

        return possibleMoves;
    }
};
