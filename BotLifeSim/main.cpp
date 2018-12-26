// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <iostream>
#include <thread>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Model/World.hpp"
#include "View/DefaultWorldImageVisualizer.hpp"

constexpr auto Delay = std::chrono::milliseconds(0); // NOLINT(cert-err58-cpp)

int main()
{
	using namespace BotLifeSim;

	BotLifeSim::World world{42};

	auto const textureWidth  = static_cast<sf::Uint32>(World::WorldWidth);
	auto const textureHeight = static_cast<sf::Uint32>(World::WorldHeight);

	sf::RenderWindow window(sf::VideoMode(textureWidth, textureHeight), "Bot life sim");

	sf::Texture texture;
	texture.create(textureWidth, textureHeight);
	texture.setSmooth(false);

	sf::Image image{};
	image.create(textureWidth, textureHeight);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(3, 3);

	BotLifeSim::DefaultWorldImageVisualizer worldImageVisualizer{};

	uint64_t stepNum = 0;
	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		std::cout << "World population: " << world.GetBots().size() << std::endl;
		std::cout << "Simulating step " << ++stepNum << std::endl;
		world.SimulateStep();


		std::this_thread::sleep_for(Delay);

		window.clear(sf::Color::Black);
		worldImageVisualizer.DrawWorld(world, image);
		texture.update(image);
		window.draw(sprite);

		window.display();
	}

	return 0;
}