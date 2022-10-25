#pragma once
#include "Miscs/Types.h"

class GameField;
class PlayerInput;

class Player
{
public:

	void Initialize(PlayerInput& playerInput, GameField& gameField);

private:
	GameField* gameField = nullptr;
	PlayerInput* playerInput = nullptr;

	void OnMouseButtonDown(int32 posX, int32 posY);
};