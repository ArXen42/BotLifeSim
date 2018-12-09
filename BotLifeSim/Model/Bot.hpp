#pragma once

#include <cstdint>
#include <array>
#include "BotCommand.hpp"
#include "Types.hpp"
#include "CellPosition.hpp"

namespace BotLifeSim
{
	class CellInfo;

	class Bot
	{
	public:
		static constexpr EnergyT EnergyMax     = UINT8_MAX;
		static constexpr EnergyT EnergyDefault = EnergyMax / 2;

		static constexpr std::size_t CommandsLength             = 64;
		static constexpr std::size_t MaxCommandsExecutedPerStep = 32;

		explicit Bot(const CellPosition& _position);

		CellPosition GetPosition() const
		{ return _position; }

		EnergyT GetEnergy() const
		{ return _energy; }

		void SimulateStep(CellInfo& currentCellInfo);

		Bot Divide(CellPosition const& position);

	private:
		enum class CommandExecutionResult
		{
			Terminal,
			NonTerminal,
			Jump
		};

	private:
		CellPosition _position;
		EnergyT      _energy{EnergyDefault};

		std::array<BotCommand, CommandsLength> _commands{};
		int64_t                                _registerValue{-1};

	private:
		CommandExecutionResult ExecuteCommand(size_t& currentCommandIndex, CellInfo& currentCellInfo);
	};
}
