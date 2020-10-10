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
	SetDefaultState();
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

std::uint16_t nes::CPU::GetStackPointer() const
{
	return RamRef.STACK_START_ADDRESS - SP;
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

void nes::CPU::SetDefaultState()
{
	// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
	P = 0x24;
	SP = 0xFD;

	// http://forum.6502.org/viewtopic.php?f=4&t=5704#:~:text=On%20the%206502%2C%20the%20reset,all%20interrupts)%20takes%207%20cycles.
	CurrentCycle = 7;
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
			Logger.LogOperation("PLA", 1);
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
	// Move stack pointer
	++SP;

	// Stack grows downwards
	std::uint16_t address = RamRef.STACK_START_ADDRESS - SP;
	std::uint8_t value = RamRef.ReadByte(address);

	// Clear value from stack
	RamRef.WriteByte(address, 0);

	return value;
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

std::uint16_t nes::CPU::GetTargetAddress(AddressingMode mode) const
{
	switch (mode)
	{
		case nes::CPU::AddressingMode::Immediate:
			{
				return PC + 1;
			}
			break;
		case nes::CPU::AddressingMode::Absolute:
			{
				std::uint8_t lsb = RamRef.ReadByte(PC + 1);
				std::uint8_t msb = RamRef.ReadByte(PC + 2);
				std::uint16_t address = ((msb << 8) | lsb);
				return address;
			}
			break;
		case nes::CPU::AddressingMode::AbsoluteX:
			{
				std::uint8_t lsb = RamRef.ReadByte(PC + 1);
				std::uint8_t msb = RamRef.ReadByte(PC + 2);
				std::uint16_t address = ((msb << 8) | lsb);
				return (address + X);
			}
			break;
		case nes::CPU::AddressingMode::AbsoluteY:
			{
				std::uint8_t lsb = RamRef.ReadByte(PC + 1);
				std::uint8_t msb = RamRef.ReadByte(PC + 2);
				std::uint16_t address = ((msb << 8) | lsb);
				return (address + Y);
			}
			break;
		case nes::CPU::AddressingMode::Indirect:
			{
				std::uint8_t lsb = RamRef.ReadByte(PC + 1);
				std::uint8_t msb = RamRef.ReadByte(PC + 2);
				std::uint16_t address = ((msb << 8) | lsb);

				std::uint8_t targetLsb = RamRef.ReadByte(address);
				std::uint8_t targetMsb = RamRef.ReadByte(address + 1);
				std::uint16_t targetAddress = ((targetMsb << 8) | targetLsb);
				return targetAddress;
			}
			break;
		case nes::CPU::AddressingMode::IndirectX:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1);
				zeroPageAddress += X;	// May wrap around

				std::uint8_t lsb = RamRef.ReadByte(zeroPageAddress);
				std::uint8_t msb = RamRef.ReadByte(zeroPageAddress + 1);
				std::uint16_t address = ((msb << 8) | lsb);
				return address;
			}
			break;
		case nes::CPU::AddressingMode::IndirectY:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1);
				std::uint16_t address = RamRef.ReadByte(zeroPageAddress);
				return (address + Y);
			}
			break;
		case nes::CPU::AddressingMode::ZeroPage:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1);
				return zeroPageAddress;
			}
			break;
		case nes::CPU::AddressingMode::ZeroPageX:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1);
				zeroPageAddress += X;	// May wrap around

				return zeroPageAddress;
			}
			break;
		case nes::CPU::AddressingMode::ZeroPageY:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1);
				zeroPageAddress += Y;	// May wrap around

				return zeroPageAddress;
			}
			break;
		default:
			std::cerr << "Invalid addressing mode." << std::endl;
			break;
	}

	// Only ever returned when the addressing mode is invalid
	return 0;
}

void nes::CPU::SetStatusFlag(StatusFlags flag)
{
	P |= static_cast<std::uint8_t>(flag);
}

void nes::CPU::ClearStatusFlag(StatusFlags flag)
{
	P &= ~static_cast<std::uint8_t>(flag);
}

bool nes::CPU::IsStatusFlagSet(StatusFlags flag) const
{
	return ((P & static_cast<std::uint8_t>(flag)) != 0);
}

bool nes::CPU::IsStatusFlagClear(StatusFlags flag) const
{
	return ((P & static_cast<std::uint8_t>(flag)) == 0);
}

