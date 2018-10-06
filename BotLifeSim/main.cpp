#include <iostream>
#include "SFML/Graphics.hpp"

constexpr sf::Uint32 width = 1280, height = 720;

int main()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Bot life sim");

	sf::Texture texture;
	texture.create(width, height);
	texture.setSmooth(false);

	sf::Image image{};
	image.create(width, height);

	for (sf::Uint32 i = 0; i < width; i++)
	{
		image.setPixel(i, height / 2, sf::Color::Red);
	}
	texture.update(image);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(sprite);

		// draw everything here...
		// window.draw(...);

		// end the current frame
		window.display();
	}

	return 0;
}