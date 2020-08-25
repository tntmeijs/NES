#include "editor.hpp"
#include "ui/ui_panel.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

nes::Editor::Editor(sf::RenderWindow& window) :
	WindowRef(window),
	TestPanel(nullptr)
{}

void nes::Editor::Initialize()
{
	ImGui::SFML::Init(WindowRef);

	ApplyStyle();

	TestPanel = new UIPanel(1280, 720, 0, 0, 0.25f, 0.5f);
}

void nes::Editor::Update(sf::Time deltaTime)
{
	ImGui::SFML::Update(WindowRef, deltaTime);
}

void nes::Editor::ProcessEvent(sf::Event event) const
{
	ImGui::SFML::ProcessEvent(event);
}

void nes::Editor::DrawUI() const
{
	TestPanel->Draw();
	ImGui::SFML::Render(WindowRef);
}

void nes::Editor::Destroy()
{
	ImGui::SFML::Shutdown();

	if (TestPanel)
	{
		delete TestPanel;
		TestPanel = nullptr;
	}
}

void nes::Editor::ApplyStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;			// Rectangular windows
}
