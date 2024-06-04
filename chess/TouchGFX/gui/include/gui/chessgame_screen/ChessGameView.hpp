#ifndef CHESSGAMEVIEW_HPP
#define CHESSGAMEVIEW_HPP

#include <gui_generated/chessgame_screen/ChessGameViewBase.hpp>
#include <gui/chessgame_screen/ChessGamePresenter.hpp>
#include <gui/chessgame_screen/Board.hpp>

class ChessGameView : public ChessGameViewBase
{
public:
    ChessGameView();
    virtual ~ChessGameView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Declaring callback handler for Box
    void screenClickedHandler(const Box& i, const ClickEvent& e);
    void buttonCallbackHandler(const ButtonWithIcon& src, const ClickEvent& e);

protected:
    // Declaring callback type of ScalableImage and clickEvent
    Callback<ChessGameView, const Box&, const ClickEvent&> screenClickedCallback;
	Callback<ChessGameView, const ButtonWithIcon&, const ClickEvent&> buttonClickedCallback;
    ScalableImage _testpawn;
    //Add Board to view
    Board _chessboard;
};

#endif // CHESSGAMEVIEW_HPP
