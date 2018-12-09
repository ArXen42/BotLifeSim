#include <iostream>
#include "Bot.hpp"
#include "CellInfo.hpp"

namespace BotLifeSim
{
	Bot::Bot(const CellPosition& _position) : _position(_position)
	{}

	void Bot::SimulateStep(CellInfo& currentCellInfo)
	{
		size_t currentCommandIndex = 0;

		CommandExecutionResult result = CommandExecutionResult::NonTerminal;
		for (auto              i      = 0; i < MaxCommandsExecutedPerStep; ++i)
		{
			if (result == CommandExecutionResult::Jump)
				currentCommandIndex = (currentCommandIndex + static_cast<uint64_t>(_commands[i])) % CommandsLength;

			result = ExecuteCommand(currentCommandIndex, currentCellInfo);
			if (result == CommandExecutionResult::Terminal)
				return;
		}
	}

	Bot::CommandExecutionResult Bot::ExecuteCommand(size_t& currentCommandIndex, CellInfo& currentCellInfo)
	{
		auto command = _commands[currentCommandIndex];

		auto luminance = currentCellInfo.GetLuminance();
		switch (command)
		{
			case BotCommand::Photosynthesis:
				std::cout << _energy << std::endl;
				if (luminance > EnergyMax - _energy)
					_energy = EnergyMax;
				else
					_energy += luminance;
				std::cout << std::to_string(_energy) << std::endl;
				return CommandExecutionResult::Terminal;
			case BotCommand::ReadLuminanceUp:
				break;
			case BotCommand::ReadLuminanceUpRight:
				break;
			case BotCommand::ReadLuminanceRight:
				break;
			case BotCommand::ReadLuminanceDownRight:
				break;
			case BotCommand::ReadLuminanceDown:
				break;
			case BotCommand::ReadLuminanceDownLeft:
				break;
			case BotCommand::ReadLuminanceLeft:
				break;
			case BotCommand::ReadLuminanceUpLeft:
				break;
			case BotCommand::Move:
				return CommandExecutionResult::Terminal;
			case BotCommand::Jump:
				return CommandExecutionResult::Jump;
		}

		currentCommandIndex = (currentCommandIndex + 1) % CommandsLength;
		return CommandExecutionResult::NonTerminal;
	}

	Bot Bot::Divide(int64_t x, int64_t y)
	{
		_energy -= EnergyDefault;
		return Bot{{x, y}};
	}
}

