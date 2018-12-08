#pragma once

#include "WorldImageVisualizerBase.hpp"

namespace BotLifeSim
{
	class DefaultWorldImageVisualizer : public WorldImageVisualizerBase
	{
	public:
		DefaultWorldImageVisualizer();

	private:
		sf::Color GetBotColor(Bot& bot) override;
	};
}


