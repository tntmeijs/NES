#include "editor_service.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"

bool nes::EditorService::Initialize()
{
	Ram = new RAM();
	Cpu = new CPU(*Ram);
	ActiveRom = new RomFile();

	return false;
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