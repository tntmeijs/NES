#include "cpu.hpp"
#include "ram/ram.hpp"

#include <iostream>
#include <fstream>

nes::CPU::CPU(RAM& ramRef) :
	A(0),
	X(0),
	Y(0),
	P(0),
	SP(0),
	PC(0),
	RamRef(ramRef),
	Logger(*this, ramRef),
	CurrentCycle(0)
{
	// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
	P = 0x24;
	SP = 0xFD;

	// http://forum.6502.org/viewtopic.php?f=4&t=5704#:~:text=On%20the%206502%2C%20the%20reset,all%20interrupts)%20takes%207%20cycles.
	CurrentCycle = 7;
}

void nes::CPU::SetProgramCounterToResetVector()
{
	// The low byte of the reset vector address is stored at 0xFFFD
	// The high byte of the reset vector address is stored at 0xFFFC
	std::uint8_t msb = RamRef.ReadByte(0xFFFD);
	std::uint8_t lsb = RamRef.ReadByte(0xFFFC);

	// Combine the low and high components into a 16 bit address
	// Note that the NES is a little-endian system
	PC = ((msb << 8) | lsb);
}

void nes::CPU::SetProgramCounterToAddress(std::uint16_t address)
{
	PC = address;
}

void nes::CPU::ExecuteInstruction()
{
	std::uint8_t opCode = RamRef.ReadByte(PC);
	ProcessOpCode(opCode);
}

void nes::CPU::MoveProgramCounter(std::int32_t offset)
{
	PC += offset;
}

std::uint16_t nes::CPU::GetProgramCounter() const
{
	return PC;
}

std::uint8_t nes::CPU::GetRegister(RegisterType type) const
{
	switch (type)
	{
		case nes::CPU::RegisterType::A:
			return A;
			break;
		case nes::CPU::RegisterType::X:
			return X;
			break;
		case nes::CPU::RegisterType::Y:
			return Y;
			break;
		case nes::CPU::RegisterType::P:
			return P;
			break;
		case nes::CPU::RegisterType::SP:
			return SP;
			break;
		default:
			return 0;
			break;
	}
}

std::uint64_t nes::CPU::GetCurrentCycle() const
{
	return CurrentCycle;
}

