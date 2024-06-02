#ifndef BOARDRENDERER_HPP
#define BOARDRENDERER_HPP

#include <touchgfx/containers/Container.hpp>
#include <array>
#include <memory>

#include <gui/chessgame_screen/AbstractPiece.hpp>
#include <gui/chessgame_screen/ChessEnums.hpp>

using namespace touchgfx;

class BoardRenderer : public Container
{
public:
    BoardRenderer();
    void setupBoard(std::array<std::unique_ptr<AbstractPiece>, 64>& board);

private:
    void addPiece(std::unique_ptr<AbstractPiece> piece, int position, std::array<std::unique_ptr<AbstractPiece>, 64>& board);
};

#endif /* BOARDRENDERER_HPP */
