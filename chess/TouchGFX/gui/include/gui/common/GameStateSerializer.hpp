#ifndef GameStateSerializer_HPP
#define GameStateSerializer_HPP

#include <string>
#include <gui/chessgame_screen/ChessEnums.hpp>
#include <gui/chessgame_screen/BoardRenderer.hpp>

#include <stdlib.h>
#include <array>
#include <memory>
#include "gui/chessgame_screen/AbstractPiece.hpp"

class GameStateSerializer {
public:
	GameStateSerializer();

	// Serialize the game state to a string
	// @param gameState The game state to serialize
	// @return The serialized game state
	std::string SerializeGameState(std::array<std::unique_ptr<AbstractPiece>, 64>& board, PieceColor _currentPlayer);

	// Deserialize the game state from a string
	// @param serializedGameState The serialized game state
	// @return The deserialized game state
	std::array<std::unique_ptr<AbstractPiece>, 64> DeserializeBoardState(std::string serializedGameState, BoardRenderer& _boardRenderer);



	// deserialize the currentplayer to a enum
	// @param serializedGameState
	// @return enum of the currentplayer
	PieceColor DeserializeCurrentPlayer(std::string serializedGameState);



private:


};

#endif