#include "Player.h"
#include "PlayerInput.h"
#include "GameField.h"
#include <math.h>

void Player::Initialize(PlayerInput& playerInput, GameField& gameField)
{
	this->playerInput = &playerInput;
	this->gameField = &gameField;

	playerInput.AddMouseButtonDownCallback(
		[this](int32 posX, int32 posY)
		{
			OnMouseButtonDown(posX, posY);
		});
}

void Player::OnMouseButtonDown(int32 posX, int32 posY)
{
	const int32 fieldSize = gameField->GetSize();
	const int32 clickedCellIndex = ComputeClickedCellIndex(posX, posY);
	const int32 currentSelectedCellIndex = gameField->GetSelectedCellIndex();
	const GameFieldCellType clickedCellType = gameField->GetCellType(clickedCellIndex);

	if (clickedCellType == GameFieldCellType::BLOCK 
		|| clickedCellType == GameFieldCellType::FREE && currentSelectedCellIndex == NO_SELECTED_CELL)
	{
		gameField->SetSelectedCellIndex(NO_SELECTED_CELL);
		return;
	}

	if (currentSelectedCellIndex == NO_SELECTED_CELL)
	{
		gameField->SetSelectedCellIndex(clickedCellIndex);
	}
	else
	{
		int32 xDistance = std::abs(clickedCellIndex / fieldSize - currentSelectedCellIndex / fieldSize);
		int32 yDIstance = std::abs(clickedCellIndex % fieldSize - currentSelectedCellIndex % fieldSize);
		int32 distance = xDistance + yDIstance;

		const bool neighbor = distance < 2 && distance > 0;

		if (neighbor && gameField->GetCellType(clickedCellIndex) == GameFieldCellType::FREE)
		{
			gameField->SwapCells(clickedCellIndex, currentSelectedCellIndex);
			gameField->SetSelectedCellIndex(NO_SELECTED_CELL);
		}
		else
		{
			gameField->SetSelectedCellIndex(clickedCellIndex);
		}
	}
}

int32 Player::ComputeClickedCellIndex(int32 posX, int32 posY) const
{
	const uint32 fieldSize = gameField->GetSize();
	const uint32 cellSize = gameField->GetCellSize();
	const uint32 halfCellSize = cellSize / 2;

	GameFieldCellCanvasPos canvasPos = { };
	for (uint32 i = 0; i < fieldSize; ++i)
		for (uint32 j = 0; j < fieldSize; ++j)
		{
			canvasPos = gameField->GetCellCanvas—enteredPos(i, j);

			if (std::abs(canvasPos.x - posX) <= halfCellSize && std::abs(canvasPos.y - posY) <= halfCellSize)
			{
				return i * fieldSize + j;
			}
		}

	return NO_SELECTED_CELL;
}
