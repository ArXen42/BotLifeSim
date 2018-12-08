#include "DefaultWorldImageVisualizer.hpp"

BotLifeSim::DefaultWorldImageVisualizer::DefaultWorldImageVisualizer()
{
	SetBackgroundColor(sf::Color(5, 5, 20));
}

sf::Color BotLifeSim::DefaultWorldImageVisualizer::GetBotColor(BotLifeSim::Bot& bot)
{
	return sf::Color::White;
}
