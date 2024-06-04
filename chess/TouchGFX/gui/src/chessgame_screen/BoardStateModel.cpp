#include <gui/chessgame_screen/BoardStateModel.hpp>

BoardStateModel::BoardStateModel()
    : _currentPlayer(PieceColor::WHITE) {
    for (auto& piece : _board) {
        piece.reset();
    }
}

std::array<std::unique_ptr<AbstractPiece>, 64>& BoardStateModel::getBoard() {
    return _board;
}

void BoardStateModel::setBoard(std::array<std::unique_ptr<AbstractPiece>, 64>&& board) {
    _board = std::move(board);
}

PieceColor BoardStateModel::getCurrentPlayer() const {
    return _currentPlayer;
}

void BoardStateModel::setCurrentPlayer(PieceColor color) {
    _currentPlayer = color;
}
