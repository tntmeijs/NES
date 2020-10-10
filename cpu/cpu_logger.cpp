#include "cpu_logger.hpp"
#include "cpu.hpp"
#include "ram/ram.hpp"

#include <ios>		// std::uppercase / std::hex / std::dec
#include <iomanip>	// std::setfill / std::setw
#include <iostream>
#include <sstream>

nes::CpuLogger::CpuLogger(const CPU& cpuRef, const RAM& ramRef) :
	CpuRef(cpuRef),
	RamRef(ramRef)
{
	LogFile = std::ofstream("cpu_log.log", std::ios::out | std::ios::trunc);
}

nes::CpuLogger::~CpuLogger()
{
	if (LogFile.is_open())
	{
		LogFile.close();
	}
}

void nes::CpuLogger::LogOperation(std::string_view name, std::uint8_t num)
{
	std::uint16_t programCounter = CpuRef.GetProgramCounter();

	std::stringstream stream;

	// Hexadecimal mode
	stream << std::uppercase << std::hex;

	// Every 8-bit value is a 16-bit value to make the output stream treat all
	// 8-bit values as numbers instead of characters
	std::uint16_t A = CpuRef.GetRegister(CPU::RegisterType::A);
	std::uint16_t X = CpuRef.GetRegister(CPU::RegisterType::X);
	std::uint16_t Y = CpuRef.GetRegister(CPU::RegisterType::Y);
	std::uint16_t P = CpuRef.GetRegister(CPU::RegisterType::P);
	std::uint16_t SP = CpuRef.GetRegister(CPU::RegisterType::SP);

	// Write current address of the program counter
	stream << programCounter << "  ";

	// Display instruction bytes
	for (std::uint8_t i = 0; i < num; ++i)
	{
		stream << std::setfill('0') << std::setw(2) << static_cast<std::uint16_t>(RamRef.ReadByte(programCounter + i)) << ' ';
	}

	// An instruction may use up to three bytes
	// Add padding to make lines align nicely
	for (std::uint8_t i = 0; i < 3 - num; ++i)
	{
		stream << "   ";
	}
	stream << ' ';

	// Write the instruction's Assembly name
	stream << name << '\t';

	// Padding
	stream << std::setfill(' ') << std::setw(30);

	// Write register states
	stream << "A:" << std::setfill('0') << std::setw(2) << A << ' ';
	stream << "X:" << std::setfill('0') << std::setw(2) << X << ' ';
	stream << "Y:" << std::setfill('0') << std::setw(2) << Y << ' ';
	stream << "P:" << std::setfill('0') << std::setw(2) << P << ' ';
	stream << "SP:" << SP << ' ';
	stream << "PPU:  " << "     " << ' ';
	stream << "CYC:" << std::dec << CpuRef.GetCurrentCycle();

	// Output to the console window
	std::cout << stream.str() << std::endl;

	// Output to the log file
	LogFile << stream.str() << std::endl;
}
