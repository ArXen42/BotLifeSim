#pragma once

#include <cstdint>
#include <array>
#include <random>
#include "BotCommand.hpp"
#include "Types.hpp"
#include "CellPosition.hpp"

namespace BotLifeSim
{
	class CellInfo;

	class Bot
	{
	public:
		static constexpr EnergyT     EnergyMax     = UINT8_MAX;
		static constexpr EnergyT     EnergyDefault = EnergyMax / 2;
		static constexpr std::size_t MutationsMax  = 2;

		static constexpr std::size_t CommandsLength             = 32;
		static constexpr std::size_t MaxCommandsExecutedPerStep = 16;

		explicit Bot(CellInfo* currentCellInfo);

		CellInfo* GetCell() const
		{ return _currentCell; }

		EnergyT GetEnergy() const
		{ return _energy; }

		void DrainEnergy(EnergyT drain)
		{
			if (drain > _energy)
				_energy = 0;
			else
				_energy -= drain;
		}

		void SimulateStep();

		Bot Divide(CellInfo* destinationCell, std::mt19937& mt19937);

	private:
		enum class CommandExecutionResult
		{
			Terminal,
			NonTerminal,
		};

	private:
		CellInfo* _currentCell;
		EnergyT _energy{EnergyDefault};
		size_t  _currentCommandIndex                            = 0;

		std::array<BotCommand, CommandsLength> _commands{};
		uint64_t                               _registerValue{0};

	private:
		CommandExecutionResult ExecuteCommand(size_t& currentCommandIndex);

		void SetRegisterValueToLuminanceIfNotNull(CellInfo* cellInfo);

		void TryMove();

	};
}
