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

GameFieldCellType GameField::GetCellType(uint32 posX, uint32 posY) const
{
	return field[posX][posY];
}
