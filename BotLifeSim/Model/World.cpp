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
			_bots.erase(botIt);
			botIt->GetCell()->RemoveBot();

			return true;
		}
	}

	return false;
}
