#pragma once

#include <cstdint>
#include "Types.hpp"
#include "CellPosition.hpp"

namespace BotLifeSim
{
	class World;

	class CellInfo
	{
	public:
		CellInfo(World* _world, const CellPosition& _position, EnergyT _luminance);

		EnergyT GetLuminance()
		{ return _luminance; }

		CellInfo GetCellUp();

		CellInfo GetCellUpRight();

		CellInfo GetCellRight();

		CellInfo GetCellDownRight();

		CellInfo GetCellDown();

		CellInfo GetCellDownLeft();

		CellInfo GetCellLeft();

		CellInfo GetCellLeftUp();

	private:
		World* _world;
		CellPosition _position;
		EnergyT      _luminance;
	};
}

