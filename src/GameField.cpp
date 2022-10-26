#include "GameField.h"

GameField::GameField(const Vector<GameFieldCellDesc>& cells)
{
	for (auto [x,y, cellType] : cells)
	{
		field[x][y] = cellType;
	}

	—ountGemMatch();
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
	const uint32 gridPosY = (canvasH - gridCellSize * fieldSize) * 0.8;

	for (uint32 i = 0; i < fieldSize; ++i)
		for (uint32 j = 0; j < fieldSize; ++j)
		{
			grid[i][j].x = gridPosX + j * (gridCellSize * 1.025);
			grid[i][j].y = gridPosY + i * (gridCellSize * 1.025);
		}
}

GameFieldCellType GameField::GetCellType(uint32 posX, uint32 posY) const
{
	return field[posX][posY];
}

GameFieldCellType GameField::GetCellType(uint32 cellIndex) const
{
	return field[cellIndex / FIELD_SIZE][cellIndex % FIELD_SIZE];
}

GameFieldCellCanvasPos GameField::GetCellCanvasPos(uint32 posX, uint32 posY) const
{
	return grid[posX][posY];
}

GameFieldCellCanvasPos GameField::GetCellCanvas—enteredPos(uint32 posX, uint32 posY) const
{
	GameFieldCellCanvasPos cellPos = grid[posX][posY];
	cellPos.x += gridCellSize / 2;
	cellPos.y += gridCellSize / 2;

	return cellPos;
}

void GameField::SetSelectedCellIndex(int32 index)
{
	selectedCellIndex = index;
}

int32 GameField::GetSelectedCellIndex() const
{
	return selectedCellIndex;
}

void GameField::SwapCells(int32 index1, int32 index2)
{
	std::swap(field[index1 / FIELD_SIZE][index1 % FIELD_SIZE], field[index2 / FIELD_SIZE][index2 % FIELD_SIZE]);
	—ountGemMatch();
}

void GameField::—ountGemMatch()
{
	for (uint32 i = 0; i < GEM_TYPE_COUNT; ++i)
	{
		gemMatchCount[i] = 0;
		for (uint32 j = 0; j < FIELD_SIZE; ++j)
		{
			if (field[j][i * 2] == static_cast<GameFieldCellType>(static_cast<uint32>(GameFieldCellType::GEM_1) + i))
				++gemMatchCount[i];
		}
	}
}

bool GameField::CheckVictory—ondition() const
{
	for (uint32 i = 0; i < GEM_TYPE_COUNT; ++i)
	{
		if (gemMatchCount[i] != FIELD_SIZE)
			return false;
	}

	return true;
}
