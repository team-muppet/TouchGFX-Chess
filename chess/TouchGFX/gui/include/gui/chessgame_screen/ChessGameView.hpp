#ifndef CHESSGAMEVIEW_HPP
#define CHESSGAMEVIEW_HPP

#include <gui_generated/chessgame_screen/ChessGameViewBase.hpp>
#include <gui/chessgame_screen/ChessGamePresenter.hpp>

class ChessGameView : public ChessGameViewBase
{
public:
    ChessGameView();
    virtual ~ChessGameView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Declaring callback handler for Box
    void imageClickedHandler(const ScalableImage& i, const ClickEvent& e);
protected:
    // Declaring callback type of ScalableImage and clickEvent
    Callback<ChessGameView, const ScalableImage&, const ClickEvent&> imageClickedCallback;
};

#endif // CHESSGAMEVIEW_HPP
