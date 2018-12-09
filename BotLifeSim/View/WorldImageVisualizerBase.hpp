#pragma once

#include <SFML/Graphics/Image.hpp>
#include "../Model/World.hpp"

namespace BotLifeSim
{
	class WorldImageVisualizerBase
	{
	public:
		void DrawWorld(const World& world, sf::Image& image);

		sf::Color GetBackgroundColor()
		{ return _backgroundColor; };

	protected:
		WorldImageVisualizerBase() = default;

		virtual sf::Color GetBotColor(Bot& bot) = 0;

		void SetBackgroundColor(sf::Color color)
		{ _backgroundColor = color; }

	private:
		sf::Color _backgroundColor{0, 0, 0};
	};
}


