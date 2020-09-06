#include "ui_rom_browser.hpp"

#include <imgui.h>

#include <filesystem>

void nes::UIRomBrowser::DrawImpl() const
{
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

			// Manual "tab" character length as Dear ImGui does not seem to respect
			// tabs properly, it always inserts 4 spaces
			std::uint32_t numberOfCharactersInCount = 0;
			std::uint32_t multiplier = 1;
			while (multiplier <= entryCount + 1)
			{
				multiplier *= 10;
				++numberOfCharactersInCount;
			}

			// By default a tab character is 4 spaces
			std::uint32_t numberOfSpaces = 4 - numberOfCharactersInCount;

			std::string fileName = '(' + std::to_string(entryCount + 1) + ')';
			
			// Insert "tabs"
			for (std::uint32_t i = 0; i < numberOfSpaces; ++i)
			{
				fileName += ' ';
			}

			// Add one full-length "tab" character to add some more padding
			fileName += '\t';

			// Add the ROM name
			fileName += filePath.filename().string();

			// Display the entry
			if (ImGui::Selectable(fileName.c_str()))
			{
				// Load ROM
				if (OnLoadRom)
				{
					OnLoadRom(filePath.string());
				}
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
}
