#include <iostream>
#include <thread>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Model/World.hpp"
#include "View/DefaultWorldImageVisualizer.hpp"

constexpr std::chrono::duration Delay        = std::chrono::milliseconds(0);

int main()
{
	BotLifeSim::World world{
			BotLifeSim::Bot{{16, 16}}
	};

	auto const textureWidth  = static_cast<sf::Uint32>(world.GetWorldWidth());
	auto const textureHeight = static_cast<sf::Uint32>(world.GetWorldHeight());

	sf::RenderWindow window(sf::VideoMode(textureWidth, textureHeight), "Bot life sim");

	sf::Texture texture;
	texture.create(textureWidth, textureHeight);
	texture.setSmooth(false);

	sf::Image image{};
	image.create(textureWidth, textureHeight);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(4,4);

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