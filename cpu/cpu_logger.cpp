#include "cpu_logger.hpp"
#include "cpu.hpp"
#include "ram/ram.hpp"

#include <ios> // std::hex / std::dec

nes::CpuLogger::CpuLogger(const CPU& cpuRef, const RAM& ramRef) :
	CpuRef(cpuRef),
	RamRef(ramRef)
{}

bool nes::CpuLogger::Initialize()
{
	// Attempt to open a new file
	OutputFile.open("./cpu_log.csv", std::ios_base::out | std::ios_base::trunc);
	if (OutputFile.is_open())
	{
		// Write CSV header and flush on newline
		OutputFile << "PC,Byte 0,Byte 1,Byte 2,Name,A,X,Y,P,SP" << std::endl;

		return true;
	}

	// Something is not right, attempt to close any remaining file handles
	OutputFile.close();
	return false;
}

void nes::CpuLogger::FlushAndClose()
{
	OutputFile.flush();
	OutputFile.close();
}

void nes::CpuLogger::LogOperation(std::string_view name, std::uint8_t num)
{
	std::uint16_t programCounter = CpuRef.GetProgramCounter();

	// Hexadecimal mode
	OutputFile << std::hex;

	// Every 8-bit value is a 16-bit value to make the output stream treat all
	// 8-bit values as numbers instead of characters
	std::uint16_t A = CpuRef.GetRegister(CPU::RegisterType::A);
	std::uint16_t X = CpuRef.GetRegister(CPU::RegisterType::X);
	std::uint16_t Y = CpuRef.GetRegister(CPU::RegisterType::Y);
	std::uint16_t P = CpuRef.GetRegister(CPU::RegisterType::P);
	std::uint16_t SP = CpuRef.GetRegister(CPU::RegisterType::SP);

	// Write current address of the program counter
	OutputFile << programCounter << ',';

	// Display instruction bytes
	for (std::uint8_t i = 0; i < num; ++i)
	{
		OutputFile << static_cast<std::uint16_t>(RamRef.ReadByte(programCounter + i)) << ',';
	}

	// An instruction may use up to three bytes
	// To make the CSV file align properly, pad the unused bytes
	for (std::uint8_t i = 0; i < 3 - num; ++i)
	{
		OutputFile << ',';
	}

	// Write the instruction's Assembly name
	OutputFile << name << ',';

	// Write register states
	OutputFile << "A: " << A << ',';
	OutputFile << "X: " << X << ',';
	OutputFile << "Y: " << Y << ',';
	OutputFile << "P: " << P << ',';
	OutputFile << "SP: " << SP << ',';
	OutputFile << "PPU: " << "NOT IMPLEMENTED" << ',';
	OutputFile << "CYC: " << CpuRef.GetCurrentCycle();

	// End of line and flush
	OutputFile << std::endl;
}
