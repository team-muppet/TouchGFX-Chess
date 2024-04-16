#include <gui/chessgame_screen/ChessGameView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

ChessGameView::ChessGameView() : imageClickedCallback(this, &ChessGameView::imageClickedHandler)
{}

void ChessGameView::setupScreen()
{
    ChessGameViewBase::setupScreen();

    Background.setAlpha(100);
    ChessBoard.setClickAction(imageClickedCallback);
}

void ChessGameView::tearDownScreen()
{
    ChessGameViewBase::tearDownScreen();
}

void ChessGameView::imageClickedHandler(const ScalableImage& i, const ClickEvent& e)
{
    if (&i == &ChessBoard)
    {
        Unicode::snprintf(locationTextBoxBuffer, LOCATIONTEXTBOX_SIZE, "%c%d", e.getX()/34+65, 8-e.getY()/34);
        locationTextBox.invalidate();
        locationTextBox.invalidateContent();
    }
}
