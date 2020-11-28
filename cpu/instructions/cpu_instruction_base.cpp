#include "cpu_instruction_base.hpp"
#include "cpu/cpu.hpp"
#include "cpu/cpu_logger.hpp"
#include "editor/editor_logger.hpp"

nes::CpuInstructionBase::CpuInstructionBase(CPU& cpuRef, AddressingMode addressingMode, std::string_view name) :
	CpuRef(cpuRef),
	InstructionAddressingMode(addressingMode),
	Name(name),
	CycleCount(0),
	AutoUpdateProgramCounter(true)
{
	switch (InstructionAddressingMode)
	{
		case nes::AddressingMode::Absolute:
		case nes::AddressingMode::AbsoluteX:
		case nes::AddressingMode::AbsoluteY:
		case nes::AddressingMode::Indirect:
			InstructionSize = 3;
			break;

		case nes::AddressingMode::Immediate:
		case nes::AddressingMode::IndirectX:
		case nes::AddressingMode::IndirectY:
		case nes::AddressingMode::Relative:
		case nes::AddressingMode::ZeroPage:
		case nes::AddressingMode::ZeroPageX:
		case nes::AddressingMode::ZeroPageY:
			InstructionSize = 2;
			break;

		case nes::AddressingMode::Accumulator:
		case nes::AddressingMode::Implicit:
			InstructionSize = 1;
			break;

		default:
			InstructionSize = 0;
			break;
	}
}

void nes::CpuInstructionBase::PrintDebugInformation() const
{
	// Output every instruction to the debug window
	EditorLogger::GetInstance().LogCpu(CpuLogger::ConstructStreamFromData(CpuRef, Name, InstructionSize).str());
}

void nes::CpuInstructionBase::Execute()
{
	ExecuteImpl();
	CpuRef.UpdateCurrentCycle(CycleCount);

	if (AutoUpdateProgramCounter)
	{
		CpuRef.MoveProgramCounter(InstructionSize);
	}
}
