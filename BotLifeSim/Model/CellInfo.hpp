#pragma once

#include <cstdint>
#include "Types.hpp"
#include "CellPosition.hpp"

namespace BotLifeSim
{
	class World;

	class Bot;

	class CellInfo
	{
	public:
		CellInfo(World* world, const CellPosition& position, EnergyT luminance);

		CellPosition GetPosition() const
		{ return _position; }

		EnergyT GetLuminance() const
		{ return _luminance; }

		CellInfo* const GetCellUp() const;

		CellInfo* const GetCellUpRight() const;

		CellInfo* const GetCellRight() const;

		CellInfo* const GetCellDownRight() const;

		CellInfo* const GetCellDown() const;

		CellInfo* const GetCellDownLeft() const;

		CellInfo* const GetCellLeft() const;

		CellInfo* const GetCellUpLeft() const;

		bool IsAccessible() const
		{ return _bot == nullptr; }

		void RemoveBot()
		{ _bot = nullptr; }

		void SetBot(Bot* bot)
		{ _bot = bot; }

	private:
		World* _world;
		const CellPosition _position;
		const EnergyT      _luminance;

		Bot* _bot;
	};
}

