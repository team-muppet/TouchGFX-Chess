#pragma once

#include "AbstractPiece.hpp"
#include <BitmapDatabase.hpp>
#include <list>
#include <algorithm>

class King : public AbstractPiece {
public:
    King(PieceColor color, int position, Container* container)
        : AbstractPiece(color, PieceType::KING, Bitmap(color == PieceColor::WHITE ? BITMAP_WHITEKING_ID : BITMAP_BLACKKING_ID), container)
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

        // Add castling moves
        std::list<int> castlingMoves = CastlingMove(board, myPosition);
        possibleMoves.insert(possibleMoves.end(), castlingMoves.begin(), castlingMoves.end());

        return possibleMoves;
    }

    std::list<int> CastlingMove(const std::unique_ptr<AbstractPiece> board[64], const int myPosition) const {
        std::list<int> castlingPositions;

        // Check if the king has moved
        if (this->hasMoved) {
            return castlingPositions;
        }

        // Determine the rook positions and castling paths
        int kingInitialPosition = (this->color == PieceColor::WHITE) ? 60 : 4;
        int leftRookPosition = (this->color == PieceColor::WHITE) ? 56 : 0;
        int rightRookPosition = (this->color == PieceColor::WHITE) ? 63 : 7;

        int leftCastlingPath[] = { kingInitialPosition - 1, kingInitialPosition - 2, kingInitialPosition - 3 };
        int rightCastlingPath[] = { kingInitialPosition + 1, kingInitialPosition + 2 };

        // Check left rook and left castling path
        if (board[leftRookPosition] != nullptr && board[leftRookPosition]->GetType() == PieceType::ROOK &&
            board[leftRookPosition]->GetColor() == this->color && !board[leftRookPosition]->HasMoved()) {

            bool pathClear = true;
            for (int i = 0; i < 3; ++i) {
                if (board[leftCastlingPath[i]] != nullptr || wouldMoveCauseCheck(myPosition, leftCastlingPath[i], board)) {
                    pathClear = false;
                    break;
                }
            }
            if (pathClear && !wouldMoveCauseCheck(myPosition, kingInitialPosition - 2, board)) {
                castlingPositions.push_back(kingInitialPosition - 2);
            }
        }

        // Check right rook and right castling path
        if (board[rightRookPosition] != nullptr && board[rightRookPosition]->GetType() == PieceType::ROOK &&
            board[rightRookPosition]->GetColor() == this->color && !board[rightRookPosition]->HasMoved()) {

            bool pathClear = true;
            for (int i = 0; i < 2; ++i) {
                if (board[rightCastlingPath[i]] != nullptr || wouldMoveCauseCheck(myPosition, rightCastlingPath[i], board)) {
                    pathClear = false;
                    break;
                }
            }
            if (pathClear && !wouldMoveCauseCheck(myPosition, kingInitialPosition + 2, board)) {
                castlingPositions.push_back(kingInitialPosition + 2);
            }
        }

        return castlingPositions;
    }

    //bool isKingInCheck(PieceColor color, const int kingPosition, const std::unique_ptr<AbstractPiece> board[64]) const {
    //   for (int i = 0; i < 64; ++i) {
    //        if (board[i] != nullptr) {
    //            if (board[i]->GetColor() != color) {
    //                //std::list<int> possibleMoves = board[i]->PossibleMoves(board, i);
    //                /*if (std::find(possibleMoves.begin(), possibleMoves.end(), kingPosition) != possibleMoves.end()) {
    //                    return true;
    //                }*/
    //            }
    //        }
    //    }
    //    return false;
    //}

    bool wouldMoveCauseCheck(int kingPosition, int targetPosition, const std::unique_ptr<AbstractPiece> board[64]) const {
        //// Create a copy of the board
        //std::unique_ptr<AbstractPiece> tempBoard[64];
        //for (int i = 0; i < 64; ++i) {
        //    if (board[i] != nullptr) {
        //        tempBoard[i] = board[i]->clone();
        //    }
        //    else {
        //        tempBoard[i] = nullptr;
        //    }
        //}

        //// Simulate the move
        //tempBoard[targetPosition] = std::move(tempBoard[kingPosition]);
        //tempBoard[kingPosition] = nullptr;

        //// Check if the king would be in check after the move
        //bool inCheck = isKingInCheck(tempBoard[targetPosition]->GetColor(), targetPosition, tempBoard);

        //// Cleanup temporary board
        //for (int i = 0; i < 64; ++i) {
        //    if (tempBoard[i] != nullptr) {
        //        tempBoard[i].reset();
        //    }
        //}

        return false;
    }
};
