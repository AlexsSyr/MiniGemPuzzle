#include "GameFieldLoader.h"
#include "../GameField.h"
#include "../Miscs/Exception.h"
#include <format>

GameField GameFieldLoader::LoadField(const Path& path)
{
	FileReader fileReader(path);

	if (!fileReader.is_open())
		Exception::Throw(std::format("Loading level \"{}\" failed! Can't open the file.", path.string()));

	uint32 cellCount = 0;

	fileReader >> cellCount;

	Vector<GameFieldCellDesc> cells(cellCount);

	uint32 cellTypeIndex = 0;
	for (auto& [x, y, type]: cells)
	{
		fileReader >> x >> y >> cellTypeIndex;

		if(cellTypeIndex >= static_cast<uint32>(GameFieldCellType::MAX_VALUE))
			Exception::Throw(std::format("Loading level \"{}\" failed! Invalid cell type index {}!", path.string(), cellTypeIndex));

		type = static_cast<GameFieldCellType>(cellTypeIndex);
	}

	return GameField(cells);
}
