#include "editor_service.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"
#include "utility/bit_tools.hpp"

bool nes::EditorService::Initialize()
{
	Ram = new RAM();
	Cpu = new CPU(*Ram);
	ActiveRom = new RomFile();

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

std::array<nes::Byte, 256> nes::EditorService::GetCopyOfCurrentStack() const
{
	// The stack has a maximum size of 256 bytes
	auto stack = std::array<Byte, 256>();

	// Stack grows downwards
	for (std::uint8_t i = 0; i < stack.size(); ++i)
	{
		// The stack is stored in an 8-bit register, however, the actual location in
		// memory is on the first page. This is why the STACK_START_ADDRESS is used
		// when calculating the raw pointer into memory.
		// Reference: https://wiki.nesdev.com/w/index.php/Stack
		std::uint16_t address_of_sp_in_ram = Ram->STACK_START_ADDRESS - i;
		stack[i] = Ram->ReadByte(address_of_sp_in_ram);
	}

	return stack;
}
