#pragma once
#include "Miscs/Types.h"

enum class GameFieldCellType
{
	FREE,
	BLOCK,
	GEM_1,
	GEM_2,
	GEM_3,
	MAX_VALUE
};

struct GameFieldCellDesc
{
	uint32 x = 0;
	uint32 y = 0;
	GameFieldCellType type = GameFieldCellType::FREE;
};

class GameField
{
public:

	GameField() = default;
	GameField(const Vector<GameFieldCellDesc>& cells);

private:
	GameFieldCellType field[5][5] = { GameFieldCellType::FREE };
};