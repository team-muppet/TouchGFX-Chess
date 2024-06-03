#include <gui/chessgame_screen/ChessGameView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>

ChessGameView::ChessGameView() : imageClickedCallback(this, &ChessGameView::imageClickedHandler)
{}

void ChessGameView::setupScreen()
{
    _chessboard.setXY(0, 0);
    add(_chessboard);
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
    if (&i != &ChessBoard)
    {
        return;
    }

    if (e.getType() != touchgfx::ClickEvent::ClickEventType::RELEASED)
    {
        return;
    }

    //Debug section
    Unicode::snprintf(locationTextBoxBuffer, LOCATIONTEXTBOX_SIZE, "%c%d", e.getX() / 34 + 65, 8 - e.getY() / 34);
    locationTextBox.invalidate();
    locationTextBox.invalidateContent();

    if (e.getX() < 272)
    {
        int position = e.getX() / 34 + (e.getY() / 34) * 8;
        _chessboard.handleClickEvent(position);
        // board.HandleClick
    }
    else
    {
        // Menu clicks
    }
}
