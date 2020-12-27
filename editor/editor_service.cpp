#include "editor_service.hpp"
#include "cpu/cpu.hpp"
#include "ram/ram.hpp"
#include "io/rom_file.hpp"

#include "editor_logger.hpp"

bool nes::EditorService::Initialize()
{
	Ram = new RAM();
	Cpu = new CPU(*Ram);
	ActiveRom = new RomFile();

	// Ensure the stack is set to a known state (zero)
	for (auto i = 0; i < StackCopy.size(); ++i)
	{
		StackCopy[i] = Byte();
	}

	// Keep track of any changes to the stack pointer
	Cpu->OnStackPointerChange = std::bind(&EditorService::OnStackChanged, this);

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

const std::array<nes::Byte, 256>& nes::EditorService::GetCurrentStackState() const
{
	return StackCopy;
}

void nes::EditorService::OnStackChanged()
{
	// Value of the stack pointer index
	auto registerValue = Cpu->GetRegister(CPU::RegisterType::SP).value;

	// Value of the byte pointed to by the stack pointer
	auto stackValue = Ram->ReadByte(Cpu->GetStackPointerAbsoluteAddress()).value;

	// Update our local copy of the stack
	StackCopy[registerValue].value = stackValue;
}
