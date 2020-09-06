#include "editor.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

nes::Editor::Editor(sf::RenderWindow& window, CPU& cpu, RAM& ram) :
	WindowRef(window),
	CpuRef(cpu),
	RamRef(ram),
	CpuControllerUI(cpu),
	RamVisualizerUI(ram, cpu)
{}

void nes::Editor::Initialize()
{
	ImGui::SFML::Init(WindowRef);
	ApplyStyle();

	// Register ROM loading callback
	RomBrowserUI.OnLoadRom = [this](const std::string& romPath)
	{
		LoadROM(romPath);
	};

	std::uint32_t windowWidth = WindowRef.getSize().x;
	std::uint32_t windowHeight = WindowRef.getSize().y;

	std::uint32_t ramVisualizerHeight = static_cast<std::uint32_t>(static_cast<float>(windowHeight) * 0.075f);
	std::uint32_t romBrowserHorizontalOffset = static_cast<std::uint32_t>(static_cast<float>(windowWidth) * 0.65f);
	
	CpuControllerUI.Create(windowWidth, windowHeight, 0, 0, 0.65f, 0.075f);
	RamVisualizerUI.Create(windowWidth, windowHeight, 0, ramVisualizerHeight, 0.5f, 0.925f);
	RomBrowserUI.Create(windowWidth, windowHeight, romBrowserHorizontalOffset, 0, 0.35f, 0.075f);
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
	CpuControllerUI.Draw();
	RamVisualizerUI.Draw();
	RomBrowserUI.Draw();

	ImGui::SFML::Render(WindowRef);
}

void nes::Editor::Destroy()
{
	ImGui::SFML::Shutdown();
}

void nes::Editor::ApplyStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;			// Rectangular windows
}

void nes::Editor::LoadROM(const std::string& romPath)
{
	if (!ActiveRom.LoadFromDisk(romPath))
	{
		// ROM failed to load from disk
		return;
	}

	if (!ActiveRom.IsValidRom())
	{
		// ROM is invalid
		return;
	}

	// Success, load the ROM file into memory
	RamRef.StoreRomData(ActiveRom);
	CpuRef.SetProgramCounterToResetVector();
}
