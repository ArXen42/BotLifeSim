// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "World.hpp"
#include "CellInfo.hpp"

void BotLifeSim::World::SimulateStep()
{
	for (auto& bot: _bots)
	{
		bot.SimulateStep();
	}

	while (DivideOrKillBots())
	{}

	for (auto& bot: _bots)
	{
		bot.DrainEnergy(EnergyDrain);
	}
}

bool BotLifeSim::World::DivideOrKillBots()
{
	for (auto botIt = _bots.begin(); botIt != _bots.end(); ++botIt)
	{
		if (botIt->GetEnergy() == 0)
			botIt = _bots.erase(botIt);

		if (botIt->GetEnergy() != Bot::EnergyMax)
			continue;

		auto const& position = botIt->GetCell()->GetPosition();
		uint64_t x = position.X;
		uint64_t y = position.Y;

		bool canDivide = false;

		std::array<CellPosition, 8> positionsToCheck{
				CellPosition{x, y - 1},
				CellPosition{x + 1, y - 1},
				CellPosition{x + 1, y},
				CellPosition{x + 1, y + 1},
				CellPosition{x, y + 1},
				CellPosition{x - 1, y + 1},
				CellPosition{x - 1, y},
				CellPosition{x - 1, y - 1},
		};

		CellInfo* newCell = nullptr;

		for (auto& pos: positionsToCheck)
		{
			auto cell = GetCellInfo(pos);
			if (cell == nullptr)
				continue;

			if (!cell->IsAccessible())
				continue;

			canDivide = true;
			newCell   = cell;
			break;
		}

		if (canDivide)
		{
			auto newBot = botIt->Divide(newCell, mt19937);
			_bots.push_back(newBot);
			auto& newBotPushed = _bots[_bots.size() - 1];

			newBot.GetCell()->SetBot(&newBotPushed);

			return true;
		}
		else
		{
			botIt->GetCell()->RemoveBot();
			_bots.erase(botIt);

			return true;
		}
	}

	return false;
}

BotLifeSim::World::World(int64_t seed) : mt19937{seed}
{
	for (size_t y = 0; y < WorldHeight; y++)
	{
		auto& row = _cells[y];

		for (size_t x = 0; x < WorldWidth; x++)
		{
			row.emplace_back(CellInfo{this, {x, y}, static_cast<EnergyT>((WorldHeight - y) * LuminanceMax / WorldHeight)});
		}
		std::cout << "Initialized row" << y << ": " << row.size() << std::endl;
	}

	auto* cell     = GetCellInfo(WorldWidth / 2, WorldHeight / 2);
	auto& firstBot = _bots.emplace_back(Bot{cell});

	cell->SetBot(&firstBot);

}
