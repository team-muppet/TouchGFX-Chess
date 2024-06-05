#include <gui/chessgame_screen/ChessGameView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <BitmapDatabase.hpp>

ChessGameView::ChessGameView()
    : screenClickedCallback(this, &ChessGameView::screenClickedHandler),
    buttonClickedCallback(this, &ChessGameView::buttonCallbackHandler),
    gameModeButtonCallback(this, &ChessGameView::gameModeButtonCallbackHandler),
    _chessTimer(PieceColor::WHITE),
    whiteTimeUpdateCallback(this, &ChessGameView::whiteTimerUpdated),
    blackTimeUpdateCallback(this, &ChessGameView::blackTimerUpdated),
    playerTurnCallback(this, &ChessGameView::updatePlayerTurn),
    currentState(GameState::MENU),
    aiDepth(3) // Default depth
{}

void ChessGameView::setupScreen()
{
    _chessboard.setXY(0, 0);
    add(_chessboard);
    ChessGameViewBase::setupScreen();

    // Set menu buttons
    Background.setClickAction(screenClickedCallback);
    SaveButton.setClickAction(buttonClickedCallback);
    LoadButton.setClickAction(buttonClickedCallback);
    CloseButton.setClickAction(buttonClickedCallback);

    // Set game mode buttons
    SingleplayerButton.setClickAction(gameModeButtonCallback);
    MultiplayerButton.setClickAction(gameModeButtonCallback);

    // Initialize timers
    _chessTimer.setWhiteTimeUpdateCallback(&whiteTimeUpdateCallback);
    _chessTimer.setBlackTimeUpdateCallback(&blackTimeUpdateCallback);

    // Set player turn callback
    _chessboard.setPlayerTurnCallback(&playerTurnCallback);

    switchToMenu();
}

void ChessGameView::tearDownScreen()
{
    ChessGameViewBase::tearDownScreen();
    _chessTimer.pause(); // Pause the timer
}

void ChessGameView::handleTickEvent()
{
    if (currentState == GameState::GAME)
    {
        _chessTimer.tick();
    }
}

void ChessGameView::DifficultyValueChanged(int value)
{
    aiDepth = value;
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
    if (e.getType() == ClickEvent::ClickEventType::RELEASED)
    {
        if (&src == &CloseButton)
        {
            switchToMenu(); // Switch to menu on CloseGame button click
        }
        else if (&src == &LoadButton)
        {
            _chessboard.loadGame(0);
            switchToGame();
        }
        else if (&src == &SaveButton)
        {
            _chessboard.saveGame(0);
        }
    }
}

void ChessGameView::gameModeButtonCallbackHandler(const TextButtonStyle<IconButtonStyle<BoxWithBorderButtonStyle<ClickButtonTrigger>>>& src, const ClickEvent& e)
{
    if (e.getType() == ClickEvent::ClickEventType::RELEASED)
    {
        if (&src == &SingleplayerButton)
        {
            _chessboard.setAIMode(true); // Enable AI mode
            _chessboard.resetGame();
            _chessboard.setupBoard();
            _chessboard.getAI().setDepth(aiDepth); // Set AI depth based on slider
            _chessTimer.reset();
            _chessTimer.resume();
            switchToGame();
        }
        else if (&src == &MultiplayerButton)
        {
            _chessboard.setAIMode(false); // Disable AI mode
            _chessboard.resetGame();
            _chessboard.setupBoard();
            _chessTimer.reset();
            _chessTimer.resume();
            switchToGame();
        }
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

    _chessTimer.setPlayer(color);
}

void ChessGameView::switchToMenu()
{
    currentState = GameState::MENU;
    _chessboard.setVisible(false);
    _chessboard.invalidate();
    MainMenu.setVisible(true);
    MainMenu.invalidate();
}

void ChessGameView::switchToGame()
{
    currentState = GameState::GAME;
    _chessboard.setVisible(true);
    _chessboard.invalidate();
    MainMenu.setVisible(false);
    MainMenu.invalidate();
}

void ChessGameView::handleGameOver()
{
    switchToMenu();
}
