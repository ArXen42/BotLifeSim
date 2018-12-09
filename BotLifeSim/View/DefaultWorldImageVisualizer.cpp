#include "DefaultWorldImageVisualizer.hpp"

BotLifeSim::DefaultWorldImageVisualizer::DefaultWorldImageVisualizer()
{
	SetBackgroundColor(sf::Color(5, 5, 20));
}

sf::Color BotLifeSim::DefaultWorldImageVisualizer::GetBotColor(const BotLifeSim::Bot& bot)
{
	auto brightness = static_cast<sf::Uint8>(bot.GetEnergy() * UINT8_MAX / Bot::EnergyMax);
	return sf::Color{brightness, brightness, brightness};
}
