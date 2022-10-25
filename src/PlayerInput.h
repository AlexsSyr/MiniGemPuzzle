#pragma once
#include "Miscs/Types.h"

typedef void (*MouseButtonDownCallback) (int32 posX, int32 posY);

class PlayerInput
{
public:

	void MouseButtonDown(int32 posX, int32 posY);
	void AddMouseButtonDownCallback(MouseButtonDownCallback callback);

private:
	Vector<MouseButtonDownCallback> mouseButtonDownCallbacks;
};