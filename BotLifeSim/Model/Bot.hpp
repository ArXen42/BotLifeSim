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

		static constexpr std::size_t CommandsLength             = 64;
		static constexpr std::size_t MaxCommandsExecutedPerStep = 32;

		explicit Bot(const CellPosition& _position);

		CellPosition GetPosition() const
		{ return _position; }

		EnergyT GetEnergy() const
		{ return _energy; }

		void SimulateStep(CellInfo& currentCellInfo);

		Bot Divide(CellPosition const& position, std::mt19937& mt19937);

	private:
		enum class CommandExecutionResult
		{
			Terminal,
			NonTerminal,
		};

	private:
		CellPosition _position;
		EnergyT      _energy{EnergyDefault};

		std::array<BotCommand, CommandsLength> _commands{};
		uint64_t                                _registerValue{0};

	private:
		CommandExecutionResult ExecuteCommand(size_t& currentCommandIndex, CellInfo& currentCellInfo);

		void TryMove(CellInfo& currentCellInfo);
	};
}
