#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "NES");
	window.setVerticalSyncEnabled(true);

	sf::Color clearColor = sf::Color::Black;

	sf::Clock mainLoopClock;
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Frame delta-time
		sf::Time delta = mainLoopClock.restart();

		window.clear(clearColor);
		window.display();
	}
}
