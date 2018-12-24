// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include "Bot.hpp"
#include "CellInfo.hpp"

namespace BotLifeSim
{

	Bot::Bot(CellInfo* currentCellInfo) : _currentCell(currentCellInfo)
	{}

	void Bot::SimulateStep()
	{

		for (auto i = 0; i < MaxCommandsExecutedPerStep; ++i)
		{
			auto result = ExecuteCommand(_currentCommandIndex);
			if (result == CommandExecutionResult::Terminal)
				return;
		}
	}

	Bot::CommandExecutionResult Bot::ExecuteCommand(size_t& currentCommandIndex)
	{
		auto command = _commands[currentCommandIndex];

		auto luminance = _currentCell->GetLuminance();

		switch (command)
		{
			case BotCommand::Photosynthesis:
				if (luminance > EnergyMax - _energy)
					_energy = EnergyMax;
				else
					_energy += luminance;
				return CommandExecutionResult::Terminal;
			case BotCommand::ReadLuminanceUp:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellUp());
				break;
			case BotCommand::ReadLuminanceUpRight:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellUpRight());
				break;
			case BotCommand::ReadLuminanceRight:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellRight());
				break;
			case BotCommand::ReadLuminanceDownRight:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellDownRight());
				break;
			case BotCommand::ReadLuminanceDown:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellDown());
				break;
			case BotCommand::ReadLuminanceDownLeft:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellDownLeft());
				break;
			case BotCommand::ReadLuminanceLeft:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellLeft());
				break;
			case BotCommand::ReadLuminanceUpLeft:
				SetRegisterValueToLuminanceIfNotNull(_currentCell->GetCellUpLeft());
				break;
			case BotCommand::Move:
				TryMove();
				return CommandExecutionResult::Terminal;
			case BotCommand::Jump:
				currentCommandIndex = (currentCommandIndex + _registerValue) % CommandsLength;
				return CommandExecutionResult::NonTerminal;
		}

		currentCommandIndex = (currentCommandIndex + 1) % CommandsLength;
		return CommandExecutionResult::NonTerminal;
	}

	Bot Bot::Divide(CellInfo* destinationCell, std::mt19937& mt19937)
	{
		static std::uniform_int_distribution<int64_t>  mutationsCountDistribution{1, MutationsMax + 1};
		static std::uniform_int_distribution<uint64_t> mutationPositionDistribution{0, CommandsLength};
		static std::uniform_int_distribution<uint64_t> mutationCommandDistribution{0, static_cast<uint64_t>(BotCommand::LastCommand)};

		_energy -= EnergyDefault;
		Bot newBot{destinationCell};
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

	void Bot::TryMove()
	{
		CellInfo* newCell = nullptr;
		switch (_registerValue % 8)
		{
			case 0:
				newCell = _currentCell->GetCellUp();
				break;
			case 1:
				newCell = _currentCell->GetCellUpRight();
				break;
			case 2:
				newCell = _currentCell->GetCellRight();
				break;
			case 3:
				newCell = _currentCell->GetCellDownRight();
				break;
			case 4:
				newCell = _currentCell->GetCellDown();
				break;
			case 5:
				newCell = _currentCell->GetCellDownLeft();
				break;
			case 6:
				newCell = _currentCell->GetCellLeft();
				break;
			case 7:
				newCell = _currentCell->GetCellUpLeft();
				break;
			default:
				return;
		}

		if (newCell == nullptr)
			return;

		if (!newCell->IsAccessible())
			return;

		_currentCell->RemoveBot();
		newCell->SetBot(this);
		_currentCell = newCell;
	}

	void Bot::SetRegisterValueToLuminanceIfNotNull(CellInfo* cellInfo)
	{
		if (cellInfo != nullptr)
			_registerValue = cellInfo->GetLuminance();
	}

}

