// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "WorldImageVisualizerBase.hpp"

void BotLifeSim::WorldImageVisualizerBase::DrawWorld(const BotLifeSim::World& world, sf::Image& image)
{
	for (sf::Uint32 x = 0; x < world.GetWorldWidth(); x++)
	{
		for (sf::Uint32 y = 0; y < world.GetWorldHeight(); y++)
		{
			image.setPixel(x, y, GetBackgroundColor());
		}
	}

	for (auto const& bot: world.GetBots())
	{
		image.setPixel(static_cast<sf::Uint32>(bot.GetPosition().X), static_cast<sf::Uint32>(bot.GetPosition().Y),
		               GetBotColor(bot));
	}
}
