#ifndef CHESSGAMEVIEW_HPP
#define CHESSGAMEVIEW_HPP

#include <gui_generated/chessgame_screen/ChessGameViewBase.hpp>
#include <gui/chessgame_screen/ChessGamePresenter.hpp>
#include <gui/chessgame_screen/Board.hpp>
#include <gui/chessgame_screen/ChessTimer.hpp>
#include <touchgfx/Callback.hpp>

class ChessGameView : public ChessGameViewBase
{
public:
    ChessGameView();
    virtual ~ChessGameView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

    // Declaring callback handler for Box
    void screenClickedHandler(const Box& i, const ClickEvent& e);
    void buttonCallbackHandler(const ButtonWithIcon& src, const ClickEvent& e);

    // Timer set UI
    void setWhiteTimer(uint8_t minutes, uint8_t seconds);
    void setBlackTimer(uint8_t minutes, uint8_t seconds);

protected:
    // Declaring callback type of ScalableImage and clickEvent
    Callback<ChessGameView, const Box&, const ClickEvent&> screenClickedCallback;
    Callback<ChessGameView, const ButtonWithIcon&, const ClickEvent&> buttonClickedCallback;
    ScalableImage _testpawn;
    // Add Board to view
    Board _chessboard;
    ChessTimer _chessTimer;  // ChessTimer instance

    // TouchGFX callbacks for timer updates and player turn
    Callback<ChessGameView, uint8_t, uint8_t> whiteTimeUpdateCallback;
    Callback<ChessGameView, uint8_t, uint8_t> blackTimeUpdateCallback;
    Callback<ChessGameView, PieceColor> playerTurnCallback;

    void whiteTimerUpdated(uint8_t minutes, uint8_t seconds);
    void blackTimerUpdated(uint8_t minutes, uint8_t seconds);
    void updatePlayerTurn(PieceColor color);
};

#endif // CHESSGAMEVIEW_HPP
