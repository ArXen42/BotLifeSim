// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "Bot.hpp"
#include "CellInfo.hpp"

namespace BotLifeSim
{
	Bot::Bot(const CellPosition& _position) : _position(_position)
	{
		if (_position.X < 0)
			throw std::invalid_argument("position.X < 0");

		if (_position.Y < 0)
			throw std::invalid_argument("position.Y < 0");
	}

	void Bot::SimulateStep(CellInfo& currentCellInfo)
	{
		size_t currentCommandIndex = 0;

		for (auto i = 0; i < MaxCommandsExecutedPerStep; ++i)
		{
			auto result = ExecuteCommand(currentCommandIndex, currentCellInfo);
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
				if (luminance > EnergyMax - _energy)
					_energy = EnergyMax;
				else
					_energy += luminance;
				return CommandExecutionResult::Terminal;
			case BotCommand::ReadLuminanceUp:
				_registerValue = currentCellInfo.GetCellUp().GetLuminance();
				break;
			case BotCommand::ReadLuminanceUpRight:
				_registerValue = currentCellInfo.GetCellUpRight().GetLuminance();
				break;
			case BotCommand::ReadLuminanceRight:
				_registerValue = currentCellInfo.GetCellRight().GetLuminance();
				break;
			case BotCommand::ReadLuminanceDownRight:
				_registerValue = currentCellInfo.GetCellDownRight().GetLuminance();
				break;
			case BotCommand::ReadLuminanceDown:
				_registerValue = currentCellInfo.GetCellDown().GetLuminance();
				break;
			case BotCommand::ReadLuminanceDownLeft:
				_registerValue = currentCellInfo.GetCellDownLeft().GetLuminance();
				break;
			case BotCommand::ReadLuminanceLeft:
				_registerValue = currentCellInfo.GetCellLeft().GetLuminance();
				break;
			case BotCommand::ReadLuminanceUpLeft:
				_registerValue = currentCellInfo.GetCellUpLeft().GetLuminance();
				break;
			case BotCommand::Move:
				TryMove(currentCellInfo);
				return CommandExecutionResult::Terminal;
			case BotCommand::Jump:
				currentCommandIndex = (currentCommandIndex + _registerValue) % CommandsLength;
				return CommandExecutionResult::NonTerminal;
		}

		currentCommandIndex = (currentCommandIndex + 1) % CommandsLength;
		return CommandExecutionResult::NonTerminal;
	}

	Bot Bot::Divide(CellPosition const& position, std::mt19937& mt19937)
	{
		static std::uniform_int_distribution<int64_t>  mutationsCountDistribution{1, MutationsMax + 1};
		static std::uniform_int_distribution<uint64_t> mutationPositionDistribution{0, CommandsLength};
		static std::uniform_int_distribution<uint64_t> mutationCommandDistribution{0, static_cast<uint64_t>(BotCommand::LastCommand)};

		_energy -= EnergyDefault;
		Bot newBot{position};
		newBot._commands = _commands;

		auto      mutationsCount = mutationsCountDistribution(mt19937);
		for (auto i              = 0; i < mutationsCount; i++)
		{
			auto mutationPosition = mutationPositionDistribution(mt19937);
			auto newCommand       = static_cast<BotCommand>(mutationCommandDistribution(mt19937));

			newBot._commands[mutationPosition] = newCommand;
		}

		return newBot;
	}

	void Bot::TryMove(CellInfo& currentCellInfo)
	{
		CellInfo newCell{nullptr, {-1, -1}, 0};
		switch (_registerValue % 8)
		{
			case 0:
				newCell = currentCellInfo.GetCellUp();
				break;
			case 1:
				newCell = currentCellInfo.GetCellUpRight();
				break;
			case 2:
				newCell = currentCellInfo.GetCellRight();
				break;
			case 3:
				newCell = currentCellInfo.GetCellDownRight();
				break;
			case 4:
				newCell = currentCellInfo.GetCellDown();
				break;
			case 5:
				newCell = currentCellInfo.GetCellDownLeft();
				break;
			case 6:
				newCell = currentCellInfo.GetCellLeft();
				break;
			case 7:
				newCell = currentCellInfo.GetCellUpLeft();
				break;
			default:
				return;
		}

		if (!newCell.IsFilled())
		{
			_position = newCell.GetPosition();
		}
	}
}

