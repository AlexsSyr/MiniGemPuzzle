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

struct GameFieldCellCanvasPos
{
	uint32 x = 0;
	uint32 y = 0;
};

#define FIELD_SIZE 5

class GameField
{
public:

	GameField() = default;
	GameField(const Vector<GameFieldCellDesc>& cells);

	uint32 GetSize() const;
	uint32 GetCellSize() const;

	void UpdateGrid(uint32 canvasW, uint32 canvasH);

	GameFieldCellType GetCellType(uint32 posX, uint32 posY) const;
	GameFieldCellCanvasPos GetCellCanvasPos(uint32 posX, uint32 posY) const;

private:
	GameFieldCellType field[FIELD_SIZE][FIELD_SIZE] = { GameFieldCellType::FREE };
	GameFieldCellCanvasPos grid[FIELD_SIZE][FIELD_SIZE] = { };
	uint32 gridCellSize = 0;
};