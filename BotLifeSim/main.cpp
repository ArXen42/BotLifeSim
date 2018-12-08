#include <iostream>
#include "SFML/Graphics.hpp"
#include "Model/World.hpp"
#include "View/DefaultWorldImageVisualizer.hpp"

constexpr sf::Uint32 TextureWidth = 1280, TextureHeight = 720;

int main()
{
	BotLifeSim::World world{
			BotLifeSim::Bot{0, 1},
			BotLifeSim::Bot{1, 4},
			BotLifeSim::Bot{2, 5},
			BotLifeSim::Bot{5, 20},
			BotLifeSim::Bot{34, 12},
			BotLifeSim::Bot{23, 42},
			BotLifeSim::Bot{12, 24},
			BotLifeSim::Bot{42, 0},
			BotLifeSim::Bot{93, 55},
			BotLifeSim::Bot{121, 63},
			BotLifeSim::Bot{324, 525},
			BotLifeSim::Bot{525, 333},
			BotLifeSim::Bot{421, 222},
			BotLifeSim::Bot{22, 111},
			BotLifeSim::Bot{119, 192},
			BotLifeSim::Bot{332, 899},
			BotLifeSim::Bot{524, 1},
			BotLifeSim::Bot{22, 2},
			BotLifeSim::Bot{0, 4},
			BotLifeSim::Bot{0, 10},
			BotLifeSim::Bot{0, 19},
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

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);

		worldImageVisualizer.DrawWorld(world, image);
		texture.update(image);
		window.draw(sprite);

		window.display();
	}

	return 0;
}