void nes::CPU::ProcessOpCode(std::uint8_t opCode)
{
	switch (opCode)
	{
		// -------------------------------------------------------------------
		// Force Interrupt
		// -------------------------------------------------------------------
		case 0x00:
			Logger.LogOperation("BRK", 1);
			BRK(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Logical Inclusive OR
			// -------------------------------------------------------------------
		case 0x01:
			Logger.LogOperation("ORA", 2);
			ORA(AddressingMode::IndirectX);
			break;

		case 0x05:
			Logger.LogOperation("ORA", 2);
			ORA(AddressingMode::ZeroPage);
			break;

		case 0x09:
			Logger.LogOperation("ORA", 2);
			ORA(AddressingMode::Immediate);
			break;

		case 0x0D:
			Logger.LogOperation("ORA", 3);
			ORA(AddressingMode::Absolute);
			break;

		case 0x11:
			Logger.LogOperation("ORA", 2);
			ORA(AddressingMode::IndirectY);
			break;

		case 0x15:
			Logger.LogOperation("ORA", 2);
			ORA(AddressingMode::ZeroPageX);
			break;

		case 0x19:
			Logger.LogOperation("ORA", 3);
			ORA(AddressingMode::AbsoluteY);
			break;

		case 0x1D:
			Logger.LogOperation("ORA", 3);
			ORA(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Arithmetic Shift Left
			// -------------------------------------------------------------------
		case 0x06:
			Logger.LogOperation("ASL", 2);
			ASL(AddressingMode::ZeroPage);
			break;

		case 0x0A:
			Logger.LogOperation("ASL", 1);
			ASL(AddressingMode::Accumulator);
			break;

		case 0x0E:
			Logger.LogOperation("ASL", 3);
			ASL(AddressingMode::Absolute);
			break;

		case 0x16:
			Logger.LogOperation("ASL", 2);
			ASL(AddressingMode::ZeroPageX);
			break;

		case 0x1E:
			Logger.LogOperation("ASL", 3);
			ASL(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Push Processor Status
			// -------------------------------------------------------------------
		case 0x08:
			Logger.LogOperation("PHP", 1);
			PHP(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Branch if Positive
			// -------------------------------------------------------------------
		case 0x10:
			Logger.LogOperation("BPL", 2);
			BPL(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Clear Carry Flag
			// -------------------------------------------------------------------
		case 0x18:
			Logger.LogOperation("CLC", 1);
			CLC(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Jump to Subroutine
			// -------------------------------------------------------------------
		case 0x20:
			Logger.LogOperation("JSR", 3);
			JSR(AddressingMode::Absolute);
			break;

			// -------------------------------------------------------------------
			// BIT
			// -------------------------------------------------------------------
		case 0x24:
			Logger.LogOperation("BIT", 2);
			BIT(AddressingMode::ZeroPage);
			break;

		case 0x2C:
			Logger.LogOperation("BIT", 3);
			BIT(AddressingMode::Absolute);
			break;

			// -------------------------------------------------------------------
			// Logical AND
			// -------------------------------------------------------------------
		case 0x21:
			Logger.LogOperation("AND", 2);
			AND(AddressingMode::IndirectX);
			break;

		case 0x25:
			Logger.LogOperation("AND", 2);
			AND(AddressingMode::ZeroPage);
			break;

		case 0x29:
			Logger.LogOperation("AND", 2);
			AND(AddressingMode::Immediate);
			break;

		case 0x2D:
			Logger.LogOperation("AND", 3);
			AND(AddressingMode::Absolute);
			break;

		case 0x31:
			Logger.LogOperation("AND", 2);
			AND(AddressingMode::IndirectY);
			break;

		case 0x35:
			Logger.LogOperation("AND", 2);
			AND(AddressingMode::ZeroPageX);
			break;

		case 0x39:
			Logger.LogOperation("AND", 3);
			AND(AddressingMode::AbsoluteY);
			break;

		case 0x3D:
			Logger.LogOperation("AND", 3);
			AND(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Pull Processor Status
			// -------------------------------------------------------------------
		case 0x28:
			Logger.LogOperation("PLP", 1);
			PLP(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Rotate Left
			// -------------------------------------------------------------------
		case 0x26:
			Logger.LogOperation("ROL", 2);
			ROL(AddressingMode::ZeroPage);
			break;

		case 0x2A:
			Logger.LogOperation("ROL", 1);
			ROL(AddressingMode::Accumulator);
			break;

		case 0x2E:
			Logger.LogOperation("ROL", 3);
			ROL(AddressingMode::Absolute);
			break;

		case 0x36:
			Logger.LogOperation("ROL", 2);
			ROL(AddressingMode::ZeroPageX);
			break;

		case 0x3E:
			Logger.LogOperation("ROL", 3);
			ROL(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Branch if Minus
			// -------------------------------------------------------------------
		case 0x30:
			Logger.LogOperation("BMI", 2);
			BMI(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Set Carry Flag
			// -------------------------------------------------------------------
		case 0x38:
			Logger.LogOperation("SEC", 1);
			SEC(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Return from Interrupt
			// -------------------------------------------------------------------
		case 0x40:
			Logger.LogOperation("RTI", 1);
			RTI(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Exclusive OR
			// -------------------------------------------------------------------
		case 0x41:
			Logger.LogOperation("EOR", 2);
			EOR(AddressingMode::IndirectX);
			break;

		case 0x45:
			Logger.LogOperation("EOR", 2);
			EOR(AddressingMode::ZeroPage);
			break;

		case 0x49:
			Logger.LogOperation("EOR", 2);
			EOR(AddressingMode::Immediate);
			break;

		case 0x4D:
			Logger.LogOperation("EOR", 3);
			EOR(AddressingMode::Absolute);
			break;

		case 0x51:
			Logger.LogOperation("EOR", 2);
			EOR(AddressingMode::IndirectY);
			break;

		case 0x55:
			Logger.LogOperation("EOR", 2);
			EOR(AddressingMode::ZeroPageX);
			break;

		case 0x59:
			Logger.LogOperation("EOR", 3);
			EOR(AddressingMode::AbsoluteY);
			break;

		case 0x5D:
			Logger.LogOperation("EOR", 3);
			EOR(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Logical Shift Right
			// -------------------------------------------------------------------
		case 0x46:
			Logger.LogOperation("LSR", 2);
			LSR(AddressingMode::ZeroPage);
			break;

		case 0x4A:
			Logger.LogOperation("LSR", 1);
			LSR(AddressingMode::Accumulator);
			break;

		case 0x4E:
			Logger.LogOperation("LSR", 3);
			LSR(AddressingMode::Absolute);
			break;

		case 0x56:
			Logger.LogOperation("LSR", 2);
			LSR(AddressingMode::ZeroPageX);
			break;

		case 0x5E:
			Logger.LogOperation("LSR", 3);
			LSR(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Push Accumulator
			// -------------------------------------------------------------------
		case 0x48:
			Logger.LogOperation("PHA", 1);
			PHA(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Jump
			// -------------------------------------------------------------------
		case 0x4C:
			Logger.LogOperation("JMP", 3);
			JMP(AddressingMode::Absolute);
			break;

		case 0x6C:
			Logger.LogOperation("JMP", 3);
			JMP(AddressingMode::Indirect);
			break;

			// -------------------------------------------------------------------
			// Branch if Overflow Clear
			// -------------------------------------------------------------------
		case 0x50:
			Logger.LogOperation("BVC", 2);
			BVC(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Clear Interrupt Disable
			// -------------------------------------------------------------------
		case 0x58:
			Logger.LogOperation("CLI", 1);
			CLI(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Return from Subroutine
			// -------------------------------------------------------------------
		case 0x60:
			Logger.LogOperation("RTS", 1);
			RTS(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Pull Accumulator
			// -------------------------------------------------------------------
		case 0x68:
			Logger.LogOperation("PLA", 3);
			PLA(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Rotate Right
			// -------------------------------------------------------------------
		case 0x66:
			Logger.LogOperation("ROR", 2);
			ROR(AddressingMode::ZeroPage);
			break;

		case 0x6A:
			Logger.LogOperation("ROR", 1);
			ROR(AddressingMode::Accumulator);
			break;

		case 0x6E:
			Logger.LogOperation("ROR", 3);
			ROR(AddressingMode::Absolute);
			break;

		case 0x76:
			Logger.LogOperation("ROR", 2);
			ROR(AddressingMode::ZeroPageX);
			break;

		case 0x7E:
			Logger.LogOperation("ROR", 3);
			ROR(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Add with Carry
			// -------------------------------------------------------------------
		case 0x61:
			Logger.LogOperation("ADC", 2);
			ADC(AddressingMode::IndirectX);
			break;

		case 0x65:
			Logger.LogOperation("ADC", 2);
			ADC(AddressingMode::ZeroPage);
			break;

		case 0x69:
			Logger.LogOperation("ADC", 2);
			ADC(AddressingMode::Immediate);
			break;

		case 0x6D:
			Logger.LogOperation("ADC", 3);
			ADC(AddressingMode::Absolute);
			break;

		case 0x71:
			Logger.LogOperation("ADC", 2);
			ADC(AddressingMode::IndirectY);
			break;

		case 0x75:
			Logger.LogOperation("ADC", 2);
			ADC(AddressingMode::ZeroPageX);
			break;

		case 0x79:
			Logger.LogOperation("ADC", 3);
			ADC(AddressingMode::AbsoluteY);
			break;

		case 0x7D:
			Logger.LogOperation("ADC", 3);
			ADC(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Branch if Overflow Set
			// -------------------------------------------------------------------
		case 0x70:
			Logger.LogOperation("BVS", 2);
			BVS(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Set Interrupt Disable
			// -------------------------------------------------------------------
		case 0x78:
			Logger.LogOperation("SEI", 1);
			SEI(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Store Accumulator
			// -------------------------------------------------------------------
		case 0x81:
			Logger.LogOperation("STA", 2);
			STA(AddressingMode::IndirectX);
			break;

		case 0x85:
			Logger.LogOperation("STA", 2);
			STA(AddressingMode::ZeroPage);
			break;

		case 0x8D:
			Logger.LogOperation("STA", 3);
			STA(AddressingMode::Absolute);
			break;

		case 0x91:
			Logger.LogOperation("STA", 2);
			STA(AddressingMode::IndirectY);
			break;

		case 0x95:
			Logger.LogOperation("STA", 2);
			STA(AddressingMode::ZeroPageX);
			break;

		case 0x99:
			Logger.LogOperation("STA", 3);
			STA(AddressingMode::AbsoluteY);
			break;

		case 0x9D:
			Logger.LogOperation("STA", 3);
			STA(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Store Y Register
			// -------------------------------------------------------------------
		case 0x84:
			Logger.LogOperation("STY", 2);
			STY(AddressingMode::ZeroPage);
			break;

		case 0x8C:
			Logger.LogOperation("STY", 3);
			STY(AddressingMode::Absolute);
			break;

		case 0x94:
			Logger.LogOperation("STY", 2);
			STY(AddressingMode::ZeroPageX);
			break;

			// -------------------------------------------------------------------
			// Store X Register
			// -------------------------------------------------------------------
		case 0x86:
			Logger.LogOperation("STX", 2);
			STX(AddressingMode::ZeroPage);
			break;

		case 0x8E:
			Logger.LogOperation("STX", 3);
			STX(AddressingMode::Absolute);
			break;

		case 0x96:
			Logger.LogOperation("STX", 2);
			STX(AddressingMode::ZeroPageY);
			break;

			// -------------------------------------------------------------------
			// Decrement Y Register
			// -------------------------------------------------------------------
		case 0x88:
			Logger.LogOperation("DEY", 1);
			DEY(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Transfer X to Accumulator
			// -------------------------------------------------------------------
		case 0x8A:
			Logger.LogOperation("TXA", 1);
			TXA(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Branch if Carry Clear
			// -------------------------------------------------------------------
		case 0x90:
			Logger.LogOperation("BCC", 2);
			BCC(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Transfer Y to Accumulator
			// -------------------------------------------------------------------
		case 0x98:
			Logger.LogOperation("TYA", 1);
			TYA(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Transfer X to Stack Pointer
			// -------------------------------------------------------------------
		case 0x9A:
			Logger.LogOperation("TXS", 1);
			TXS(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Load Y Register
			// -------------------------------------------------------------------
		case 0xA0:
			Logger.LogOperation("LDY", 2);
			LDY(AddressingMode::Immediate);
			break;

		case 0xA4:
			Logger.LogOperation("LDY", 2);
			LDY(AddressingMode::ZeroPage);
			break;

		case 0xAC:
			Logger.LogOperation("LDY", 3);
			LDY(AddressingMode::Absolute);
			break;

		case 0xB4:
			Logger.LogOperation("LDY", 2);
			LDY(AddressingMode::ZeroPageX);
			break;

		case 0xBC:
			Logger.LogOperation("LDY", 3);
			LDY(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Load Accumulator
			// -------------------------------------------------------------------
		case 0xA1:
			Logger.LogOperation("LDA", 2);
			LDA(AddressingMode::IndirectX);
			break;

		case 0xA5:
			Logger.LogOperation("LDA", 2);
			LDA(AddressingMode::ZeroPage);
			break;

		case 0xA9:
			Logger.LogOperation("LDA", 2);
			LDA(AddressingMode::Immediate);
			break;

		case 0xAD:
			Logger.LogOperation("LDA", 3);
			LDA(AddressingMode::Absolute);
			break;

		case 0xB1:
			Logger.LogOperation("LDA", 2);
			LDA(AddressingMode::IndirectY);
			break;

		case 0xB5:
			Logger.LogOperation("LDA", 2);
			LDA(AddressingMode::ZeroPageX);
			break;

		case 0xB9:
			Logger.LogOperation("LDA", 3);
			LDA(AddressingMode::AbsoluteY);
			break;

		case 0xBD:
			Logger.LogOperation("LDA", 3);
			LDA(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Load X Register
			// -------------------------------------------------------------------
		case 0xA2:
			Logger.LogOperation("LDX", 2);
			LDX(AddressingMode::Immediate);
			break;

		case 0xA6:
			Logger.LogOperation("LDX", 2);
			LDX(AddressingMode::ZeroPage);
			break;

		case 0xAE:
			Logger.LogOperation("LDX", 3);
			LDX(AddressingMode::Absolute);
			break;

		case 0xB6:
			Logger.LogOperation("LDX", 2);
			LDX(AddressingMode::ZeroPageY);
			break;

		case 0xBE:
			Logger.LogOperation("LDX", 3);
			LDX(AddressingMode::AbsoluteY);
			break;

			// -------------------------------------------------------------------
			// Transfer Accumulator to Y
			// -------------------------------------------------------------------
		case 0xA8:
			Logger.LogOperation("TAY", 1);
			TAY(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Transfer Accumulator to X
			// -------------------------------------------------------------------
		case 0xAA:
			Logger.LogOperation("TAX", 1);
			TAX(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Branch if Carry Set
			// -------------------------------------------------------------------
		case 0xB0:
			Logger.LogOperation("BCS", 2);
			BCS(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Clear Overflow Flag
			// -------------------------------------------------------------------
		case 0xB8:
			Logger.LogOperation("CLV", 1);
			CLV(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Transfer Stack Pointer to X
			// -------------------------------------------------------------------
		case 0xBA:
			Logger.LogOperation("TSX", 1);
			TSX(AddressingMode::Implicit);

			// -------------------------------------------------------------------
			// Compare
			// -------------------------------------------------------------------
		case 0xC1:
			Logger.LogOperation("CMP", 2);
			CMP(AddressingMode::IndirectX);
			break;

		case 0xC5:
			Logger.LogOperation("CMP", 2);
			CMP(AddressingMode::ZeroPage);
			break;

		case 0xC9:
			Logger.LogOperation("CMP", 2);
			CMP(AddressingMode::Immediate);
			break;

		case 0xCD:
			Logger.LogOperation("CMP", 3);
			CMP(AddressingMode::Absolute);
			break;

		case 0xD1:
			Logger.LogOperation("CMP", 2);
			CMP(AddressingMode::IndirectY);
			break;

		case 0xD5:
			Logger.LogOperation("CMP", 2);
			CMP(AddressingMode::ZeroPageX);
			break;

		case 0xD9:
			Logger.LogOperation("CMP", 3);
			CMP(AddressingMode::AbsoluteY);
			break;

		case 0xDD:
			Logger.LogOperation("CMP", 3);
			CMP(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Decrement Memory
			// -------------------------------------------------------------------
		case 0xC6:
			Logger.LogOperation("DEC", 2);
			DEC(AddressingMode::ZeroPage);
			break;

		case 0xD6:
			Logger.LogOperation("DEC", 2);
			DEC(AddressingMode::ZeroPageX);
			break;

		case 0xCE:
			Logger.LogOperation("DEC", 3);
			DEC(AddressingMode::Absolute);
			break;

		case 0xDE:
			Logger.LogOperation("DEC", 3);
			DEC(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Decrement X Register
			// -------------------------------------------------------------------
		case 0xCA:
			Logger.LogOperation("DEX", 1);
			DEX(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Compare Y Register
			// -------------------------------------------------------------------
		case 0xC0:
			Logger.LogOperation("CPY", 2);
			CPY(AddressingMode::Immediate);
			break;

		case 0xC4:
			Logger.LogOperation("CPY", 2);
			CPY(AddressingMode::ZeroPage);
			break;

		case 0xCC:
			Logger.LogOperation("CPY", 3);
			CPY(AddressingMode::Absolute);

			// -------------------------------------------------------------------
			// Increment Y Register
			// -------------------------------------------------------------------
		case 0xC8:
			Logger.LogOperation("INY", 1);
			INY(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Branch if not Equal
			// -------------------------------------------------------------------
		case 0xD0:
			Logger.LogOperation("BNE", 2);
			BNE(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Clear Decimal Mode
			// -------------------------------------------------------------------
		case 0xD8:
			Logger.LogOperation("CLD", 1);
			CLD(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Compare X Register
			// -------------------------------------------------------------------
		case 0xE0:
			Logger.LogOperation("CPX", 2);
			CPX(AddressingMode::Immediate);
			break;

		case 0xE4:
			Logger.LogOperation("CPX", 2);
			CPX(AddressingMode::ZeroPage);
			break;

		case 0xEC:
			Logger.LogOperation("CPX", 3);
			CPX(AddressingMode::Absolute);
			break;

			// -------------------------------------------------------------------
			// Subtract with Carry
			// -------------------------------------------------------------------
		case 0xE1:
			Logger.LogOperation("SBC", 2);
			SBC(AddressingMode::IndirectX);
			break;

		case 0xE5:
			Logger.LogOperation("SBC", 2);
			SBC(AddressingMode::ZeroPage);
			break;

		case 0xE9:
			Logger.LogOperation("SBC", 2);
			SBC(AddressingMode::Immediate);
			break;

		case 0xED:
			Logger.LogOperation("SBC", 3);
			SBC(AddressingMode::Absolute);
			break;

		case 0xF1:
			Logger.LogOperation("SBC", 2);
			SBC(AddressingMode::IndirectY);
			break;

		case 0xF5:
			Logger.LogOperation("SBC", 2);
			SBC(AddressingMode::ZeroPageX);
			break;

		case 0xFD:
			Logger.LogOperation("SBC", 3);
			SBC(AddressingMode::AbsoluteX);
			break;

		case 0xF9:
			Logger.LogOperation("SBC", 3);
			SBC(AddressingMode::AbsoluteY);
			break;

			// -------------------------------------------------------------------
			// Increment Memory
			// -------------------------------------------------------------------
		case 0xE6:
			Logger.LogOperation("INC", 2);
			INC(AddressingMode::ZeroPage);
			break;

		case 0xF6:
			Logger.LogOperation("INC", 2);
			INC(AddressingMode::ZeroPageX);
			break;

		case 0xEE:
			Logger.LogOperation("INC", 3);
			INC(AddressingMode::Absolute);
			break;

		case 0xFE:
			Logger.LogOperation("INC", 3);
			INC(AddressingMode::AbsoluteX);
			break;

			// -------------------------------------------------------------------
			// Increment X Register
			// -------------------------------------------------------------------
		case 0xE8:
			Logger.LogOperation("INX", 1);
			INX(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// No Operation
			// -------------------------------------------------------------------
		case 0xEA:
			Logger.LogOperation("NOP", 1);
			NOP(AddressingMode::Implicit);
			break;

			// -------------------------------------------------------------------
			// Branch if Equal
			// -------------------------------------------------------------------
		case 0xF0:
			Logger.LogOperation("BEQ", 2);
			BEQ(AddressingMode::Relative);
			break;

			// -------------------------------------------------------------------
			// Set Carry Flag
			// -------------------------------------------------------------------
		case 0xF8:
			Logger.LogOperation("SED", 1);
			SED(AddressingMode::Implicit);
			break;

		default:
			Logger.LogOperation("UNKNOWN OP-CODE, THIS SHOULD NEVER HAPPEN", 0);
			std::cerr << "Unknown op-code: " << std::hex << opCode << '\n';
			break;
	}
}

void nes::CPU::PushStack(std::uint8_t value)
{
	// Stack grows downwards
	std::uint16_t address = RamRef.STACK_START_ADDRESS - SP;
	RamRef.WriteByte(address, value);

	// Move stack pointer
	--SP;
}

std::uint8_t nes::CPU::PopStack()
{
	// Stack grows downwards
	std::uint16_t address = RamRef.STACK_START_ADDRESS - SP;
	
	// Move stack pointer
	++SP;

	return RamRef.ReadByte(address);
}

bool nes::CPU::DidProgramCounterCrossPageBoundary(std::uint16_t before, std::uint16_t after) const
{
	// Detect if the lower byte wrapped around
	std::uint16_t lowerBefore = (before & 0xFF);
	std::uint16_t lowerAfter = (after & 0xFF);

	// If the newer value is less than the value before incrementing the address,
	// a page boundary was crossed
	return (lowerAfter < lowerBefore);
}

void nes::CPU::ADC(AddressingMode mode)
{
}

void nes::CPU::AND(AddressingMode mode)
{
}

void nes::CPU::ASL(AddressingMode mode)
{
}

void nes::CPU::BCC(AddressingMode mode)
{
	// Carry flag is clear
	if ((P & (1 << 0)) == 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::BCS(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BCS - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Carry flag is set
	if ((P & (1 << 0)) != 0)
	{
		std::uint16_t initialPC = PC;

		std::int8_t displacement = RamRef.ReadByte(PC + 1);

		// Perform branching
		PC += displacement;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			CurrentCycle += 2;
		}
		else
		{
			CurrentCycle += 1;
		}
	}

	// Always move past the branch bytes, regardless of the branch outcome
	PC += 2;
}

void nes::CPU::BEQ(AddressingMode mode)
{
	// Zero flag is set
	if ((P & (1 << 1)) != 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::BIT(AddressingMode mode)
{
}

void nes::CPU::BMI(AddressingMode mode)
{
	// Negative flag is set
	if ((P & (1 << 7)) != 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::BNE(AddressingMode mode)
{
	// Zero flag is clear
	if ((P & (1 << 1)) == 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::BPL(AddressingMode mode)
{
	// Negative flag is clear
	if ((P & (1 << 7)) == 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::BRK(AddressingMode mode)
{
}

void nes::CPU::BVC(AddressingMode mode)
{
	// Overflow flag is clear
	if ((P & (1 << 6)) == 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::BVS(AddressingMode mode)
{
	// Overflow flag is set
	if ((P & (1 << 6)) != 0)
	{
		// Perform branching
		std::int8_t displacement = RamRef.ReadByte(PC + 1);
		PC += displacement;
	}
}

void nes::CPU::CLC(AddressingMode mode)
{
	P &= ~(1 << 0);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::CLD(AddressingMode mode)
{
	P &= ~(1 << 3);
}

void nes::CPU::CLI(AddressingMode mode)
{
	P &= ~(1 << 2);
}

void nes::CPU::CLV(AddressingMode mode)
{
	P &= ~(1 << 6);
}

void nes::CPU::CMP(AddressingMode mode)
{
}

void nes::CPU::CPX(AddressingMode mode)
{
}

void nes::CPU::CPY(AddressingMode mode)
{
}

void nes::CPU::DEC(AddressingMode mode)
{
}

void nes::CPU::DEX(AddressingMode mode)
{
	// Decrement X
	X -= 1;

	if (X == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((X & (1 << 7)) != 0)
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
	// Decrement Y
	Y -= 1;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((Y & (1 << 7)) != 0)
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
}

void nes::CPU::INC(AddressingMode mode)
{
}

void nes::CPU::INX(AddressingMode mode)
{
	// Increment X
	X += 1;

	if (X == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}
	
	if ((X & (1 << 7)) != 0)
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

void nes::CPU::INY(AddressingMode mode)
{
	// Increment Y
	Y += 1;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((Y & (1 << 7)) != 0)
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

void nes::CPU::JMP(AddressingMode mode)
{
	if (mode == AddressingMode::Absolute)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		PC = ((msb << 8) | lsb);

		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::Indirect)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);

		lsb = RamRef.ReadByte(address);
		msb = RamRef.ReadByte(address + 1);
		PC = ((msb << 8) | lsb);

		CurrentCycle += 5;
	}
	else
	{
		std::cerr << "JMP - Unknown addressing mode.\n";
	}
}

void nes::CPU::JSR(AddressingMode mode)
{
	if (mode == AddressingMode::Absolute)
	{
		// Store the current address minus one on the stack
		std::uint16_t address = PC - 1;
		std::uint8_t lsb = (address & 0x00FF);
		std::uint8_t msb = ((address & 0xFF00) >> 8);
		PushStack(lsb);
		PushStack(msb);

		// Jump to the target location
		lsb = RamRef.ReadByte(PC + 1);
		msb = RamRef.ReadByte(PC + 2);
		PC = ((msb << 8) | lsb);

		CurrentCycle += 6;
	}
	else
	{
		std::cerr << "JSR - Unknown addressing mode.\n";
	}
}

void nes::CPU::LDA(AddressingMode mode)
{
}

void nes::CPU::LDX(AddressingMode mode)
{
	std::uint8_t value = 0;

	if (mode == AddressingMode::Immediate)
	{
		value = RamRef.ReadByte(PC + 1);
		PC += 2;

		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		value = RamRef.ReadByte(address);
		PC += 2;

		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageY)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		address += Y;
		value = RamRef.ReadByte(address);
		PC += 2;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);
		value = RamRef.ReadByte(address);
		PC += 3;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteY)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);
		address += Y;
		value = RamRef.ReadByte(address);

		std::uint16_t initialPC = PC;
		PC += 3;

		CurrentCycle += 4;

		// Crossed a page boundary
		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "LDX - Unknown addressing mode.\n";
	}

	// Set zero flag
	if (value == 0)
	{
		P |= (1 << 1);
	}

	// Set negative flag
	if ((value & (1 << 7)) != 0)
	{
		P |= (1 << 7);
	}

	// Store in the X register
	X = value;
}

void nes::CPU::LDY(AddressingMode mode)
{
	std::uint8_t value = 0;

	if (mode == AddressingMode::Immediate)
	{
		value = RamRef.ReadByte(PC + 1);
		PC += 2;

		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		value = RamRef.ReadByte(address);
		PC += 2;

		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		address += X;
		value = RamRef.ReadByte(address);
		PC += 2;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);
		value = RamRef.ReadByte(address);
		PC += 3;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);
		address += X;
		value = RamRef.ReadByte(address);
		
		std::uint16_t initialPC = PC;
		PC += 3;

		CurrentCycle += 4;

		// Crossed a page boundary
		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "LDY - Unknown addressing mode.\n";
	}

	// Set zero flag
	if (value == 0)
	{
		P |= (1 << 1);
	}

	// Set negative flag
	if ((value & (1 << 7)) != 0)
	{
		P |= (1 << 7);
	}

	// Store in the Y register
	Y = value;
}

void nes::CPU::LSR(AddressingMode mode)
{
}

void nes::CPU::NOP(AddressingMode mode)
{
	++PC;

	CurrentCycle += 2;
}

void nes::CPU::ORA(AddressingMode mode)
{
}

void nes::CPU::PHA(AddressingMode mode)
{
}

void nes::CPU::PHP(AddressingMode mode)
{
}

void nes::CPU::PLA(AddressingMode mode)
{
}

void nes::CPU::PLP(AddressingMode mode)
{
}

void nes::CPU::ROL(AddressingMode mode)
{
}

void nes::CPU::ROR(AddressingMode mode)
{
}

void nes::CPU::RTI(AddressingMode mode)
{
}

void nes::CPU::RTS(AddressingMode mode)
{
}

void nes::CPU::SBC(AddressingMode mode)
{
}

void nes::CPU::SEC(AddressingMode mode)
{
	P |= (1 << 0);

	++PC;

	CurrentCycle += 2;
}

void nes::CPU::SED(AddressingMode mode)
{
	P |= (1 << 3);
}

void nes::CPU::SEI(AddressingMode mode)
{
	P |= (1 << 2);
}

void nes::CPU::STA(AddressingMode mode)
{
}

void nes::CPU::STX(AddressingMode mode)
{
	if (mode == AddressingMode::ZeroPage)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		RamRef.WriteByte(address, X);
		PC += 2;

		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageY)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		address += Y;
		RamRef.WriteByte(address, X);
		PC += 2;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);
		RamRef.WriteByte(address, X);
		PC += 3;

		CurrentCycle += 4;
	}
	else
	{
		std::cerr << "STX - Unknown addressing mode.\n";
	}
}

void nes::CPU::STY(AddressingMode mode)
{
	if (mode == AddressingMode::ZeroPage)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		RamRef.WriteByte(address, Y);
		PC += 2;

		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		std::uint16_t address = RamRef.ReadByte(PC + 1);
		address += Y;
		RamRef.WriteByte(address, Y);
		PC += 2;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		std::uint8_t lsb = RamRef.ReadByte(PC + 1);
		std::uint8_t msb = RamRef.ReadByte(PC + 2);
		std::uint16_t address = ((msb << 8) | lsb);
		RamRef.WriteByte(address, Y);
		PC += 3;

		CurrentCycle += 4;
	}
	else
	{
		std::cerr << "STY - Unknown addressing mode.\n";
	}
}

void nes::CPU::TAX(AddressingMode mode)
{
	// Transfer the accumulator to the X register
	X = A;

	if (X == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((X & (1 << 7)) != 0)
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

void nes::CPU::TAY(AddressingMode mode)
{
	// Transfer the accumulator to the Y register
	Y = A;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((Y & (1 << 7)) != 0)
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

void nes::CPU::TSX(AddressingMode mode)
{
	// Transfer the stack pointer to the X register
	X = SP;

	if (X == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((X & (1 << 7)) != 0)
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

void nes::CPU::TXA(AddressingMode mode)
{
	// Transfer the X register to the accumulator
	A = X;

	if (A == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((A & (1 << 7)) != 0)
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

void nes::CPU::TXS(AddressingMode mode)
{
	SP = X;
}

void nes::CPU::TYA(AddressingMode mode)
{
	// Transfer the Y register to the accumulator
	A = Y;

	if (A == 0)
	{
		// Value is zero, set zero flag
		P |= (1 << 1);
	}
	else
	{
		// Not zero, unset zero flag
		P &= ~(1 << 1);
	}

	if ((A & (1 << 7)) != 0)
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
