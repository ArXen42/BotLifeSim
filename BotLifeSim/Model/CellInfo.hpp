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

		CellPosition GetPosition() const
		{
			return _position;
		}

		EnergyT GetLuminance() const
		{ return _luminance; }

		CellInfo GetCellUp() const;

		CellInfo GetCellUpRight() const;

		CellInfo GetCellRight() const;

		CellInfo GetCellDownRight() const;

		CellInfo GetCellDown() const;

		CellInfo GetCellDownLeft() const;

		CellInfo GetCellLeft() const;

		CellInfo GetCellUpLeft() const;

		bool IsFilled() const;


	private:
		World* _world;
		CellPosition _position;
		EnergyT      _luminance;
	};
}

