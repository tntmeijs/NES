#include "cpu_logger.hpp"
#include "cpu.hpp"
#include "ram/ram.hpp"

#include <ios> // std::uppercase / std::hex / std::dec
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
	stream << programCounter << '\t';

	// Display instruction bytes
	for (std::uint8_t i = 0; i < num; ++i)
	{
		stream << static_cast<std::uint16_t>(RamRef.ReadByte(programCounter + i)) << '\t';
	}

	// An instruction may use up to three bytes
	// To make the CSV file align properly, pad the unused bytes
	for (std::uint8_t i = 0; i < 3 - num; ++i)
	{
		stream << '\t';
	}

	// Write the instruction's Assembly name
	stream << name << '\t';

	// Write register states
	stream << "A: " << A << '\t';
	stream << "X: " << X << '\t';
	stream << "Y: " << Y << '\t';
	stream << "P: " << P << '\t';
	stream << "SP: " << SP << '\t';
	stream << "PPU: " << "NOT IMPLEMENTED" << '\t';
	stream << "CYC: " << std::dec << CpuRef.GetCurrentCycle();

	// Output to the console window
	std::cout << stream.str() << std::endl;

	// Output to the log file
	LogFile << stream.str() << std::endl;
}
