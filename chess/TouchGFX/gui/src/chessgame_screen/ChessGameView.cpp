#include <gui/chessgame_screen/ChessGameView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>

ChessGameView::ChessGameView() : buttonClickedCallback(this, &ChessGameView::buttonCallbackHandler), imageClickedCallback(this, &ChessGameView::imageClickedHandler)
{}

void ChessGameView::setupScreen()
{
    _chessboard.setXY(0, 0);
    add(_chessboard);
    ChessGameViewBase::setupScreen();

    
    Background.setAlpha(100);
    ChessBoard.setClickAction(imageClickedCallback);
	SaveButton.setClickAction(buttonClickedCallback);
	NewGameButton.setClickAction(buttonClickedCallback);
	LoadButton.setClickAction(buttonClickedCallback);
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

void ChessGameView::buttonCallbackHandler(const ButtonWithIcon& src, const ClickEvent& e)
{
    
    if (&src == &NewGameButton)
    {
        _chessboard.resetGame();
        _chessboard.setupBoard();
    }
    else if (&src == &SaveButton)
    {
        _chessboard.saveGame(0);
    }
    else if (&src == &LoadButton)
    {
        _chessboard.loadGame(0);
    }
}
