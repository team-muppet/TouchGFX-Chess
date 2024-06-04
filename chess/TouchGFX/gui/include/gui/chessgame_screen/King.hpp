#pragma once

#include "AbstractPiece.hpp"
#include <BitmapDatabase.hpp>

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

        return possibleMoves;
    }

	//int CastlingMove(const std::unique_ptr<AbstractPiece> board[64], const int myPosition) const {
	//	// Implementation for castling move of a KING
	//	// Check if the king has moved
	//	if (this->hasMoved) {
	//		return -1;
	//	}

	//	// Check if the king is in check
	//	if (isKingInCheck(this->color, const int myPosition) != -1) {
	//		return -1;
	//	}

	//	// Check if the rooks are in their initial positions
	//	int leftRookPosition = (this->color == PieceColor::WHITE) ? 56 : 0;
	//	int rightRookPosition = (this->color == PieceColor::WHITE) ? 63 : 7;

	//	if (board[leftRookPosition] == nullptr || board[leftRookPosition]->GetType() != PieceType::ROOK || board[leftRookPosition]->GetColor() != this->color || board[leftRookPosition]->HasMoved()) {
	//		return -1;
	//	}

	//	if (board[rightRookPosition] == nullptr || board[rightRookPosition]->GetType() != PieceType::ROOK || board[rightRookPosition]->GetColor() != this->color || board[rightRookPosition]->HasMoved()) {
	//		return -1;
	//	}

	//	// Check if the squares between the king and the rook are empty
	//	int leftRookSquare = (this->color == PieceColor::WHITE) ? 57 : 1;
	//	int rightRookSquare = (this->color == PieceColor::WHITE) ? 62 : 6;

	//	if (board[leftRookSquare] != nullptr || board[rightRookSquare] != nullptr) {
	//		return -1;
	//	}

	//	// Check if the squares are not under attack
	//	if (wouldMoveCauseCheck(myPosition, leftRookSquare, board) || wouldMoveCauseCheck(myPosition, rightRookSquare, board)) {
	//		return -1;
	//	}

	//	// Return the position of the rook for castling
	//	return (myPosition == leftRookSquare) ? leftRookPosition : rightRookPosition;
	//}

	//bool isKingInCheck(PieceColor color, const int myPosition) const {
	//	// Implementation for checking if the king is in check
	//	int kingPosition = myPosition;
	//	int directions[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };

	//	for (int dir : directions) {
	//		int pos = kingPosition;
	//		while (true) {
	//			pos += dir;
	//			// Check if the move is within bounds and on the correct diagonal
	//			if (pos < 0 || pos >= 64 ||
	//				((pos - dir) % 8 == 0 && (dir == -9 || dir == -1 || dir == 7)) ||
	//				((pos - dir) % 8 == 7 && (dir == -7 || dir == 1 || dir == 9))) {
	//				break;
	//			}
	//			// Check if the king is in check by a queen or a bishop
	//			if (board[pos] != nullptr && (board[pos]->GetType() == PieceType::QUEEN || board[pos]->GetType() == PieceType::BISHOP) && board[pos]->GetColor() != color) {
	//				return pos;
	//			}
	//			// Stop if there is a piece in the way
	//			if (board[pos] != nullptr) {
	//				break;
	//			}
	//		}
	//	}

	//	return -1;
	//}

};
