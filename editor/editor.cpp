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
	// Height of the main menu bar, can be used as an offset to position elements
	// right underneath the main menu bar
	float mainMenuBarHeight = 0.0f;

	// Main menu bar
	{
		if (ImGui::BeginMainMenuBar())
		{
			mainMenuBarHeight = ImGui::GetWindowSize().y;

			if (ImGui::BeginMenu("CPU"))
			{
				CpuControllerUI.Draw();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Load"))
			{
				RomBrowserUI.Draw();
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Reset"))
			{
				ImGui::Text("Reset CPU:");
				ImGui::SameLine();
				if (ImGui::Button("RESET"))
				{
					CpuRef.SetDefaultState();
				}

				ImGui::Separator();

				ImGui::Text("Reset RAM:");
				ImGui::SameLine();
				if (ImGui::Button("RESET"))
				{
					RamRef.Clear();
				}

				ImGui::Separator();

				ImGui::Text("Reset ALL:");
				ImGui::SameLine();
				if (ImGui::Button("RESET"))
				{
					CpuRef.SetDefaultState();
					RamRef.Clear();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	// RAM visualizer
	{
		ImGui::Begin("##ram_visualizer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

		float windowWidth = static_cast<float>(WindowRef.getSize().x) * 0.5f;
		float windowHeight = static_cast<float>(WindowRef.getSize().y) - mainMenuBarHeight;

		// Fixed position and size
		ImGui::SetWindowPos("##ram_visualizer", { windowWidth, mainMenuBarHeight });
		ImGui::SetWindowSize("##ram_visualizer", { windowWidth, windowHeight });

		RamVisualizerUI.Draw();

		ImGui::End();
	}

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
