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
			// Force Interrupt
			// -------------------------------------------------------------------
			case 0x00:
				BRK();
				break;

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
			// Branch if Positive
			// -------------------------------------------------------------------
			case 0x10:
				BPL();
				break;

			// -------------------------------------------------------------------
			// Clear Carry Flag
			// -------------------------------------------------------------------
			case 0x18:
				CLC();
				break;

			// -------------------------------------------------------------------
			// BIT
			// -------------------------------------------------------------------
			case 0x24:
				BIT(AddressingMode::ZeroPage);
				break;

			case 0x2C:
				BIT(AddressingMode::Absolute);
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
			// Branch if Minus
			// -------------------------------------------------------------------
			case 0x30:
				BMI();
				break;

			// -------------------------------------------------------------------
			// Exclusive OR
			// -------------------------------------------------------------------
			case 0x41:
				EOR(AddressingMode::IndirectX);
				break;

			case 0x45:
				EOR(AddressingMode::ZeroPage);
				break;

			case 0x49:
				EOR(AddressingMode::Immediate);
				break;

			case 0x4D:
				EOR(AddressingMode::Absolute);
				break;

			case 0x51:
				EOR(AddressingMode::IndirectY);
				break;

			case 0x55:
				EOR(AddressingMode::ZeroPageX);
				break;

			case 0x59:
				EOR(AddressingMode::AbsoluteY);
				break;

			case 0x5D:
				EOR(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Branch if Overflow Clear
			// -------------------------------------------------------------------
			case 0x50:
				BVC();
				break;

			// -------------------------------------------------------------------
			// Clear Interrupt Disable
			// -------------------------------------------------------------------
			case 0x58:
				CLI();
				break;

			// -------------------------------------------------------------------
			// Branch if Overflow Set
			// -------------------------------------------------------------------
			case 0x70:
				BVS();
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

			// -------------------------------------------------------------------
			// Decrement Y Register
			// -------------------------------------------------------------------
			case 0x88:
				DEY();
				break;

			// -------------------------------------------------------------------
			// Branch if Carry Clear
			// -------------------------------------------------------------------
			case 0x90:
				BCC();
				break;

			// -------------------------------------------------------------------
			// Branch if Carry Set
			// -------------------------------------------------------------------
			case 0xB0:
				BCS();
				break;

			// -------------------------------------------------------------------
			// Clear Overflow Flag
			// -------------------------------------------------------------------
			case 0xB8:
				CLV();
				break;

			// -------------------------------------------------------------------
			// Compare
			// -------------------------------------------------------------------
			case 0xC1:
				CMP(AddressingMode::IndirectX);
				break;

			case 0xC5:
				CMP(AddressingMode::ZeroPage);
				break;

			case 0xC9:
				CMP(AddressingMode::Immediate);
				break;

			case 0xCD:
				CMP(AddressingMode::Absolute);
				break;

			case 0xD1:
				CMP(AddressingMode::IndirectY);
				break;

			case 0xD5:
				CMP(AddressingMode::ZeroPageX);
				break;

			case 0xD9:
				CMP(AddressingMode::AbsoluteY);
				break;

			case 0xDD:
				CMP(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Decrement Memory
			// -------------------------------------------------------------------
			case 0xC6:
				DEC(AddressingMode::ZeroPage);
				break;

			case 0xD6:
				DEC(AddressingMode::ZeroPageX);
				break;

			case 0xCE:
				DEC(AddressingMode::Absolute);
				break;

			case 0xDE:
				DEC(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Decrement X Register
			// -------------------------------------------------------------------
			case 0xCA:
				DEX();
				break;

			// -------------------------------------------------------------------
			// Compare Y Register
			// -------------------------------------------------------------------
			case 0xC0:
				CPY(AddressingMode::Immediate);
				break;

			case 0xC4:
				CPY(AddressingMode::ZeroPage);
				break;

			case 0xCC:
				CPY(AddressingMode::Absolute);

			// -------------------------------------------------------------------
			// Increment Y Register
			// -------------------------------------------------------------------
			case 0xC8:
				INY();
				break;

			// -------------------------------------------------------------------
			// Branch if not Equal
			// -------------------------------------------------------------------
			case 0xD0:
				BNE();
				break;

			// -------------------------------------------------------------------
			// Clear Decimal Mode
			// -------------------------------------------------------------------
			case 0xD8:
				CLD();
				break;

			// -------------------------------------------------------------------
			// Compare X Register
			// -------------------------------------------------------------------
			case 0xE0:
				CPX(AddressingMode::Immediate);
				break;

			case 0xE4:
				CPX(AddressingMode::ZeroPage);
				break;

			case 0xEC:
				CPX(AddressingMode::Absolute);
				break;

			// -------------------------------------------------------------------
			// Increment Memory
			// -------------------------------------------------------------------
			case 0xE6:
				INC(AddressingMode::ZeroPage);
				break;

			case 0xF6:
				INC(AddressingMode::ZeroPageX);
				break;

			case 0xEE:
				INC(AddressingMode::Absolute);
				break;

			case 0xFE:
				INC(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Increment X Register
			// -------------------------------------------------------------------
			case 0xE8:
				INX();
				break;

			// -------------------------------------------------------------------
			// Branch if Equal
			// -------------------------------------------------------------------
			case 0xF0:
				BEQ();
				break;

			default:
				std::cerr << "Unknown op-code: " << std::hex << opCode << '\n';
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

void nes::CPU::BCC()
{
	std::cout << "OP BCC" << '\n';
}

void nes::CPU::BCS()
{
	std::cout << "OP BCS" << '\n';
}

void nes::CPU::BEQ()
{
	std::cout << "OP BEQ" << '\n';
}

void nes::CPU::BIT(AddressingMode mode)
{
	std::cout << "OP BIT" << '\n';
}

void nes::CPU::BMI()
{
	std::cout << "OP BMI" << '\n';
}

void nes::CPU::BNE()
{
	std::cout << "OP BNE" << '\n';
}

void nes::CPU::BPL()
{
	std::cout << "OP BPL" << '\n';
}

void nes::CPU::BRK()
{
	std::cout << "OP BRK" << '\n';
}

void nes::CPU::BVC()
{
	std::cout << "OP BVC" << '\n';
}

void nes::CPU::BVS()
{
	std::cout << "OP BVS" << '\n';
}

void nes::CPU::CLC()
{
	std::cout << "OP CLC" << '\n';
}

void nes::CPU::CLD()
{
	std::cout << "OP CLC" << '\n';
}

void nes::CPU::CLI()
{
	std::cout << "OP CLI" << '\n';
}

void nes::CPU::CLV()
{
	std::cout << "OP CLV" << '\n';
}

void nes::CPU::CMP(AddressingMode mode)
{
	std::cout << "OP CMP" << '\n';
}

void nes::CPU::CPX(AddressingMode mode)
{
	std::cout << "OP CPX" << '\n';
}

void nes::CPU::CPY(AddressingMode mode)
{
	std::cout << "OP CPY" << '\n';
}

void nes::CPU::DEC(AddressingMode mode)
{
	std::cout << "OP DEC" << '\n';
}

void nes::CPU::DEX()
{
	std::cout << "OP DEX" << '\n';
}

void nes::CPU::DEY()
{
	std::cout << "OP DEY" << '\n';
}

void nes::CPU::EOR(AddressingMode mode)
{
	std::cout << "OP EOR" << '\n';
}

void nes::CPU::INC(AddressingMode mode)
{
	std::cout << "OP INC" << '\n';
}

void nes::CPU::INX()
{
	std::cout << "OP INX" << '\n';
}

void nes::CPU::INY()
{
	std::cout << "OP INY" << '\n';
}
