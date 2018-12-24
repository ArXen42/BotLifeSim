#pragma once

#include <vector>
#include <random>
#include "CellInfo.hpp"
#include "Bot.hpp"
#include <iostream>

namespace BotLifeSim
{
	class World
	{
	public:
		static constexpr EnergyT  LuminanceMax = Bot::EnergyDefault / 4;
		static constexpr EnergyT  EnergyDrain  = Bot::EnergyDefault / 48;
		static constexpr uint64_t WorldWidth   = 150;
		static constexpr uint64_t WorldHeight  = 150;

		explicit World(int64_t seed);

		std::vector<Bot> const& GetBots() const
		{ return _bots; }

		std::array<std::vector<CellInfo>, WorldHeight>& GetCells()
		{ return _cells; }

		void SimulateStep();

		CellInfo* GetCellInfo(uint64_t x, uint64_t y)
		{
			if (x < WorldWidth && y < WorldHeight)
			{
				auto& row = _cells[y];
				return row.data() + x;
			}

			return nullptr;
		}

		CellInfo* GetCellInfo(const CellPosition& position)
		{
			return GetCellInfo(position.X, position.Y);
		}

	private:
		std::vector<Bot>                               _bots;
		std::array<std::vector<CellInfo>, WorldHeight> _cells{};
		std::mt19937                                   mt19937;

	private:
		bool DivideOrKillBots();
	};
}
