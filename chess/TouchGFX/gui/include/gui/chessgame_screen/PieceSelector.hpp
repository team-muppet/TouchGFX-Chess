#pragma once

#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/containers/Container.hpp>
#include <list>
#include <vector>
#include <memory>

using namespace touchgfx;

class PieceSelector {
public:
    PieceSelector(touchgfx::Container* container);
    ~PieceSelector();
    void selectPiece(int position, const std::list<int>& possibleMoves);
    void deselectPiece();
    bool isVisible() const;

private:
    Box _pieceSelector;
    std::vector<std::unique_ptr<Box>> _moveMarkers;
    Container* _container;

    void clearMoveMarkers();
    void displayMoveMarkers(const std::list<int>& positions);
};