#include "editor.hpp"
#include "ui/ui_panel.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <cmath>		// std::ceil
#include <filesystem>
#include <iomanip>		// std::hex / std::setw / std::setfill
#include <sstream>

nes::Editor::Editor(sf::RenderWindow& window, CPU& cpu, RAM& ram) :
	WindowRef(window),
	CpuRef(cpu),
	RamRef(ram),
	ActiveRom(nullptr),
	ActiveRomName("")
{}

void nes::Editor::Initialize()
{
	ImGui::SFML::Init(WindowRef);
	ActiveRom = new RomFile();

	ApplyStyle();
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
	
	// CPU controller
	{
		ImGui::Begin("CPU controller");
		ImGui::Text("Current Address:\t0x%04X", CpuRef.GetProgramCounter());
		ImGui::PushButtonRepeat(true);
		if (ImGui::Button("Next Instruction"))
		{
			CpuRef.NextInstruction();
		}
		ImGui::PopButtonRepeat();
		ImGui::End();
	}

	// RAM visualizer
	{
		ImGui::Begin("RAM visualization");
		ImGuiListClipper clipper(static_cast<std::int32_t>(std::ceil(static_cast<float>(RamRef.Size) / 16.0f)));
		while (clipper.Step())
		{
			for (std::int32_t row = clipper.DisplayStart; row < clipper.DisplayEnd; ++row)
			{
				// Stream with default settings
				std::stringstream rowText;
				rowText << std::hex << std::uppercase << std::setfill('0');

				// Represent the base address for this row using four hexadecimal characters
				rowText << "0x" << std::setw(4) << (row * 16) << "  |  ";

				// Render 16 bytes per row
				for (std::uint16_t column = 0; column < 16; ++column)
				{
					std::uint16_t address = (row * 16) + column;

					// Need to cast the value in RAM to a wider type to force it to be treated as a number rather than a character
					std::uint16_t valueAtAddress = static_cast<std::uint16_t>(RamRef.ReadByte(address++));

					if (CpuRef.GetProgramCounter() == address - 1)
					{
						// If the program counter points to this byte, highlight it
						rowText << "( " << std::setw(2) << valueAtAddress << " )";
					}
					else
					{
						// Else, display it with the usual spacing
						rowText << "  " << std::setw(2) << valueAtAddress << "  ";
					}
				}

				// Display this row
				ImGui::Text(rowText.str().c_str());
			}
		}
		ImGui::End();
	}

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
	if (ActiveRom)
	{
		delete ActiveRom;
		ActiveRom = nullptr;
	}

	ImGui::SFML::Shutdown();
}

void nes::Editor::ApplyStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 0.0f;			// Rectangular windows
}

void nes::Editor::LoadROM()
{
	if (!ActiveRom->LoadFromDisk(ActiveRomName))
	{
		// ROM failed to load from disk
		ActiveRomName = "";
	}

	if (!ActiveRom->IsValidRom())
	{
		// ROM is invalid
		ActiveRomName = "";
	}
}
