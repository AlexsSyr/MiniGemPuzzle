#include "GameField.h"

GameField::GameField(const Vector<GameFieldCellDesc>& cells)
{
	for (auto [x,y, cellType] : cells)
	{
		field[x][y] = cellType;
	}
}