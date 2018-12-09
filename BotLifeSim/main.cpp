#include <iostream>
#include <thread>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Model/World.hpp"
#include "View/DefaultWorldImageVisualizer.hpp"

constexpr sf::Uint32            TextureWidth = 256, TextureHeight = 256;
constexpr std::chrono::duration Delay        = std::chrono::milliseconds(1);

int main()
{
	BotLifeSim::World world{
			BotLifeSim::Bot{{TextureWidth / 2, TextureHeight / 2}}
	};

	sf::RenderWindow window(sf::VideoMode(TextureWidth, TextureHeight), "Bot life sim");

	sf::Texture texture;
	texture.create(TextureWidth, TextureHeight);
	texture.setSmooth(false);

	sf::Image image{};
	image.create(TextureWidth, TextureHeight);

	sf::Sprite sprite;
	sprite.setTexture(texture);

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