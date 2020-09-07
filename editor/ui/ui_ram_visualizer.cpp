#include "ui_ram_visualizer.hpp"
#include "ram/ram.hpp"
#include "cpu/cpu.hpp"

#include <imgui.h>

#include <cmath>		// std::ceil
#include <iomanip>		// std::hex / std::setw / std::setfill
#include <sstream>

nes::UIRamVisualizer::UIRamVisualizer(const RAM& ramRef, const CPU& cpuRef) :
	RamRef(ramRef),
	CpuRef(cpuRef)
{}

void nes::UIRamVisualizer::Draw() const
{
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
					rowText << "(" << std::setw(2) << valueAtAddress << ")";
				}
				else
				{
					// Else, display it with the usual spacing
					rowText << " " << std::setw(2) << valueAtAddress << " ";
				}
			}

			// Display this row
			ImGui::Text(rowText.str().c_str());
		}
	}
}
