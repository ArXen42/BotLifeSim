#pragma once

#include <vector>
#include "Bot.hpp"

namespace BotLifeSim
{
	class World
	{
	public:
		World(std::initializer_list<Bot> initialBots)
				: bots_(initialBots)
		{}

		std::vector<Bot> const& GetBots() const
		{ return bots_; }

		const uint64_t GetWorldWidth() const
		{ return 1280; };

		const uint64_t GetWorldHeight() const
		{ return 720; }

	private:
		std::vector<Bot> bots_;
	};
}
