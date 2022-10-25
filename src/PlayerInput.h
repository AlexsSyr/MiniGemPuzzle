#pragma once
#include "Miscs/Types.h"
#include <functional>

class Player;

using MouseButtonDownCallback = std::function<void(int32 posX, int32 posY)>;

class PlayerInput
{
public:

	void MouseButtonDown(int32 posX, int32 posY);
	void AddMouseButtonDownCallback(const MouseButtonDownCallback& callback);

private:
	Vector<MouseButtonDownCallback> mouseButtonDownCallbacks;
};