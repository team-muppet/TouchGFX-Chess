#include <gui/chessgame_screen/ChessGameView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>

ChessGameView::ChessGameView()
    : screenClickedCallback(this, &ChessGameView::screenClickedHandler),
    buttonClickedCallback(this, &ChessGameView::buttonCallbackHandler),
    _chessTimer(PieceColor::WHITE),
    whiteTimeUpdateCallback(this, &ChessGameView::whiteTimerUpdated),
    blackTimeUpdateCallback(this, &ChessGameView::blackTimerUpdated),
    playerTurnCallback(this, &ChessGameView::updatePlayerTurn)
{}

void ChessGameView::setupScreen()
{
    _chessboard.setXY(0, 0);
    add(_chessboard);
    ChessGameViewBase::setupScreen();

    Background.setClickAction(screenClickedCallback);
    SaveButton.setClickAction(buttonClickedCallback);
    NewGameButton.setClickAction(buttonClickedCallback);
    LoadButton.setClickAction(buttonClickedCallback);

    // Initialize timers
    _chessTimer.setWhiteTimeUpdateCallback(&whiteTimeUpdateCallback);
    _chessTimer.setBlackTimeUpdateCallback(&blackTimeUpdateCallback);
    _chessTimer.resume(); // Start the timer

    // Set player turn callback
    _chessboard.setPlayerTurnCallback(&playerTurnCallback);
}

void ChessGameView::tearDownScreen()
{
    ChessGameViewBase::tearDownScreen();
    _chessTimer.pause(); // Pause the timer
}

void ChessGameView::handleTickEvent()
{
    _chessTimer.tick();
}

void ChessGameView::screenClickedHandler(const Box& i, const ClickEvent& e)
{
    if (&i != &Background)
    {
        return;
    }

    if (e.getType() != touchgfx::ClickEvent::ClickEventType::RELEASED)
    {
        return;
    }

    // Debug section
    Unicode::snprintf(locationTextBoxBuffer, LOCATIONTEXTBOX_SIZE, "%c%d", e.getX() / 34 + 65, 8 - e.getY() / 34);
    locationTextBox.invalidate();
    locationTextBox.invalidateContent();

    if (e.getX() < 272)
    {
        int position = e.getX() / 34 + (e.getY() / 34) * 8;
        _chessboard.handleClickEvent(position);
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
        _chessTimer.reset();
        _chessTimer.resume();

        // Set player turn callback again after resetting the game
        _chessboard.setPlayerTurnCallback(&playerTurnCallback);
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

void ChessGameView::setWhiteTimer(uint8_t minutes, uint8_t seconds)
{
    WhiteClock.setTime24Hour(minutes, seconds, 0);
}

void ChessGameView::setBlackTimer(uint8_t minutes, uint8_t seconds)
{
    BlackClock.setTime24Hour(minutes, seconds, 0);
}

void ChessGameView::whiteTimerUpdated(uint8_t minutes, uint8_t seconds)
{
    setWhiteTimer(minutes, seconds);
}

void ChessGameView::blackTimerUpdated(uint8_t minutes, uint8_t seconds)
{
    setBlackTimer(minutes, seconds);
}

void ChessGameView::updatePlayerTurn(PieceColor color)
{
    if (color == PieceColor::WHITE)
    {
        PlayerTurn.setColor(Color::getColorFromRGB(255, 255, 255)); // White color
    }
    else
    {
        PlayerTurn.setColor(Color::getColorFromRGB(0, 0, 0)); // Black color
    }
    PlayerTurn.invalidate(); // Redraw the PlayerTurn box

    _chessTimer.changePlayer();
}
