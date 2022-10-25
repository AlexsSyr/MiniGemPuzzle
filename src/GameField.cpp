#include "GameField.h"

GameField::GameField(const Vector<GameFieldCellDesc>& cells)
{
	for (auto [x,y, cellType] : cells)
	{
		field[x][y] = cellType;
	}
}

uint32 GameField::GetSize() const
{
	return FIELD_SIZE;
}

uint32 GameField::GetCellSize() const
{
	return gridCellSize;
}

void GameField::UpdateGrid(uint32 canvasW, uint32 canvasH)
{
	gridCellSize = std::min(canvasW, canvasH) * 0.15;
	const uint32 fieldSize = FIELD_SIZE;
	const uint32 gridPosX = (canvasW - gridCellSize * fieldSize) / 2;
	const uint32 gridPosY = (canvasH - gridCellSize * fieldSize) / 2;

	for (uint32 i = 0; i < fieldSize; ++i)
		for (uint32 j = 0; j < fieldSize; ++j)
		{
			grid[i][j].x = gridPosX + j * gridCellSize;
			grid[i][j].y = gridPosY + i * gridCellSize;
		}
}

GameFieldCellType GameField::GetCellType(uint32 posX, uint32 posY) const
{
	return field[posX][posY];
}

GameFieldCellCanvasPos GameField::GetCellCanvasPos(uint32 posX, uint32 posY) const
{
	return grid[posX][posY];
}
