#include "cpu_logger.hpp"
#include "cpu.hpp"
#include "ram/ram.hpp"

#include <ios>		// std::uppercase / std::hex / std::dec
#include <iomanip>	// std::setfill / std::setw
#include <iostream>

std::stringstream nes::CpuLogger::ConstructStreamFromData(const CPU& cpuRef, std::string_view opName, std::uint8_t opSize)
{
	std::uint16_t programCounter = cpuRef.GetProgramCounter();

	std::stringstream stream;

	// Hexadecimal mode
	stream << std::uppercase << std::hex;

	// Every 8-bit value needs to be a 16-bit value to make the output stream
	// treat all 8-bit values as numbers instead of characters
	std::uint16_t A = cpuRef.GetRegister(CPU::RegisterType::A).value;
	std::uint16_t X = cpuRef.GetRegister(CPU::RegisterType::X).value;
	std::uint16_t Y = cpuRef.GetRegister(CPU::RegisterType::Y).value;
	std::uint16_t P = cpuRef.GetRegister(CPU::RegisterType::P).value;
	std::uint16_t SP = cpuRef.GetRegister(CPU::RegisterType::SP).value;

	// Write current address of the program counter
	stream << programCounter << '\t';

	// Display instruction bytes
	for (std::uint8_t i = 0; i < opSize; ++i)
	{
		stream << std::setfill('0') << std::setw(2) << static_cast<std::uint16_t>(cpuRef.ReadRamValueAtAddress(programCounter + i).value) << '\t';
	}

	// An instruction may use up to three bytes
	// Add padding to make lines align nicely
	for (std::uint8_t i = 0; i < 3 - opSize; ++i)
	{
		stream << '\t';
	}
	stream << '\t';

	// Write the instruction's Assembly name
	stream << opName << '\t';

	// Padding
	stream << std::setfill(' ') << std::setw(30);

	// Write register states
	stream << "A:" << std::setfill('0') << std::setw(2) << A << '\t';
	stream << "X:" << std::setfill('0') << std::setw(2) << X << '\t';
	stream << "Y:" << std::setfill('0') << std::setw(2) << Y << '\t';
	stream << "P:" << std::setfill('0') << std::setw(2) << P << '\t';
	stream << "SP:" << SP << '\t';
	stream << "PPU:  " << "     " << '\t';
	stream << "CYC:" << std::dec << cpuRef.GetCurrentCycle();

	return stream;
}
