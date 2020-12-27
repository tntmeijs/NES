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
	Cpu->OnStackPointerChange = [&]()
	{
		/**
		 * Make a copy of the current stack
		 * 
		 * This is not super efficient, but it works well enough
		 * We only copy 256 bytes, which is not that much data
		 * 
		 * There are bigger performance gains to be had elsewhere in this emulator
		 */
		std::array<Byte, 256> stack;
		for (std::uint16_t i = 0; i < 256; ++i)
		{
			auto address = Ram->STACK_START_ADDRESS - i;
			auto value = Ram->ReadByte(address);
			stack[i] = value;
		}

		OnUpdateStackVisualization(stack);
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

std::uint8_t nes::EditorService::GetStackPointerValue() const
{
	return Cpu->GetRegister(CPU::RegisterType::SP).value;
}
