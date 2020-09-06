#include "ui_rom_browser.hpp"

#include <imgui.h>

#include <algorithm>	// std::sort / std::clamp
#include <filesystem>
#include <vector>

void nes::UIRomBrowser::Draw() const
{
	// Scan the directory for NES roms
	std::filesystem::path romPath(std::filesystem::absolute("./roms"));
	if (std::filesystem::exists(romPath))
	{
		std::vector<std::filesystem::path> foundRomPaths;

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

			foundRomPaths.push_back(filePath);
		}

		if (foundRomPaths.empty())
		{
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
			// Sort the list of ROMs alphabetically to make it easy to find ROMs
			std::sort(foundRomPaths.begin(), foundRomPaths.end());

			// Display a maximum of 10 ROMs at the same time
			int displayCount = std::clamp(static_cast<int>(foundRomPaths.size()), 1, 10);

			if (ImGui::ListBoxHeader("##available_rom_names", foundRomPaths.size(), displayCount))
			{
				for (const auto& path : foundRomPaths)
				{
					if (ImGui::Selectable(path.filename().string().c_str()))
					{
						// Load ROM
						if (OnLoadRom)
						{
							OnLoadRom(path.string());
						}
					}
				}

				ImGui::ListBoxFooter();
			}
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
