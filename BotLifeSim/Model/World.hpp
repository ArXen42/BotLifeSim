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
		static constexpr uint64_t WorldWidth   = 160;
		static constexpr uint64_t WorldHeight  = 160;

		explicit World(int64_t seed) : mt19937{seed}
		{
			for (size_t y = 0; y < WorldHeight; y++)
			{
				auto& row = _cells[y];

				for (size_t x = 0; x < WorldWidth; x++)
				{
					row.emplace_back(CellInfo{this, {x, y}, static_cast<EnergyT>(y * LuminanceMax / WorldHeight)});
				}
				std::cout << "Initialized row" << y << ": " << row.size() << std::endl;
			}

			auto* cell     = GetCellInfo(WorldWidth / 2, WorldHeight / 2);
			auto& firstBot = _bots.emplace_back(Bot{cell});

			cell->SetBot(&firstBot);

		}

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
