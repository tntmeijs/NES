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
				BRK(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Logical Inclusive OR
			// -------------------------------------------------------------------
			case 0x01:
				ORA(AddressingMode::IndirectX);
				break;
			
			case 0x05:
				ORA(AddressingMode::ZeroPage);
				break;
			
			case 0x09:
				ORA(AddressingMode::Immediate);
				break;

			case 0x0D:
				ORA(AddressingMode::Absolute);
				break;

			case 0x11:
				ORA(AddressingMode::IndirectY);
				break;

			case 0x15:
				ORA(AddressingMode::ZeroPageX);
				break;

			case 0x19:
				ORA(AddressingMode::AbsoluteY);
				break;

			case 0x1D:
				ORA(AddressingMode::AbsoluteX);
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
			// Push Processor Status
			// -------------------------------------------------------------------
			case 0x08:
				PHP(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Branch if Positive
			// -------------------------------------------------------------------
			case 0x10:
				BPL(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Clear Carry Flag
			// -------------------------------------------------------------------
			case 0x18:
				CLC(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Jump to Subroutine
			// -------------------------------------------------------------------
			case 0x20:
				JSR(AddressingMode::Implicit);
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
			// Pull Processor Status
			// -------------------------------------------------------------------
			case 0x28:
				PLP(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Rotate Left
			// -------------------------------------------------------------------
			case 0x26:
				ROL(AddressingMode::ZeroPage);
				break;

			case 0x2A:
				ROL(AddressingMode::Accumulator);
				break;

			case 0x2E:
				ROL(AddressingMode::Absolute);
				break;

			case 0x36:
				ROL(AddressingMode::ZeroPageX);
				break;

			case 0x3E:
				ROL(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Branch if Minus
			// -------------------------------------------------------------------
			case 0x30:
				BMI(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Set Carry Flag
			// -------------------------------------------------------------------
			case 0x38:
				SEC(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Return from Interrupt
			// -------------------------------------------------------------------
			case 0x40:
				RTI(AddressingMode::Implicit);
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
			// Logical Shift Right
			// -------------------------------------------------------------------
			case 0x46:
				LSR(AddressingMode::ZeroPage);
				break;
			
			case 0x4A:
				LSR(AddressingMode::Accumulator);
				break;

			case 0x4E:
				LSR(AddressingMode::Absolute);
				break;

			case 0x56:
				LSR(AddressingMode::ZeroPageX);
				break;

			case 0x5E:
				LSR(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Push Accumulator
			// -------------------------------------------------------------------
			case 0x48:
				PHA(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Jump
			// -------------------------------------------------------------------
			case 0x4C:
				JMP(AddressingMode::Absolute);
				break;

			case 0x6C:
				JMP(AddressingMode::Indirect);
				break;

			// -------------------------------------------------------------------
			// Branch if Overflow Clear
			// -------------------------------------------------------------------
			case 0x50:
				BVC(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Clear Interrupt Disable
			// -------------------------------------------------------------------
			case 0x58:
				CLI(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Return from Subroutine
			// -------------------------------------------------------------------
			case 0x60:
				RTS(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Pull Accumulator
			// -------------------------------------------------------------------
			case 0x68:
				PLA(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Rotate Right
			// -------------------------------------------------------------------
			case 0x66:
				ROR(AddressingMode::ZeroPage);
				break;

			case 0x6A:
				ROR(AddressingMode::Accumulator);
				break;

			case 0x6E:
				ROR(AddressingMode::Absolute);
				break;

			case 0x76:
				ROR(AddressingMode::ZeroPageX);
				break;

			case 0x7E:
				ROR(AddressingMode::AbsoluteX);
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
			// Branch if Overflow Set
			// -------------------------------------------------------------------
			case 0x70:
				BVS(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Set Interrupt Disable
			// -------------------------------------------------------------------
			case 0x78:
				SEI(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Store Accumulator
			// -------------------------------------------------------------------
			case 0x81:
				STA(AddressingMode::IndirectX);
				break;
			
			case 0x85:
				STA(AddressingMode::ZeroPage);
				break;

			case 0x8D:
				STA(AddressingMode::Absolute);
				break;

			case 0x91:
				STA(AddressingMode::IndirectY);
				break;

			case 0x95:
				STA(AddressingMode::ZeroPageX);
				break;

			case 0x99:
				STA(AddressingMode::AbsoluteY);
				break;

			case 0x9D:
				STA(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Store Y Register
			// -------------------------------------------------------------------
			case 0x84:
				STY(AddressingMode::ZeroPage);
				break;

			case 0x8C:
				STY(AddressingMode::Absolute);
				break;

			case 0x94:
				STY(AddressingMode::ZeroPageX);
				break;

			// -------------------------------------------------------------------
			// Store X Register
			// -------------------------------------------------------------------
			case 0x86:
				STX(AddressingMode::ZeroPage);
				break;

			case 0x8E:
				STX(AddressingMode::Absolute);
				break;

			case 0x96:
				STX(AddressingMode::ZeroPageY);
				break;

			// -------------------------------------------------------------------
			// Decrement Y Register
			// -------------------------------------------------------------------
			case 0x88:
				DEY(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Transfer X to Accumulator
			// -------------------------------------------------------------------
			case 0x8A:
				TXA(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Branch if Carry Clear
			// -------------------------------------------------------------------
			case 0x90:
				BCC(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Transfer Y to Accumulator
			// -------------------------------------------------------------------
			case 0x98:
				TYA(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Transfer X to Stack Pointer
			// -------------------------------------------------------------------
			case 0x9A:
				TXS(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Load Y Register
			// -------------------------------------------------------------------
			case 0xA0:
				LDY(AddressingMode::Immediate);
				break;

			case 0xA4:
				LDY(AddressingMode::ZeroPage);
				break;

			case 0xAC:
				LDY(AddressingMode::Absolute);
				break;

			case 0xB4:
				LDY(AddressingMode::ZeroPageX);
				break;

			case 0xBC:
				LDY(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Load Accumulator
			// -------------------------------------------------------------------
			case 0xA1:
				LDA(AddressingMode::IndirectX);
				break;
			
			case 0xA5:
				LDA(AddressingMode::ZeroPage);
				break;

			case 0xA9:
				LDA(AddressingMode::Immediate);
				break;

			case 0xAD:
				LDA(AddressingMode::Absolute);
				break;

			case 0xB1:
				LDA(AddressingMode::IndirectY);
				break;

			case 0xB5:
				LDA(AddressingMode::ZeroPageX);
				break;

			case 0xB9:
				LDA(AddressingMode::AbsoluteY);
				break;

			case 0xBD:
				LDA(AddressingMode::AbsoluteX);
				break;

			// -------------------------------------------------------------------
			// Load X Register
			// -------------------------------------------------------------------
			case 0xA2:
				LDX(AddressingMode::Immediate);
				break;

			case 0xA6:
				LDX(AddressingMode::ZeroPage);
				break;

			case 0xAE:
				LDX(AddressingMode::Absolute);
				break;

			case 0xB6:
				LDX(AddressingMode::ZeroPageY);
				break;

			case 0xBE:
				LDX(AddressingMode::AbsoluteY);
				break;

			// -------------------------------------------------------------------
			// Transfer Accumulator to Y
			// -------------------------------------------------------------------
			case 0xA8:
				TAY(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Transfer Accumulator to X
			// -------------------------------------------------------------------
			case 0xAA:
				TAX(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Branch if Carry Set
			// -------------------------------------------------------------------
			case 0xB0:
				BCS(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Clear Overflow Flag
			// -------------------------------------------------------------------
			case 0xB8:
				CLV(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Transfer Stack Pointer to X
			// -------------------------------------------------------------------
			case 0xBA:
				TSX(AddressingMode::Implicit);

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
				DEX(AddressingMode::Implicit);
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
				INY(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Branch if not Equal
			// -------------------------------------------------------------------
			case 0xD0:
				BNE(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Clear Decimal Mode
			// -------------------------------------------------------------------
			case 0xD8:
				CLD(AddressingMode::Implicit);
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
			// Subtract with Carry
			// -------------------------------------------------------------------
			case 0xE1:
				SBC(AddressingMode::IndirectX);
				break;

			case 0xE5:
				SBC(AddressingMode::ZeroPage);
				break;

			case 0xE9:
				SBC(AddressingMode::Immediate);
				break;

			case 0xED:
				SBC(AddressingMode::Absolute);
				break;

			case 0xF1:
				SBC(AddressingMode::IndirectY);
				break;

			case 0xF5:
				SBC(AddressingMode::ZeroPageX);
				break;

			case 0xFD:
				SBC(AddressingMode::AbsoluteX);
				break;

			case 0xF9:
				SBC(AddressingMode::AbsoluteY);
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
				INX(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// No Operation
			// -------------------------------------------------------------------
			case 0xEA:
				NOP(AddressingMode::Implicit);
				break;

			// -------------------------------------------------------------------
			// Branch if Equal
			// -------------------------------------------------------------------
			case 0xF0:
				BEQ(AddressingMode::Relative);
				break;

			// -------------------------------------------------------------------
			// Set Carry Flag
			// -------------------------------------------------------------------
			case 0xF8:
				SED(AddressingMode::Implicit);
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

void nes::CPU::BCC(AddressingMode mode)
{
	std::cout << "OP BCC" << '\n';
}

void nes::CPU::BCS(AddressingMode mode)
{
	std::cout << "OP BCS" << '\n';
}

void nes::CPU::BEQ(AddressingMode mode)
{
	std::cout << "OP BEQ" << '\n';
}

void nes::CPU::BIT(AddressingMode mode)
{
	std::cout << "OP BIT" << '\n';
}

void nes::CPU::BMI(AddressingMode mode)
{
	std::cout << "OP BMI" << '\n';
}

void nes::CPU::BNE(AddressingMode mode)
{
	std::cout << "OP BNE" << '\n';
}

void nes::CPU::BPL(AddressingMode mode)
{
	std::cout << "OP BPL" << '\n';
}

void nes::CPU::BRK(AddressingMode mode)
{
	std::cout << "OP BRK" << '\n';
}

void nes::CPU::BVC(AddressingMode mode)
{
	std::cout << "OP BVC" << '\n';
}

void nes::CPU::BVS(AddressingMode mode)
{
	std::cout << "OP BVS" << '\n';
}

void nes::CPU::CLC(AddressingMode mode)
{
	std::cout << "OP CLC" << '\n';

	P &= ~(1 << 0);
}

void nes::CPU::CLD(AddressingMode mode)
{
	std::cout << "OP CLC" << '\n';

	P &= ~(1 << 3);
}

void nes::CPU::CLI(AddressingMode mode)
{
	std::cout << "OP CLI" << '\n';

	P &= ~(1 << 2);
}

void nes::CPU::CLV(AddressingMode mode)
{
	std::cout << "OP CLV" << '\n';

	P &= ~(1 << 6);
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

void nes::CPU::DEX(AddressingMode mode)
{
	std::cout << "OP DEX" << '\n';

	// Decrement X
	X -= 1;

	if (X == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else if ((X & (1 << 7)) != 0)
	{
		// Value is negative, set negative flag
		P |= (1 << 7);
	}
	else
	{
		// Value is positive, unset negative flag
		P &= ~(1 << 7);
	}
}

void nes::CPU::DEY(AddressingMode mode)
{
	std::cout << "OP DEY" << '\n';

	// Decrement Y
	Y -= 1;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else if ((Y & (1 << 7)) != 0)
	{
		// Value is negative, set negative flag
		P |= (1 << 7);
	}
	else
	{
		// Value is positive, unset negative flag
		P &= ~(1 << 7);
	}
}

void nes::CPU::EOR(AddressingMode mode)
{
	std::cout << "OP EOR" << '\n';
}

void nes::CPU::INC(AddressingMode mode)
{
	std::cout << "OP INC" << '\n';
}

void nes::CPU::INX(AddressingMode mode)
{
	std::cout << "OP INX" << '\n';
}

void nes::CPU::INY(AddressingMode mode)
{
	std::cout << "OP INY" << '\n';
}

void nes::CPU::JMP(AddressingMode mode)
{
	std::cout << "OP JMP" << '\n';
}

void nes::CPU::JSR(AddressingMode mode)
{
	std::cout << "OP JSR" << '\n';
}

void nes::CPU::LDA(AddressingMode mode)
{
	std::cout << "OP LDA" << '\n';
}

void nes::CPU::LDX(AddressingMode mode)
{
	std::cout << "OP LDY" << '\n';
}

void nes::CPU::LDY(AddressingMode mode)
{
	std::cout << "OP LDY" << '\n';
}

void nes::CPU::LSR(AddressingMode mode)
{
	std::cout << "OP LSR" << '\n';
}

void nes::CPU::NOP(AddressingMode mode)
{
	std::cout << "OP NOP" << '\n';
}

void nes::CPU::ORA(AddressingMode mode)
{
	std::cout << "OP ORA" << '\n';
}

void nes::CPU::PHA(AddressingMode mode)
{
	std::cout << "OP PHA" << '\n';
}

void nes::CPU::PHP(AddressingMode mode)
{
	std::cout << "OP PHP" << '\n';
}

void nes::CPU::PLA(AddressingMode mode)
{
	std::cout << "OP PLA" << '\n';
}

void nes::CPU::PLP(AddressingMode mode)
{
	std::cout << "OP PLP" << '\n';
}

void nes::CPU::ROL(AddressingMode mode)
{
	std::cout << "OP ROL" << '\n';
}

void nes::CPU::ROR(AddressingMode mode)
{
	std::cout << "OP ROR" << '\n';
}

void nes::CPU::RTI(AddressingMode mode)
{
	std::cout << "OP RTI" << '\n';
}

void nes::CPU::RTS(AddressingMode mode)
{
	std::cout << "OP RTS" << '\n';
}

void nes::CPU::SBC(AddressingMode mode)
{
	std::cout << "OP SBC" << '\n';
}

void nes::CPU::SEC(AddressingMode mode)
{
	std::cout << "OP SEC" << '\n';
}

void nes::CPU::SED(AddressingMode mode)
{
	std::cout << "OP SED" << '\n';
}

void nes::CPU::SEI(AddressingMode mode)
{
	std::cout << "OP SEI" << '\n';
}

void nes::CPU::STA(AddressingMode mode)
{
	std::cout << "OP STA" << '\n';
}

void nes::CPU::STX(AddressingMode mode)
{
	std::cout << "OP STX" << '\n';
}

void nes::CPU::STY(AddressingMode mode)
{
	std::cout << "OP STY" << '\n';
}

void nes::CPU::TAX(AddressingMode mode)
{
	std::cout << "OP TAX" << '\n';
}

void nes::CPU::TAY(AddressingMode mode)
{
	std::cout << "OP TAY" << '\n';
}

void nes::CPU::TSX(AddressingMode mode)
{
	std::cout << "OP TSX" << '\n';
}

void nes::CPU::TXA(AddressingMode mode)
{
	std::cout << "OP TXA" << '\n';
}

void nes::CPU::TXS(AddressingMode mode)
{
	std::cout << "OP TXS" << '\n';
}

void nes::CPU::TYA(AddressingMode mode)
{
	std::cout << "OP TYA" << '\n';
}
