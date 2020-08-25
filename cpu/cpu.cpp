#include "cpu.hpp"

#include <iostream>
#include <fstream>

void nes::CPU::Entry()
{
	// Reset registers and counters
	A = X = Y = P = S = PC = 0;

	// Grab a test rom (hard-coded location, fine for now
	std::ifstream rom("D:/6502_functional_test.bin", std::ios_base::binary | std::ios_base::in);

	if (!rom.is_open())
	{
		std::cerr << "Unable to open test ROM." << std::endl;
	}

	rom.seekg(0, rom.end);
	size_t romSize = rom.tellg();
	rom.seekg(0, rom.beg);

	Memory = new std::uint8_t[romSize];

	// Dump the entire binary blob
	rom.read(reinterpret_cast<char*>(Memory), romSize);
	rom.close();

	// Start reading at PC = 0x0400
	PC = 0x0400;

	// Ugly opcode switch
	//#TODO: use a function table to tidy this up a little
	while (true)
	{
		std::uint8_t opCode = Memory[PC++];
		switch (opCode)
		{
			// -------------------------------------------------------------------
			// Arithmetic Shift Left
			// -------------------------------------------------------------------
			case 0x06:
				ASL(AddressingMode::ZeroPage);
				break;

			case 0x0A:
				ASL(AddressingMode::Accumulator);
				break;

			case 0x0E:
				ASL(AddressingMode::Absolute);
				break;

			case 0x16:
				ASL(AddressingMode::ZeroPageX);
				break;

			case 0x1E:
				ASL(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Logical AND
			// -------------------------------------------------------------------
			case 0x21:
				AND(AddressingMode::IndirectX);
				break;

			case 0x25:
				AND(AddressingMode::ZeroPage);
				break;

			case 0x29:
				AND(AddressingMode::Immediate);
				break;

			case 0x2D:
				AND(AddressingMode::Absolute);
				break;

			case 0x31:
				AND(AddressingMode::IndirectY);
				break;

			case 0x35:
				AND(AddressingMode::ZeroPageX);
				break;

			case 0x39:
				AND(AddressingMode::AbsoluteY);
				break;

			case 0x3D:
				AND(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Add with Carry
			// -------------------------------------------------------------------
			case 0x61:
				ADC(AddressingMode::IndirectX);
				break;

			case 0x65:
				ADC(AddressingMode::ZeroPage);
				break;

			case 0x69:
				ADC(AddressingMode::Immediate);
				break;

			case 0x6D:
				ADC(AddressingMode::Absolute);
				break;

			case 0x71:
				ADC(AddressingMode::IndirectY);
				break;

			case 0x75:
				ADC(AddressingMode::ZeroPageX);
				break;

			case 0x79:
				ADC(AddressingMode::AbsoluteY);
				break;

			case 0x7D:
				ADC(AddressingMode::AbsoluteX);
				break;

			default:
				break;
		}
	}

	delete[] Memory;
}

// DEBUG FUNCTION, PRINT A BYTE
void PrintByte(std::uint8_t byte)
{
	for (int i = 7; i >= 0; --i)
	{
		std::cout << ((byte & (1 << i)) != 0) ? '1' : '0';
	}
}

char nes::CPU::ReadAtPC()
{
	PrintByte(Memory[PC]);

	return 0;
}

void nes::CPU::ADC(AddressingMode mode)
{
	std::cout << "OP ADC" << '\n';
}

void nes::CPU::AND(AddressingMode mode)
{
	std::cout << "OP AND" << '\n';
}

void nes::CPU::ASL(AddressingMode mode)
{
	std::cout << "OP ASL" << '\n';
}
