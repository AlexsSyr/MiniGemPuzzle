#include "PlayerInput.h"

void PlayerInput::MouseButtonDown(int32 posX, int32 posY)
{
	for (auto callback : mouseButtonDownCallbacks)
	{
		callback(posX, posY);
	}
}

void PlayerInput::AddMouseButtonDownCallback(const MouseButtonDownCallback& callback)
{
	mouseButtonDownCallbacks.push_back(callback);
}
