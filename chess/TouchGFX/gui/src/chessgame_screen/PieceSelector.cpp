#include <gui/chessgame_screen/PieceSelector.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/containers/Container.hpp>
#include <vector>
#include <list>
#include <memory>

#define MARKER_SIZE 8
#define MARKER_OFFSET (34-MARKER_SIZE)/2

PieceSelector::PieceSelector(touchgfx::Container* container)
    : _pieceSelector(34, 34, touchgfx::Color::getColorFromRGB(174, 198, 207), 200),
    _container(container)
{
    _pieceSelector.setVisible(false);
    container->add(_pieceSelector);

    // Initialize a fixed number of move markers and position them
    for (int i = 0; i < 64; i++) { // Assuming a maximum of 64 markers for an 8x8 board
        auto marker = std::make_unique<touchgfx::Box>(MARKER_SIZE, MARKER_SIZE, touchgfx::Color::getColorFromRGB(0, 0, 0), 100);
        marker->setVisible(false);

        marker->moveTo((i % 8) * 34 + MARKER_OFFSET, (i / 8) * 34 + MARKER_OFFSET);

        container->add(*marker);
        _moveMarkers.push_back(std::move(marker));
    }
}

void PieceSelector::selectPiece(int position, const std::list<int>& possibleMoves) {
    _pieceSelector.moveTo((position % 8) * 34, (position / 8) * 34);
    _pieceSelector.setVisible(true);
    _pieceSelector.invalidate();

    clearMoveMarkers();
    displayMoveMarkers(possibleMoves);
}

void PieceSelector::deselectPiece() {
    _pieceSelector.setVisible(false);
    _pieceSelector.invalidate();
    clearMoveMarkers();
}

bool PieceSelector::isVisible() const {
    return _pieceSelector.isVisible();
}

void PieceSelector::clearMoveMarkers() {
    for (auto& marker : _moveMarkers) {
        marker->setVisible(false);
    }
    _container->invalidate(); // Invalidate the container once after hiding all markers
}

void PieceSelector::displayMoveMarkers(const std::list<int>& positions) {
    for (size_t pos : positions) {
        if (pos >= _moveMarkers.size()) {
            break; // Safety check to prevent accessing out of bounds
        }
        auto& marker = _moveMarkers[pos];
        marker->setVisible(true);
    }
    _container->invalidate(); // Invalidate the container once after showing all markers
}

PieceSelector::~PieceSelector() {
    clearMoveMarkers();
}