bool nes::CPU::IsNthBitSet(std::uint8_t byte, std::uint8_t n) const
{
	return ((byte & (1 << n)) != 0);
}

bool nes::CPU::IsNthBitClear(std::uint8_t byte, std::uint8_t n) const
{
	return ((byte & (1 << n)) == 0);
}

void nes::CPU::ADC(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));
	std::uint8_t result = A + value + (P << static_cast<std::uint8_t>(StatusFlags::Carry));

	// Overflow detected
	if (result < A)
	{
		SetStatusFlag(StatusFlags::Overflow);
		SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Overflow);
		ClearStatusFlag(StatusFlags::Carry);
	}

	A = result;

	if (IsNthBitSet(A, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (A == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX || mode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = PC;
		PC += 2;
		CurrentCycle += 5;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "ADC - Unknown addressing mode.\n";
	}
}

void nes::CPU::AND(AddressingMode mode)
{
	// Retrieve value to AND against the accumulator
	std::uint8_t compareAgainst = RamRef.ReadByte(GetTargetAddress(mode));

	// Perform logical AND
	A &= compareAgainst;

	// Set zero flag
	if (A == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	// Set negative flag if the 7th bit is set
	if (IsNthBitSet(A, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = PC;
		PC += 2;
		CurrentCycle += 5;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "AND - Unknown addressing mode.\n";
	}
}

void nes::CPU::ASL(AddressingMode mode)
{
}

void nes::CPU::BCC(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BCC - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Carry flag is clear
	if (IsStatusFlagClear(StatusFlags::Carry))
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
	if (IsStatusFlagSet(StatusFlags::Carry))
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
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BEQ - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Zero flag is set
	if (IsStatusFlagSet(StatusFlags::Zero))
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

void nes::CPU::BIT(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));

	if (mode == AddressingMode::ZeroPage)
	{
		CurrentCycle += 3;
		PC += 2;
	}
	else if (mode == AddressingMode::Absolute)
	{
		CurrentCycle += 4;
		PC += 3;
	}
	else
	{
		std::cerr << "BIT - Unknown addressing mode.\n";
	}

	// Set the zero flag if the BIT result is zero
	if ((A & value) == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	// Set the overflow flag to the value of the 6th bit
	if (IsNthBitSet(value, 6))
	{
		SetStatusFlag(StatusFlags::Overflow);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Overflow);
	}

	// Set the negative flag to the value of the 7th bit
	if (IsNthBitSet(value, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}
}

void nes::CPU::BMI(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BMI - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Negative flag is set
	if (IsStatusFlagSet(StatusFlags::Negative))
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

void nes::CPU::BNE(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BNE - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Zero flag is clear
	if (IsStatusFlagClear(StatusFlags::Zero))
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

void nes::CPU::BPL(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BPL - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Negative flag is clear
	if (IsStatusFlagClear(StatusFlags::Negative))
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

void nes::CPU::BRK(AddressingMode mode)
{
}

void nes::CPU::BVC(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BVC - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Overflow flag is clear
	if (IsStatusFlagClear(StatusFlags::Overflow))
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

void nes::CPU::BVS(AddressingMode mode)
{
	if (mode != AddressingMode::Relative)
	{
		// Addressing mode is not used, but it is good to check for any
		// inconsistencies regardless
		std::cerr << "BVC - Unknown addressing mode.\n";
	}

	CurrentCycle += 2;

	// Overflow flag is set
	if (IsStatusFlagSet(StatusFlags::Overflow))
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

void nes::CPU::CLC(AddressingMode mode)
{
	ClearStatusFlag(StatusFlags::Carry);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::CLD(AddressingMode mode)
{
	ClearStatusFlag(StatusFlags::DecimalMode);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::CLI(AddressingMode mode)
{
	ClearStatusFlag(StatusFlags::InterruptDisable);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::CLV(AddressingMode mode)
{
	ClearStatusFlag(StatusFlags::Overflow);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::CMP(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));
	std::uint8_t result = A - value;

	if (A >= value)
	{
		SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Carry);
	}

	if (A == value)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(result, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX || mode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = PC;
		PC += 2;
		CurrentCycle += 5;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "CMP - Unknown addressing mode.\n";
	}
}

void nes::CPU::CPX(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));
	std::uint8_t result = X - value;

	if (X >= value)
	{
		SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Carry);
	}

	if (X == value)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(result, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else
	{
		std::cerr << "CPX - Unknown addressing mode.\n";
	}
}

void nes::CPU::CPY(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));
	std::uint8_t result = Y - value;

	if (Y >= value)
	{
		SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Carry);
	}

	if (Y == value)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(result, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else
	{
		std::cerr << "CPY - Unknown addressing mode.\n";
	}
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
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(X, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}
}

void nes::CPU::DEY(AddressingMode mode)
{
	// Decrement Y
	Y -= 1;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(Y, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}
}

void nes::CPU::EOR(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));

	// Perform bit-wise exclusive OR on the accumulator
	A ^= value;

	if (A == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(A, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX || mode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = PC;
		PC += 2;
		CurrentCycle += 5;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "EOR - Unknown addressing mode.\n";
	}
}

void nes::CPU::INC(AddressingMode mode)
{
	std::uint16_t address = GetTargetAddress(mode);

	// Increment and store the value at the specified address
	std::uint8_t value = (RamRef.ReadByte(address) + 1);
	RamRef.WriteByte(address, value);

	if (value == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(value, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 5;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::AbsoluteX)
	{
		PC += 3;
		CurrentCycle += 7;
	}
	else
	{
		std::cerr << "INC - Unknown addressing mode.\n";
	}
}

void nes::CPU::INX(AddressingMode mode)
{
	// Increment X
	X += 1;

	if (X == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(X, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 2;
}

void nes::CPU::INY(AddressingMode mode)
{
	// Increment Y
	Y += 1;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(Y, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 2;
}

void nes::CPU::JMP(AddressingMode mode)
{
	PC = GetTargetAddress(mode);

	if (mode == AddressingMode::Absolute)
	{
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::Indirect)
	{
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
		std::uint16_t targetAddress = GetTargetAddress(mode);

		// The JSR instruction is 3 bytes wide, this would mean that the next
		// instruction is at PC + 3. However, the documentation states that JSR
		// pushes (next instruction - 1) to the stack, hence we only add two bytes
		// instead of three. This is to account for that -1.
		std::uint16_t returnAddress = PC + 2;

		// Store the target address minus one on the stack
		std::uint8_t lsb = (returnAddress & 0x00FF);
		std::uint8_t msb = ((returnAddress & 0xFF00) >> 8);

		// According to the documentation, the high byte needs to be pushed first
		PushStack(msb);
		PushStack(lsb);

		// Jump to the target location
		PC = GetTargetAddress(mode);
		CurrentCycle += 6;
	}
	else
	{
		std::cerr << "JSR - Unknown addressing mode.\n";
	}
}

void nes::CPU::LDA(AddressingMode mode)
{
	std::uint8_t value = 0;
	std::uint16_t initialPC = PC;

	if (mode == AddressingMode::Immediate)
	{
		value = RamRef.ReadByte(PC + 1);
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 2;

		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 3;
		CurrentCycle += 4;

		// Crossed a page boundary
		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::AbsoluteY)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 3;
		CurrentCycle += 4;

		// Crossed a page boundary
		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		CurrentCycle += 6;
		PC += 2;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		CurrentCycle += 5;
		PC += 2;

		// Crossed a page boundary
		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "LDA - Unknown addressing mode.\n";
	}

	if (value == 0)
	{
		// Set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(value, 7))
	{
		// Set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	// Store in the A register
	A = value;
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
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageY)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteY)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));

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

	if (value == 0)
	{
		// Set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(value, 7) != 0)
	{
		// Set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
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
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX)
	{
		value = RamRef.ReadByte(GetTargetAddress(mode));

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

	if (value == 0)
	{
		// Set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(value, 7) != 0)
	{
		// Set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
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
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));

	// Perform bit-wise OR on the accumulator
	A |= value;

	if (A == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(A, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX || mode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = PC;
		PC += 2;
		CurrentCycle += 5;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "ORA - Unknown addressing mode.\n";
	}
}

void nes::CPU::PHP(AddressingMode mode)
{
	PushStack(P);
	++PC;
	CurrentCycle += 3;
}

void nes::CPU::PLA(AddressingMode mode)
{
	A = PopStack();

	// Set zero flag if the accumulator equals zero
	if (A == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	// Set negative flag if bit 7 is set
	if (IsNthBitSet(A, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 4;
}

void nes::CPU::PLP(AddressingMode mode)
{
	P = PopStack();
	++PC;
	CurrentCycle += 4;
}

void nes::CPU::PHA(AddressingMode mode)
{
	PushStack(A);
	++PC;
	CurrentCycle += 3;
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
	std::uint8_t lsb = PopStack();
	std::uint8_t msb = PopStack();
	std::uint16_t address = ((msb << 8) | lsb);

	// Because JSR stores the target address - 1 on the stack, we have to add 1 to
	// the target address to get the location of the next instruction
	PC = address + 1;
	CurrentCycle += 6;
}

void nes::CPU::SBC(AddressingMode mode)
{
	std::uint8_t value = RamRef.ReadByte(GetTargetAddress(mode));
	std::uint8_t result = A - value - (1 - ~static_cast<std::uint8_t>(StatusFlags::Carry));

	// Overflow detected
	if (result < A)
	{
		SetStatusFlag(StatusFlags::Overflow);
		SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Overflow);
		ClearStatusFlag(StatusFlags::Carry);
	}

	A = result;

	if (IsNthBitSet(A, 7))
	{
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Negative);
	}

	if (A == 0)
	{
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (mode == AddressingMode::Immediate)
	{
		PC += 2;
		CurrentCycle += 2;
	}
	else if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX || mode == AddressingMode::AbsoluteY)
	{
		std::uint16_t initialPC = PC;
		PC += 3;
		CurrentCycle += 4;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		std::uint16_t initialPC = PC;
		PC += 2;
		CurrentCycle += 5;

		if (DidProgramCounterCrossPageBoundary(initialPC, PC))
		{
			++CurrentCycle;
		}
	}
	else
	{
		std::cerr << "SBC - Unknown addressing mode.\n";
	}
}

void nes::CPU::SEC(AddressingMode mode)
{
	SetStatusFlag(StatusFlags::Carry);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::SED(AddressingMode mode)
{
	SetStatusFlag(StatusFlags::DecimalMode);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::SEI(AddressingMode mode)
{
	SetStatusFlag(StatusFlags::InterruptDisable);
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::STA(AddressingMode mode)
{
	RamRef.WriteByte(GetTargetAddress(mode), A);

	if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
		PC += 3;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::AbsoluteX)
	{
		PC += 3;
		CurrentCycle += 5;
	}
	else if (mode == AddressingMode::AbsoluteY)
	{
		PC += 3;
		CurrentCycle += 5;
	}
	else if (mode == AddressingMode::IndirectX)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else if (mode == AddressingMode::IndirectY)
	{
		PC += 2;
		CurrentCycle += 6;
	}
	else
	{
		std::cerr << "STA - Unknown addressing mode.\n";
	}
}

void nes::CPU::STX(AddressingMode mode)
{
	RamRef.WriteByte(GetTargetAddress(mode), X);

	if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageY)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
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
	RamRef.WriteByte(GetTargetAddress(mode), Y);

	if (mode == AddressingMode::ZeroPage)
	{
		PC += 2;
		CurrentCycle += 3;
	}
	else if (mode == AddressingMode::ZeroPageX)
	{
		PC += 2;
		CurrentCycle += 4;
	}
	else if (mode == AddressingMode::Absolute)
	{
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
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(X, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 2;
}

void nes::CPU::TAY(AddressingMode mode)
{
	// Transfer the accumulator to the Y register
	Y = A;

	if (Y == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(Y, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 2;
}

void nes::CPU::TSX(AddressingMode mode)
{
	// Transfer the stack pointer to the X register
	X = SP;

	if (X == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(X, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 2;
}

void nes::CPU::TXA(AddressingMode mode)
{
	// Transfer the X register to the accumulator
	A = X;

	if (A == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(A, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}

	++PC;
	CurrentCycle += 2;
}

void nes::CPU::TXS(AddressingMode mode)
{
	SP = X;
	++PC;
	CurrentCycle += 2;
}

void nes::CPU::TYA(AddressingMode mode)
{
	// Transfer the Y register to the accumulator
	A = Y;

	if (A == 0)
	{
		// Value is zero, set zero flag
		SetStatusFlag(StatusFlags::Zero);
	}
	else
	{
		// Not zero, unset zero flag
		ClearStatusFlag(StatusFlags::Zero);
	}

	if (IsNthBitSet(A, 7))
	{
		// Value is negative, set negative flag
		SetStatusFlag(StatusFlags::Negative);
	}
	else
	{
		// Value is positive, unset negative flag
		ClearStatusFlag(StatusFlags::Negative);
	}
}
