#pragma once
#include "../Miscs/Types.h"

class GameField;

class GameFieldLoader
{
public:
	static GameField LoadField(const Path& path) const;
};