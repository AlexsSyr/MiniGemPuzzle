#pragma once
#include "Miscs/Types.h"
#include <functional>

class GameField;
class PlayerInput;

class Player
{
public:

	void Initialize(PlayerInput& playerInput, GameField& gameField, const std::function<void()> victoryCallback);

private:
	GameField* gameField = nullptr;
	PlayerInput* playerInput = nullptr;
	std::function<void()> victoryCallback;

	void OnMouseButtonDown(int32 posX, int32 posY);
	int32 ComputeClickedCellIndex(int32 posX, int32 posY) const;
};