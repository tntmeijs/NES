#include "cpu_instruction_base.hpp"
#include "cpu/cpu_logger.hpp"

#include <iostream>

nes::CpuInstructionBase::CpuInstructionBase(CPU& cpuRef, std::string_view name, std::uint8_t size) :
	CpuRef(cpuRef),
	Name(name),
	InstructionSize(size)
{}

void nes::CpuInstructionBase::PrintDebugInformation()
{
	// Output to the console window
	std::cout << CpuLogger::ConstructStreamFromData(CpuRef, Name, InstructionSize).str() << std::endl;
}
