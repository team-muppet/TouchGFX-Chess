#pragma once

#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/containers/Container.hpp>
#include <list>
#include <vector>

using namespace touchgfx;

class PieceSelector {
public:
    PieceSelector(touchgfx::Container* container);
    ~PieceSelector();
    void selectPiece(int position, const std::list<int>& possibleMoves, const std::list<int>& captureMoves);
    void deselectPiece();
    bool isVisible() const;
    bool isPossibleMove(int position) const; // Check if a position is a possible move

private:
    Box _pieceSelector;
    std::vector<Box> _moveMarkers;
    std::vector<Box> _captureMarkers; // New vector for capture markers
    std::list<int> _possibleMoves; // Store possible moves
    std::list<int> _captureMoves; // Store capture moves
    Container* _container;

    void clearMoveMarkers();
    void displayMoveMarkers(const std::list<int>& positions, const std::list<int>& captures);
};
