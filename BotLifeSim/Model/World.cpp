// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "World.hpp"
#include "CellInfo.hpp"

void BotLifeSim::World::SimulateStep()
{
	for (auto& bot: _bots)
	{
		auto cell = GetCellInfo(bot.GetPosition().X, bot.GetPosition().Y);
		bot.SimulateStep(cell);
	}

	while (DivideOrKillBots())
	{}
}

BotLifeSim::CellInfo BotLifeSim::World::GetCellInfo(int64_t x, int64_t y)
{
	CellPosition position{x, y};
	position.FitConstraints(GetWorldWidth(), GetWorldHeight());

	auto luminance = static_cast<EnergyT>(y * LuminanceMax / GetWorldHeight());

	CellInfo cell(this, position, luminance);
	return cell;
}

bool BotLifeSim::World::IsCellFilled(int64_t x, int64_t y) const
{
	CellPosition checkedPosition{x, y};
	checkedPosition.FitConstraints(GetWorldWidth(), GetWorldHeight());

	for (auto& bot: _bots)
	{
		if (bot.GetPosition() == checkedPosition)
			return false;
	}

	return true;
}

bool BotLifeSim::World::DivideOrKillBots()
{
	for (auto botIt = _bots.begin(); botIt != _bots.end(); ++botIt)
	{
		if (botIt->GetEnergy() == 0)
			botIt = _bots.erase(botIt);

		if (botIt->GetEnergy() != Bot::EnergyMax)
			continue;

		auto const& position = botIt->GetPosition();
		int64_t x = botIt->GetPosition().X;
		int64_t y = botIt->GetPosition().Y;

		bool         canDivide = false;
		CellPosition newPosition{};

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

		for (auto& pos: positionsToCheck)
		{
			if (!IsCellFilled(pos.X, pos.Y))
				continue;

			canDivide   = true;
			newPosition = pos;
			break;
		}

		if (canDivide)
		{
			newPosition.FitConstraints(GetWorldWidth(), GetWorldHeight());
			auto newBot = botIt->Divide(newPosition, mt19937);
			_bots.push_back(newBot);
			return true;
		}
		else
		{
			_bots.erase(botIt);
			return true;
		}
	}

	return false;
}
