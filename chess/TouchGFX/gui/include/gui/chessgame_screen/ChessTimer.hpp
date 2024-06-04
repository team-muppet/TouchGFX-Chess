#ifndef CHESSTIMER_HPP
#define CHESSTIMER_HPP

#include <gui/chessgame_screen/ChessEnums.hpp>
#include <chrono>
#include <touchgfx/Callback.hpp>

class ChessTimer
{
public:
    ChessTimer(PieceColor currentPlayer);
    void changePlayer();
    void resume();
    void pause();
    void tick();
    void reset();

    void setWhiteTimeUpdateCallback(touchgfx::GenericCallback<uint8_t, uint8_t>* callback);
    void setBlackTimeUpdateCallback(touchgfx::GenericCallback<uint8_t, uint8_t>* callback);

private:
    PieceColor _currentPlayer;
    std::chrono::steady_clock::time_point _lastTick;
    std::chrono::duration<double> _whitePlayerTime;
    std::chrono::duration<double> _blackPlayerTime;
    bool _isRunning;

    touchgfx::GenericCallback<uint8_t, uint8_t>* _whiteTimeUpdateCallback;
    touchgfx::GenericCallback<uint8_t, uint8_t>* _blackTimeUpdateCallback;
};

#endif /* CHESSTIMER_HPP */
