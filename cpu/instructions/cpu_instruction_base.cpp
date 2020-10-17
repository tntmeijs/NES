#include "cpu_instruction_base.hpp"
#include "cpu/cpu.hpp"
#include "cpu/cpu_logger.hpp"

#include <iostream>

nes::CpuInstructionBase::CpuInstructionBase(CPU& cpuRef, AddressingMode addressingMode, std::string_view name) :
	CpuRef(cpuRef),
	InstructionAddressingMode(addressingMode),
	Name(name),
	CycleCount(0)
{
	switch (InstructionAddressingMode)
	{
		case nes::AddressingMode::Absolute:
		case nes::AddressingMode::AbsoluteX:
		case nes::AddressingMode::AbsoluteY:
		case nes::AddressingMode::Indirect:
			InstructionSize = 3;

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
	// Convert addressing mode to a short identifier for debugging purposes
	std::string modeId;

	switch (InstructionAddressingMode)
	{
        case nes::AddressingMode::Absolute:
            modeId = "ABS   ";
            break;
        case nes::AddressingMode::AbsoluteX:
			modeId = "ABS X ";
			break;
        case nes::AddressingMode::AbsoluteY:
			modeId = "ABS Y ";
            break;
        case nes::AddressingMode::Accumulator:
			modeId = "ACC   ";
			break;
        case nes::AddressingMode::Immediate:
			modeId = "IMM   ";
			break;
        case nes::AddressingMode::Implicit:
			modeId = "IMPL  ";
			break;
        case nes::AddressingMode::Indirect:
			modeId = "INDR  ";
			break;
        case nes::AddressingMode::IndirectX:
			modeId = "INDR X";
			break;
        case nes::AddressingMode::IndirectY:
			modeId = "INDR Y";
			break;
        case nes::AddressingMode::Relative:
			modeId = "REL   ";
			break;
        case nes::AddressingMode::ZeroPage:
			modeId = "ZERO  ";
			break;
        case nes::AddressingMode::ZeroPageX:
			modeId = "ZERO X";
			break;
        case nes::AddressingMode::ZeroPageY:
			modeId = "ZERO Y";
			break;
        default:
			modeId = "???";
			break;
	}

	// Output to the console window
    std::cout << '[' << modeId << ']' << '\t';
    std::cout << CpuLogger::ConstructStreamFromData(CpuRef, Name, InstructionSize).str() << std::endl;
}

void nes::CpuInstructionBase::Execute() const
{
	ExecuteImpl();
	CpuRef.MoveProgramCounter(InstructionSize);
	CpuRef.UpdateCurrentCycle(CycleCount);
}
