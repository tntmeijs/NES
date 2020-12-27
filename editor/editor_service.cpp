#include "editor_service.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"

#include "editor_logger.hpp"

#include <array>
#include <cstdint>

bool nes::EditorService::Initialize()
{
	Ram = new RAM();
	Cpu = new CPU(*Ram);
	ActiveRom = new RomFile();

	// Keep track of any changes to the stack pointer
	Cpu->OnStackPush = [&](auto byte)
	{
		MinimalStack.push_back(byte);
		OnUpdateStackVisualization(MinimalStack);
	};

	Cpu->OnStackPop = [&](auto byte)
	{
		MinimalStack.erase(MinimalStack.end() - 1);
		OnUpdateStackVisualization(MinimalStack);
	};

	return true;
}

void nes::EditorService::Destroy()
{
	delete Cpu;
	delete Ram;
	delete ActiveRom;
}

bool nes::EditorService::TryLoadRomFile(std::string_view path)
{
	if (!ActiveRom->LoadFromDisk(path))
	{
		return false;
	}

	if (!ActiveRom->IsValidRom())
	{
		return false;
	}

	Ram->StoreRomData(*ActiveRom);
	Cpu->SetProgramCounterToResetVector();

	return true;
}

bool nes::EditorService::HasLoadedRom() const
{
	return ActiveRom->IsValidRom();
}

void nes::EditorService::ExecuteNextCpuInstruction() const
{
	Cpu->ExecuteInstruction();
}

void nes::EditorService::SetCpuProgramCounter(std::uint16_t address) const
{
	Cpu->SetProgramCounterToAddress(address);
}

std::uint16_t nes::EditorService::GetCpuProgramCounterValue() const
{
	return Cpu->GetProgramCounter();
}

std::uint64_t nes::EditorService::GetCpuCurrentCycle() const
{
	return Cpu->GetCurrentCycle();
}
