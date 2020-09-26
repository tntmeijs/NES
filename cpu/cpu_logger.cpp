#include "cpu_logger.hpp"
#include "cpu.hpp"
#include "ram/ram.hpp"

#include <ios> // std::hex / std::dec
#include <iostream>

nes::CpuLogger::CpuLogger(const CPU& cpuRef, const RAM& ramRef) :
	CpuRef(cpuRef),
	RamRef(ramRef)
{}

void nes::CpuLogger::LogOperation(std::string_view name, std::uint8_t num)
{
	std::uint16_t programCounter = CpuRef.GetProgramCounter();

	// Hexadecimal mode
	std::cout << std::hex;

	// Every 8-bit value is a 16-bit value to make the output stream treat all
	// 8-bit values as numbers instead of characters
	std::uint16_t A = CpuRef.GetRegister(CPU::RegisterType::A);
	std::uint16_t X = CpuRef.GetRegister(CPU::RegisterType::X);
	std::uint16_t Y = CpuRef.GetRegister(CPU::RegisterType::Y);
	std::uint16_t P = CpuRef.GetRegister(CPU::RegisterType::P);
	std::uint16_t SP = CpuRef.GetRegister(CPU::RegisterType::SP);

	// Write current address of the program counter
	std::cout << programCounter << '\t';

	// Display instruction bytes
	for (std::uint8_t i = 0; i < num; ++i)
	{
		std::cout << static_cast<std::uint16_t>(RamRef.ReadByte(programCounter + i)) << '\t';
	}

	// An instruction may use up to three bytes
	// To make the CSV file align properly, pad the unused bytes
	for (std::uint8_t i = 0; i < 3 - num; ++i)
	{
		std::cout << '\t';
	}

	// Write the instruction's Assembly name
	std::cout << name << '\t';

	// Write register states
	std::cout << "A: " << A << '\t';
	std::cout << "X: " << X << '\t';
	std::cout << "Y: " << Y << '\t';
	std::cout << "P: " << P << '\t';
	std::cout << "SP: " << SP << '\t';
	std::cout << "PPU: " << "NOT IMPLEMENTED" << '\t';
	std::cout << "CYC: " << std::dec << CpuRef.GetCurrentCycle();

	// End of line and flush
	std::cout << std::endl;
}
