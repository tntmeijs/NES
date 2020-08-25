#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "NES");
	window.setVerticalSyncEnabled(true);

	// Initialize ImGui for SFML
	ImGui::SFML::Init(window);

	sf::Color clearColor = sf::Color::Black;
	float color[3] = { clearColor.r, clearColor.g, clearColor.b };

	sf::Clock mainLoopClock;
	
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// Frame delta-time
		sf::Time delta = mainLoopClock.restart();

		// Update ImGui
		ImGui::SFML::Update(window, delta);

		// Test ImGui
		ImGui::Begin("Test Window");
		if (ImGui::ColorEdit3("Clear Color", color))
		{
			clearColor.r = color[0] * 255.0f;
			clearColor.g = color[1] * 255.0f;
			clearColor.b = color[2] * 255.0f;
		}
		ImGui::End();

		window.clear(clearColor);

		// Render ImGui
		ImGui::SFML::Render(window);

		window.display();
	}
}
