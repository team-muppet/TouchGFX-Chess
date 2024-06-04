#include "gui/common/GameStateSerializer.hpp"

#include <rapidjson.h>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include <string>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "filereadstream.h"
#include "error/en.h"
#include <cstdio>
#include <gui/chessgame_screen/Pawn.hpp>
#include <gui/chessgame_screen/Rook.hpp>
#include <gui/chessgame_screen/Knight.hpp>
#include <gui/chessgame_screen/Bishop.hpp>
#include <gui/chessgame_screen/Queen.hpp>
#include <gui/chessgame_screen/King.hpp>

GameStateSerializer::GameStateSerializer()
{
}

std::string GameStateSerializer::SerializeGameState(std::array<std::unique_ptr<AbstractPiece>, 64>& _board, PieceColor _currentPlayer)
{
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    // Serialize the board
    rapidjson::Value boardArray(rapidjson::kArrayType);
    for (const auto& piece : _board) {
        if (piece) {
            rapidjson::Value pieceObject(rapidjson::kObjectType);
            pieceObject.AddMember("type", static_cast<int>(piece->GetType()), allocator);
            pieceObject.AddMember("color", static_cast<int>(piece->GetColor()), allocator);
            boardArray.PushBack(pieceObject, allocator);
        }
        else {
            boardArray.PushBack(rapidjson::Value(rapidjson::kNullType), allocator);
        }
    }
    document.AddMember("board", boardArray, allocator);
    document.AddMember("currentPlayer", static_cast<int>(_currentPlayer), allocator);

    // Convert JSON document to string
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    int size = buffer.GetSize();

    std::string serializedBoard = buffer.GetString();
    std::string serializedBoards(serializedBoard, size);

	return std::string();
}


std::array<std::unique_ptr<AbstractPiece>, 64> GameStateSerializer::DeserializeBoardState(std::string serializedGameState, BoardRenderer& _boardRenderer)
{
    rapidjson::Document document;
    if (document.Parse(serializedGameState.c_str()).HasParseError()) {
        printf("Error(offset %u): %s\n",
            (unsigned)document.GetErrorOffset(),
            rapidjson::GetParseError_En(document.GetParseError()));
		return std::array<std::unique_ptr<AbstractPiece>, 64>();
    }

    std::array<std::unique_ptr<AbstractPiece>, 64> tempboard;

    if (document.HasMember("board") && document["board"].IsArray()) {
        const rapidjson::Value& boardArray = document["board"];
        for (rapidjson::SizeType i = 0; i < boardArray.Size(); ++i) {
            const rapidjson::Value& piece = boardArray[i];
            if (!piece.IsNull() && piece.IsObject()) {
                if (piece.HasMember("type") && piece["type"].IsInt() &&
                    piece.HasMember("color") && piece["color"].IsInt()) {
                    PieceType type = static_cast<PieceType>(piece["type"].GetInt());
                    PieceColor color = static_cast<PieceColor>(piece["color"].GetInt());

                    switch (type) {
                    case PieceType::PAWN:
                        tempboard[i] = std::make_unique<Pawn>(color, i, &_boardRenderer);
                        break;
                        // Add cases for other piece types (KING, QUEEN, etc.)
                        // Example:
                    case PieceType::KING:
                        tempboard[i] = std::make_unique<King>(color, i, &_boardRenderer);
                        break;
                    case PieceType::QUEEN:
                        tempboard[i] = std::make_unique<Queen>(color, i, &_boardRenderer);
                        break;
                    case PieceType::ROOK:
                        tempboard[i] = std::make_unique<Rook>(color, i, &_boardRenderer);
                        break;
                    case PieceType::BISHOP:
                        tempboard[i] = std::make_unique<Bishop>(color, i, &_boardRenderer);
                        break;
                    case PieceType::KNIGHT:
                        tempboard[i] = std::make_unique<Knight>(color, i, &_boardRenderer);
                        break;
                    default:
                        break;
                    }
                }
            }
            else {
                tempboard[i] = nullptr;
            }
        }
    }
        return tempboard;
}

PieceColor GameStateSerializer::DeserializeCurrentPlayer(std::string serializedGameState)
{
	rapidjson::Document document;
	PieceColor _currentPlayer;
	if (document.Parse(serializedGameState.c_str()).HasParseError()) {
		printf("Error(offset %u): %s\n",
			(unsigned)document.GetErrorOffset(),
			rapidjson::GetParseError_En(document.GetParseError()));
		return PieceColor();
	}

    if (document.HasMember("currentPlayer") && document["currentPlayer"].IsInt()) {
        _currentPlayer = static_cast<PieceColor>(document["currentPlayer"].GetInt());
    }

    return _currentPlayer;
}
