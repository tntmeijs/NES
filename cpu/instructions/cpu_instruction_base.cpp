#include "cpu_instruction_base.hpp"
#include "cpu/cpu_logger.hpp"

#include <iostream>

nes::CpuInstructionBase::CpuInstructionBase(CPU& cpuRef, AddressingMode addressingMode, std::string_view name, std::uint8_t size) :
	CpuRef(cpuRef),
	InstructionAddressingMode(addressingMode),
	Name(name),
	InstructionSize(size)
{}

void nes::CpuInstructionBase::PrintDebugInformation()
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
