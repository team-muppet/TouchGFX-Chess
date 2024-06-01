#pragma once

#include "AbstractPiece.hpp"
#include <BitmapDatabase.hpp>

class Pawn : public AbstractPiece {
public:
    Pawn(PieceColor color, int position, Container* container) {
        this->color = color;
        this->type = PieceType::PAWN;
        _image = std::make_unique<ScalableImage>();
        _image->setBitmap(Bitmap(color == PieceColor::WHITE ? BITMAP_WHITEPAWN_ID : BITMAP_BLACKPAWN_ID));
        container->add(*_image);
        Move(position);
    }

    std::list<int> PotentialMoves(const AbstractPiece* board[64], const int myPosition) const override {
        std::list<int> moves;
        int direction = (color == PieceColor::WHITE) ? -8 : 8; // White moves up, Black moves down

        // Move one step forward
        int pos = myPosition + direction;
        if (pos >= 0 && pos < 64) {
            moves.push_back(pos);
        }

        // Move two steps forward from starting position
        if ((color == PieceColor::WHITE && myPosition / 8 == 6) || (color == PieceColor::BLACK && myPosition / 8 == 1)) {
            pos = myPosition + 2 * direction;
            if (pos >= 0 && pos < 64) {
                moves.push_back(pos);
            }
        }

        // Capture diagonally
        int captureLeft = myPosition + direction - 1;
        int captureRight = myPosition + direction + 1;
        if (captureLeft >= 0 && captureLeft < 64 && myPosition % 8 != 0) {
            moves.push_back(captureLeft);
        }
        if (captureRight >= 0 && captureRight < 64 && myPosition % 8 != 7) {
            moves.push_back(captureRight);
        }

        return moves;
    }

    std::list<int> PossibleMoves(const AbstractPiece* board[64], const int myPosition) const override {
        std::list<int> potentialMoves = PotentialMoves(board, myPosition);
        std::list<int> possibleMoves;

        int direction = (color == PieceColor::WHITE) ? -8 : 8;

        for (int move : potentialMoves) {
            // Forward moves must be to empty squares
            if (move == myPosition + direction || move == myPosition + 2 * direction) {
                if (board[move] == nullptr) {
                    possibleMoves.push_back(move);
                }
                else {
                    break; // Blocked
                }
            }
            else {
                // Diagonal captures must be to squares occupied by an opponent's piece
                if (board[move] != nullptr && board[move]->GetColor() != this->color) {
                    possibleMoves.push_back(move);
                }
            }
        }

        return possibleMoves;
    }
};
