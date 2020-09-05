#include "editor.hpp"
#include "ui/ui_panel.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <filesystem>

nes::Editor::Editor(sf::RenderWindow& window, CPU& cpu, RAM& ram) :
	WindowRef(window),
	CpuRef(cpu),
	RamRef(ram),
	CpuControllerUI(cpu),
	RamVisualizerUI(ram, cpu),
	ActiveRomName("")
{}

void nes::Editor::Initialize()
{
	ImGui::SFML::Init(WindowRef);
	ApplyStyle();

	std::uint32_t windowWidth = WindowRef.getSize().x;
	std::uint32_t windowHeight = WindowRef.getSize().y;

	std::uint32_t ramVisualizerHeight = static_cast<std::uint32_t>(static_cast<float>(windowHeight) * 0.075f);
	
	CpuControllerUI.Create(windowWidth, windowHeight, 0, 0, 1.0f, 0.075f);
	RamVisualizerUI.Create(windowWidth, windowHeight, 0, ramVisualizerHeight, 0.5f, 0.925f);
}

void nes::Editor::Update(sf::Time deltaTime)
{
	ImGui::SFML::Update(WindowRef, deltaTime);
}

void nes::Editor::ProcessEvent(sf::Event event) const
{
	ImGui::SFML::ProcessEvent(event);
}

void nes::Editor::DrawUI()
{
	//#TODO: Move this to a specialized UI object
	//#TODO: Make this function const again!
	
	CpuControllerUI.Draw();
	RamVisualizerUI.Draw();

	// File explorer
	{
		ImGui::Begin("ROM browser");

		// Scan the directory for NES roms
		std::filesystem::path romPath(std::filesystem::absolute("./roms"));
		if (std::filesystem::exists(romPath))
		{
			std::uint32_t entryCount = 0;
			for (const auto& entry : std::filesystem::directory_iterator(romPath))
			{
				std::filesystem::path filePath = entry.path();
				
				// Potential issue: files with uppercase file extensions will not show in the list
				if (std::strcmp(filePath.extension().string().c_str(), ".nes") != 0)
				{
					// Not a .nes file
					continue;
				}

				std::string fileName = filePath.filename().string();

				if (ImGui::Selectable(fileName.c_str(), (fileName == ActiveRomName)))
				{
					// Load ROM
					ActiveRomName = fileName;
					LoadROM();
				}

				++entryCount;
			}

			// No ROMs available
			if (entryCount == 0)
			{
				std::string message = "No NES ROMs found in \"";
				message.append(romPath.string());
				message.append("\"");
				ImGui::Text(message.c_str());
			}
		}
		else
		{
			ImGui::Text("\"%s\" does not exist!", romPath.string().c_str());
			
			if (ImGui::Button("Create Folder"))
			{
				std::filesystem::create_directories(romPath);
			}
		}

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

void nes::Editor::LoadROM()
{
	if (!ActiveRom.LoadFromDisk(ActiveRomName))
	{
		// ROM failed to load from disk
		ActiveRomName = "";
	}

	if (!ActiveRom.IsValidRom())
	{
		// ROM is invalid
		ActiveRomName = "";
	}

	RamRef.StoreRomData(ActiveRom);
	CpuRef.SetProgramCounterToResetVector();
}
