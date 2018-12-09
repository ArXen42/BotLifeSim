#pragma once

#include <vector>
#include "Bot.hpp"

namespace BotLifeSim
{
	class World
	{
	public:
		static constexpr EnergyT LuminanceMax = Bot::EnergyDefault;

		World(std::initializer_list<Bot> initialBots)
				: _bots(initialBots)
		{}

		std::vector<Bot> const& GetBots() const
		{ return _bots; }

		const uint64_t GetWorldWidth() const
		{ return 256; };

		const uint64_t GetWorldHeight() const
		{ return 256; }

		bool IsCellFilled(int64_t x, int64_t y) const;

		void SimulateStep();

		CellInfo GetCellInfo(int64_t x, int64_t y);

	private:
		std::vector<Bot> _bots;

	private:
		bool DivideOrKillBots();
	};
}
