#include "Player.h"
#include "PlayerInput.h"
#include "GameField.h"

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
//	const auto [x, y] = gameField->GetCellPosByMousePos(posX, posY);
}
