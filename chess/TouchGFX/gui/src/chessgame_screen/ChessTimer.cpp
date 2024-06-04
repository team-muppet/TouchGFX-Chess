#include <gui/chessgame_screen/ChessTimer.hpp>

using namespace std;

ChessTimer::ChessTimer(PieceColor currentPlayer)
    : _currentPlayer(currentPlayer), _whitePlayerTime(0), _blackPlayerTime(0), _isRunning(false),
    _whiteTimeUpdateCallback(nullptr), _blackTimeUpdateCallback(nullptr)
{}

void ChessTimer::changePlayer()
{
    _currentPlayer = _currentPlayer == PieceColor::BLACK ? PieceColor::WHITE : PieceColor::BLACK; // Toggle player color.
}

void ChessTimer::resume()
{
    _isRunning = true;
    _lastTick = std::chrono::steady_clock::now();
}

void ChessTimer::pause()
{
    if (_isRunning)
    {
        tick();
        _isRunning = false;
    }
}

void ChessTimer::tick()
{
    if (_isRunning)
    {
        auto now = chrono::steady_clock::now();
        auto elapsed = now - _lastTick;
        _lastTick = now;

        if (_currentPlayer == PieceColor::WHITE)
        {
            _whitePlayerTime += elapsed;
            if (_whiteTimeUpdateCallback && _whiteTimeUpdateCallback->isValid())
            {
                auto totalSeconds = chrono::duration_cast<chrono::seconds>(_whitePlayerTime).count();
                _whiteTimeUpdateCallback->execute(static_cast<uint8_t>(totalSeconds / 60), static_cast<uint8_t>(totalSeconds % 60));
            }
        }
        else
        {
            _blackPlayerTime += elapsed;
            if (_blackTimeUpdateCallback && _blackTimeUpdateCallback->isValid())
            {
                auto totalSeconds = chrono::duration_cast<chrono::seconds>(_blackPlayerTime).count();
                _blackTimeUpdateCallback->execute(static_cast<uint8_t>(totalSeconds / 60), static_cast<uint8_t>(totalSeconds % 60));
            }
        }
    }
}

void ChessTimer::reset()
{
    _whitePlayerTime = std::chrono::duration<double>(0);
    _blackPlayerTime = std::chrono::duration<double>(0);
    _currentPlayer = PieceColor::WHITE;
    _isRunning = false;

    if (_whiteTimeUpdateCallback && _whiteTimeUpdateCallback->isValid())
    {
        _whiteTimeUpdateCallback->execute(0, 0);
    }
    if (_blackTimeUpdateCallback && _blackTimeUpdateCallback->isValid())
    {
        _blackTimeUpdateCallback->execute(0, 0);
    }
}

void ChessTimer::setWhiteTimeUpdateCallback(touchgfx::GenericCallback<uint8_t, uint8_t>* callback)
{
    _whiteTimeUpdateCallback = callback;
}

void ChessTimer::setBlackTimeUpdateCallback(touchgfx::GenericCallback<uint8_t, uint8_t>* callback)
{
    _blackTimeUpdateCallback = callback;
}
