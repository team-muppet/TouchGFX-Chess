#include <gui/chessgame_screen/PieceSelector.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/containers/Container.hpp>
#include <vector>
#include <list>
#include <algorithm>

#define MARKER_SIZE 8
#define CAPTURE_MARKER_SIZE 28
#define MARKER_OFFSET (34 - MARKER_SIZE) / 2
#define CAPTURE_MARKER_OFFSET (34 - CAPTURE_MARKER_SIZE) / 2

PieceSelector::PieceSelector(touchgfx::Container* container)
    : _pieceSelector(34, 34, touchgfx::Color::getColorFromRGB(174, 198, 207), 200),
    _container(container),
    _moveMarkers(64), // Initialize vector to hold 64 Box markers
    _captureMarkers(64) // Initialize vector to hold 64 capture markers
{
    _pieceSelector.setVisible(false);
    container->add(_pieceSelector);

    // Initialize and position the move markers
    for (int i = 0; i < 64; i++) {
        _moveMarkers[i] = Box(MARKER_SIZE, MARKER_SIZE, touchgfx::Color::getColorFromRGB(0, 0, 0), 100);
        _moveMarkers[i].setVisible(false);
        _moveMarkers[i].moveTo((i % 8) * 34 + MARKER_OFFSET, (i / 8) * 34 + MARKER_OFFSET);
        container->add(_moveMarkers[i]);

        _captureMarkers[i] = Box(CAPTURE_MARKER_SIZE, CAPTURE_MARKER_SIZE, touchgfx::Color::getColorFromRGB(255, 0, 0), 100);
        _captureMarkers[i].setVisible(false);
        _captureMarkers[i].moveTo((i % 8) * 34 + CAPTURE_MARKER_OFFSET, (i / 8) * 34 + CAPTURE_MARKER_OFFSET);
        container->add(_captureMarkers[i]);
    }
}

void PieceSelector::selectPiece(int position, const std::list<int>& possibleMoves, const std::list<int>& captureMoves) {
    _pieceSelector.moveTo((position % 8) * 34, (position / 8) * 34);
    _pieceSelector.setVisible(true);
    _pieceSelector.invalidate();

    clearMoveMarkers();
    displayMoveMarkers(possibleMoves, captureMoves);
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
        marker.setVisible(false);
    }
    for (auto& marker : _captureMarkers) {
        marker.setVisible(false);
    }
    _possibleMoves.clear();
    _captureMoves.clear();
    _container->invalidate(); // Invalidate the container once after hiding all markers
}

void PieceSelector::displayMoveMarkers(const std::list<int>& positions, const std::list<int>& captures) {
    for (int pos : positions) {
        if (pos < 0 || pos >= 64) {
            continue; // Safety check to ensure valid positions
        }
        auto& marker = _moveMarkers[pos];
        marker.setVisible(true);
        _possibleMoves.push_back(pos);
    }
    for (int pos : captures) {
        if (pos < 0 || pos >= 64) {
            continue; // Safety check to ensure valid positions
        }
        auto& marker = _captureMarkers[pos];
        marker.setVisible(true);
        _captureMoves.push_back(pos);
    }
    _container->invalidate(); // Invalidate the container once after showing all markers
}

bool PieceSelector::isPossibleMove(int position) const {
    return std::find(_possibleMoves.begin(), _possibleMoves.end(), position) != _possibleMoves.end() ||
        std::find(_captureMoves.begin(), _captureMoves.end(), position) != _captureMoves.end();
}

PieceSelector::~PieceSelector() {
    clearMoveMarkers();
}
