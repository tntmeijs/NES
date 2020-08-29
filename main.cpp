#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "editor/editor.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "NES");
	window.setVerticalSyncEnabled(true);

	nes::RAM ram;
	ram.Initialize(0x10000);	//#DEBUG: Allocate plenty of memory to store a test ROM in

	nes::CPU Mos6502(ram);
	Mos6502.Entry();

	nes::Editor nesEditor(window, Mos6502, ram);
	nesEditor.Initialize();

	sf::Color clearColor = sf::Color::Black;
	sf::Clock mainLoopClock;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			nesEditor.ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Frame delta-time
		sf::Time delta = mainLoopClock.restart();

		// Update
		nesEditor.Update(delta);
		
		// Render
		window.clear(clearColor);
		nesEditor.DrawUI();
		window.display();
	}

	nesEditor.Destroy();
	ram.Delete();
}
