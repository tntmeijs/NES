#include "cpu.hpp"
#include "ram/ram.hpp"
#include "flags/cpu_b_flags.hpp"

#include "instructions/cpu_instruction_base.hpp"
#include "instructions/cpu_instruction_op_adc.hpp"
#include "instructions/cpu_instruction_op_and.hpp"
#include "instructions/cpu_instruction_op_asl.hpp"
#include "instructions/cpu_instruction_op_bcc.hpp"
#include "instructions/cpu_instruction_op_bcs.hpp"
#include "instructions/cpu_instruction_op_beq.hpp"
#include "instructions/cpu_instruction_op_bit.hpp"
#include "instructions/cpu_instruction_op_bmi.hpp"
#include "instructions/cpu_instruction_op_bne.hpp"
#include "instructions/cpu_instruction_op_bpl.hpp"
#include "instructions/cpu_instruction_op_brk.hpp"
#include "instructions/cpu_instruction_op_bvc.hpp"
#include "instructions/cpu_instruction_op_bvs.hpp"
#include "instructions/cpu_instruction_op_clc.hpp"
#include "instructions/cpu_instruction_op_cld.hpp"
#include "instructions/cpu_instruction_op_cli.hpp"
#include "instructions/cpu_instruction_op_clv.hpp"
#include "instructions/cpu_instruction_op_cmp.hpp"
#include "instructions/cpu_instruction_op_cpx.hpp"
#include "instructions/cpu_instruction_op_cpy.hpp"
#include "instructions/cpu_instruction_op_dec.hpp"
#include "instructions/cpu_instruction_op_dex.hpp"
#include "instructions/cpu_instruction_op_dey.hpp"
#include "instructions/cpu_instruction_op_eor.hpp"
#include "instructions/cpu_instruction_op_inc.hpp"
#include "instructions/cpu_instruction_op_inx.hpp"
#include "instructions/cpu_instruction_op_iny.hpp"
#include "instructions/cpu_instruction_op_jmp.hpp"
#include "instructions/cpu_instruction_op_jsr.hpp"
#include "instructions/cpu_instruction_op_lda.hpp"
#include "instructions/cpu_instruction_op_ldx.hpp"
#include "instructions/cpu_instruction_op_ldy.hpp"
#include "instructions/cpu_instruction_op_lsr.hpp"
#include "instructions/cpu_instruction_op_nop.hpp"
#include "instructions/cpu_instruction_op_ora.hpp"
#include "instructions/cpu_instruction_op_pha.hpp"
#include "instructions/cpu_instruction_op_php.hpp"
#include "instructions/cpu_instruction_op_pla.hpp"
#include "instructions/cpu_instruction_op_plp.hpp"
#include "instructions/cpu_instruction_op_rol.hpp"
#include "instructions/cpu_instruction_op_ror.hpp"
#include "instructions/cpu_instruction_op_rti.hpp"
#include "instructions/cpu_instruction_op_rts.hpp"
#include "instructions/cpu_instruction_op_sbc.hpp"
#include "instructions/cpu_instruction_op_sec.hpp"
#include "instructions/cpu_instruction_op_sed.hpp"
#include "instructions/cpu_instruction_op_sei.hpp"
#include "instructions/cpu_instruction_op_sta.hpp"
#include "instructions/cpu_instruction_op_stx.hpp"
#include "instructions/cpu_instruction_op_sty.hpp"
#include "instructions/cpu_instruction_op_tax.hpp"
#include "instructions/cpu_instruction_op_tay.hpp"
#include "instructions/cpu_instruction_op_tsx.hpp"
#include "instructions/cpu_instruction_op_txa.hpp"
#include "instructions/cpu_instruction_op_txs.hpp"
#include "instructions/cpu_instruction_op_tya.hpp"

#include <iostream>

nes::CPU::CPU(RAM& ramRef) :
	PC(0),
	RamRef(ramRef),
	CurrentCycle(0)
{
	SetDefaultState();
	AllocateInstructionTable();
}

nes::CPU::~CPU()
{
	DeallocateInstructionTable();
}

void nes::CPU::SetProgramCounterToResetVector()
{
	// The low byte of the reset vector address is stored at 0xFFFD
	// The high byte of the reset vector address is stored at 0xFFFC
	PC = ConstructAddressFromBytes(RamRef.ReadByte(0xFFFD), RamRef.ReadByte(0xFFFC));
}

void nes::CPU::SetProgramCounterToAddress(std::uint16_t address)
{
	PC = address;
}

void nes::CPU::ExecuteInstruction()
{
	Byte opCode = RamRef.ReadByte(PC);
	ProcessOpCode(opCode);
}

void nes::CPU::MoveProgramCounter(std::int32_t offset)
{
	PC += offset;
}

void nes::CPU::UpdateCurrentCycle(std::uint8_t offset)
{
	CurrentCycle += offset;
}

nes::Byte nes::CPU::ReadRamValueAtAddress(std::uint16_t address) const
{
	return RamRef.ReadByte(address);
}

void nes::CPU::WriteRamValueAtAddress(std::uint16_t address, Byte value) const
{
	RamRef.WriteByte(address, value);
}

std::uint16_t nes::CPU::GetProgramCounter() const
{
	return PC;
}

std::uint16_t nes::CPU::GetStackPointer() const
{
	return RamRef.STACK_START_ADDRESS - SP.value;
}

nes::Byte nes::CPU::GetRegister(RegisterType type) const
{
	Byte value;

	switch (type)
	{
		case nes::CPU::RegisterType::A:
			value = A;
			break;
		case nes::CPU::RegisterType::X:
			value = X;
			break;
		case nes::CPU::RegisterType::Y:
			value = Y;
			break;
		case nes::CPU::RegisterType::P:
			value = P;
			break;
		case nes::CPU::RegisterType::SP:
			value = SP;
			break;
		default:
			break;
	}

	return value;
}

std::uint64_t nes::CPU::GetCurrentCycle() const
{
	return CurrentCycle;
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

void nes::CPU::SetDefaultState()
{
	A.value = 0;
	X.value = 0;
	Y.value = 0;

	// https://wiki.nesdev.com/w/index.php/CPU_power_up_state
	P.value = 0x24;
	SP.value = 0xFD;

	// http://forum.6502.org/viewtopic.php?f=4&t=5704#:~:text=On%20the%206502%2C%20the%20reset,all%20interrupts)%20takes%207%20cycles.
	CurrentCycle = 7;
}

std::uint16_t nes::CPU::GetTargetAddress(AddressingMode mode) const
{
	switch (mode)
	{
		case nes::AddressingMode::Immediate:
			{
				return PC + 1;
			}
			break;
		case nes::AddressingMode::Absolute:
			{
				return ConstructAddressFromBytes(RamRef.ReadByte(PC + 2), RamRef.ReadByte(PC + 1));
			}
			break;
		case nes::AddressingMode::AbsoluteX:
			{
				std::uint16_t address = ConstructAddressFromBytes(RamRef.ReadByte(PC + 2), RamRef.ReadByte(PC + 1));
				return (address + X.value);
			}
			break;
		case nes::AddressingMode::AbsoluteY:
			{
				std::uint16_t address = ConstructAddressFromBytes(RamRef.ReadByte(PC + 2), RamRef.ReadByte(PC + 1));
				return (address + Y.value);
			}
			break;
		case nes::AddressingMode::Indirect:
			{
				std::uint16_t address = ConstructAddressFromBytes(RamRef.ReadByte(PC + 2), RamRef.ReadByte(PC + 1));

				Byte targetLsb = RamRef.ReadByte(address);
				Byte targetMsb = RamRef.ReadByte(address + 1);
				std::uint16_t targetAddress = ConstructAddressFromBytes(targetMsb, targetLsb);
				return targetAddress;
			}
			break;
		case nes::AddressingMode::IndirectX:
			{
				Byte zeroPageAddress = RamRef.ReadByte(PC + 1);
				zeroPageAddress.value += X.value;	// May wrap around

				Byte lsb = RamRef.ReadByte(zeroPageAddress.value);
				Byte msb = RamRef.ReadByte(zeroPageAddress.value + 1);
				std::uint16_t address = ConstructAddressFromBytes(msb, lsb);
				return address;
			}
			break;
		case nes::AddressingMode::IndirectY:
			{
				Byte zeroPageAddress = RamRef.ReadByte(PC + 1);
				std::uint16_t address = RamRef.ReadByte(zeroPageAddress.value).value;
				return (address + Y.value);
			}
			break;
		case nes::AddressingMode::ZeroPage:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1).value;
				return zeroPageAddress;
			}
			break;
		case nes::AddressingMode::ZeroPageX:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1).value;
				zeroPageAddress += X.value;	// May wrap around

				return zeroPageAddress;
			}
			break;
		case nes::AddressingMode::ZeroPageY:
			{
				std::uint8_t zeroPageAddress = RamRef.ReadByte(PC + 1).value;
				zeroPageAddress += Y.value;	// May wrap around

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

void nes::CPU::AllocateInstructionTable()
{
	// Set all pointers to nullptr to ensure that we have no garbage values
	for (std::size_t i = 0; i < InstructionTable.size(); ++i)
	{
		InstructionTable[i] = nullptr;
	}

	// ADC
	InstructionTable[0x61] = new CpuInstructionOpADC(*this, AddressingMode::IndirectX);
	InstructionTable[0x65] = new CpuInstructionOpADC(*this, AddressingMode::ZeroPage);
	InstructionTable[0x69] = new CpuInstructionOpADC(*this, AddressingMode::Immediate);
	InstructionTable[0x6D] = new CpuInstructionOpADC(*this, AddressingMode::Absolute);
	InstructionTable[0x71] = new CpuInstructionOpADC(*this, AddressingMode::IndirectY);
	InstructionTable[0x75] = new CpuInstructionOpADC(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x79] = new CpuInstructionOpADC(*this, AddressingMode::AbsoluteY);
	InstructionTable[0x7D] = new CpuInstructionOpADC(*this, AddressingMode::AbsoluteX);

	// AND
	InstructionTable[0x21] = new CpuInstructionOpAND(*this, AddressingMode::IndirectX);
	InstructionTable[0x25] = new CpuInstructionOpAND(*this, AddressingMode::ZeroPage);
	InstructionTable[0x29] = new CpuInstructionOpAND(*this, AddressingMode::Immediate);
	InstructionTable[0x2D] = new CpuInstructionOpAND(*this, AddressingMode::Absolute);
	InstructionTable[0x31] = new CpuInstructionOpAND(*this, AddressingMode::IndirectY);
	InstructionTable[0x35] = new CpuInstructionOpAND(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x39] = new CpuInstructionOpAND(*this, AddressingMode::AbsoluteY);
	InstructionTable[0x3D] = new CpuInstructionOpAND(*this, AddressingMode::AbsoluteX);

	// ASL
	InstructionTable[0x06] = new CpuInstructionOpASL(*this, AddressingMode::ZeroPage);
	InstructionTable[0x0A] = new CpuInstructionOpASL(*this, AddressingMode::Accumulator);
	InstructionTable[0x0E] = new CpuInstructionOpASL(*this, AddressingMode::Absolute);
	InstructionTable[0x16] = new CpuInstructionOpASL(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x1E] = new CpuInstructionOpASL(*this, AddressingMode::AbsoluteX);

	// BCC
	InstructionTable[0x90] = new CpuInstructionOpBCC(*this, AddressingMode::Relative);

	// BCS
	InstructionTable[0xB0] = new CpuInstructionOpBCS(*this, AddressingMode::Relative);

	// BEQ
	InstructionTable[0xF0] = new CpuInstructionOpBEQ(*this, AddressingMode::Relative);

	// BIT
	InstructionTable[0x24] = new CpuInstructionOpBIT(*this, AddressingMode::ZeroPage);
	InstructionTable[0x2C] = new CpuInstructionOpBIT(*this, AddressingMode::Absolute);

	// BMI
	InstructionTable[0x30] = new CpuInstructionOpBMI(*this, AddressingMode::Relative);

	// BNE
	InstructionTable[0xD0] = new CpuInstructionOpBNE(*this, AddressingMode::Relative);

	// BPL
	InstructionTable[0x10] = new CpuInstructionOpBPL(*this, AddressingMode::Relative);

	// BRK
	InstructionTable[0x00] = new CpuInstructionOpBRK(*this, AddressingMode::Implicit);

	// BVC
	InstructionTable[0x50] = new CpuInstructionOpBVC(*this, AddressingMode::Relative);

	// BVS
	InstructionTable[0x70] = new CpuInstructionOpBVS(*this, AddressingMode::Relative);

	// CLC
	InstructionTable[0x18] = new CpuInstructionOpCLC(*this, AddressingMode::Implicit);

	// CLD
	InstructionTable[0xD8] = new CpuInstructionOpCLD(*this, AddressingMode::Implicit);

	// CLI
	InstructionTable[0x58] = new CpuInstructionOpCLI(*this, AddressingMode::Implicit);

	// CLV
	InstructionTable[0xB8] = new CpuInstructionOpCLV(*this, AddressingMode::Implicit);

	// CMP
	InstructionTable[0xC1] = new CpuInstructionOpCMP(*this, AddressingMode::IndirectX);
	InstructionTable[0xC5] = new CpuInstructionOpCMP(*this, AddressingMode::ZeroPage);
	InstructionTable[0xC9] = new CpuInstructionOpCMP(*this, AddressingMode::Immediate);
	InstructionTable[0xCD] = new CpuInstructionOpCMP(*this, AddressingMode::Absolute);
	InstructionTable[0xD1] = new CpuInstructionOpCMP(*this, AddressingMode::IndirectY);
	InstructionTable[0xD5] = new CpuInstructionOpCMP(*this, AddressingMode::ZeroPageX);
	InstructionTable[0xD9] = new CpuInstructionOpCMP(*this, AddressingMode::AbsoluteY);
	InstructionTable[0xDD] = new CpuInstructionOpCMP(*this, AddressingMode::AbsoluteX);

	// CPX
	InstructionTable[0xE0] = new CpuInstructionOpCPX(*this, AddressingMode::Immediate);
	InstructionTable[0xE4] = new CpuInstructionOpCPX(*this, AddressingMode::ZeroPage);
	InstructionTable[0xEC] = new CpuInstructionOpCPX(*this, AddressingMode::Absolute);

	// CPY
	InstructionTable[0xC0] = new CpuInstructionOpCPY(*this, AddressingMode::Immediate);
	InstructionTable[0xC4] = new CpuInstructionOpCPY(*this, AddressingMode::ZeroPage);
	InstructionTable[0xCC] = new CpuInstructionOpCPY(*this, AddressingMode::Absolute);

	// DEC
	InstructionTable[0xC6] = new CpuInstructionOpDEC(*this, AddressingMode::ZeroPage);
	InstructionTable[0xD6] = new CpuInstructionOpDEC(*this, AddressingMode::ZeroPageX);
	InstructionTable[0xCE] = new CpuInstructionOpDEC(*this, AddressingMode::Absolute);
	InstructionTable[0xDE] = new CpuInstructionOpDEC(*this, AddressingMode::AbsoluteX);

	// DEX
	InstructionTable[0xCA] = new CpuInstructionOpDEX(*this, AddressingMode::Implicit);

	// DEY
	InstructionTable[0x88] = new CpuInstructionOpDEY(*this, AddressingMode::Implicit);

	// EOR
	InstructionTable[0x41] = new CpuInstructionOpEOR(*this, AddressingMode::IndirectX);
	InstructionTable[0x45] = new CpuInstructionOpEOR(*this, AddressingMode::ZeroPage);
	InstructionTable[0x49] = new CpuInstructionOpEOR(*this, AddressingMode::Immediate);
	InstructionTable[0x4D] = new CpuInstructionOpEOR(*this, AddressingMode::Absolute);
	InstructionTable[0x51] = new CpuInstructionOpEOR(*this, AddressingMode::IndirectY);
	InstructionTable[0x55] = new CpuInstructionOpEOR(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x59] = new CpuInstructionOpEOR(*this, AddressingMode::AbsoluteY);
	InstructionTable[0x5D] = new CpuInstructionOpEOR(*this, AddressingMode::AbsoluteX);

	// INC
	InstructionTable[0xE6] = new CpuInstructionOpINC(*this, AddressingMode::ZeroPage);
	InstructionTable[0xF6] = new CpuInstructionOpINC(*this, AddressingMode::ZeroPageX);
	InstructionTable[0xEE] = new CpuInstructionOpINC(*this, AddressingMode::Absolute);
	InstructionTable[0xFE] = new CpuInstructionOpINC(*this, AddressingMode::AbsoluteX);

	// INX
	InstructionTable[0xE8] = new CpuInstructionOpINX(*this, AddressingMode::Implicit);

	// INY
	InstructionTable[0xC8] = new CpuInstructionOpINY(*this, AddressingMode::Implicit);

	// JMP
	InstructionTable[0x4C] = new CpuInstructionOpJMP(*this, AddressingMode::Absolute);
	InstructionTable[0x6C] = new CpuInstructionOpJMP(*this, AddressingMode::Indirect);

	// JSR
	InstructionTable[0x20] = new CpuInstructionOpJSR(*this, AddressingMode::Absolute);

	// LDA
	InstructionTable[0xA1] = new CpuInstructionOpLDA(*this, AddressingMode::IndirectX);
	InstructionTable[0xA5] = new CpuInstructionOpLDA(*this, AddressingMode::ZeroPage);
	InstructionTable[0xA9] = new CpuInstructionOpLDA(*this, AddressingMode::Immediate);
	InstructionTable[0xAD] = new CpuInstructionOpLDA(*this, AddressingMode::Absolute);
	InstructionTable[0xB1] = new CpuInstructionOpLDA(*this, AddressingMode::IndirectY);
	InstructionTable[0xB5] = new CpuInstructionOpLDA(*this, AddressingMode::ZeroPageX);
	InstructionTable[0xB9] = new CpuInstructionOpLDA(*this, AddressingMode::AbsoluteY);
	InstructionTable[0xBD] = new CpuInstructionOpLDA(*this, AddressingMode::AbsoluteX);

	// LDX
	InstructionTable[0xA2] = new CpuInstructionOpLDX(*this, AddressingMode::Immediate);
	InstructionTable[0xA6] = new CpuInstructionOpLDX(*this, AddressingMode::ZeroPage);
	InstructionTable[0xAE] = new CpuInstructionOpLDX(*this, AddressingMode::Absolute);
	InstructionTable[0xB6] = new CpuInstructionOpLDX(*this, AddressingMode::ZeroPageY);
	InstructionTable[0xBE] = new CpuInstructionOpLDX(*this, AddressingMode::AbsoluteY);

	// LDY
	InstructionTable[0xA0] = new CpuInstructionOpLDY(*this, AddressingMode::Immediate);
	InstructionTable[0xA4] = new CpuInstructionOpLDY(*this, AddressingMode::ZeroPage);
	InstructionTable[0xAC] = new CpuInstructionOpLDY(*this, AddressingMode::Absolute);
	InstructionTable[0xB4] = new CpuInstructionOpLDY(*this, AddressingMode::ZeroPageX);
	InstructionTable[0xBC] = new CpuInstructionOpLDY(*this, AddressingMode::AbsoluteX);

	// LSR
	InstructionTable[0x46] = new CpuInstructionOpLSR(*this, AddressingMode::ZeroPage);
	InstructionTable[0x4A] = new CpuInstructionOpLSR(*this, AddressingMode::Accumulator);
	InstructionTable[0x4E] = new CpuInstructionOpLSR(*this, AddressingMode::Absolute);
	InstructionTable[0x56] = new CpuInstructionOpLSR(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x5E] = new CpuInstructionOpLSR(*this, AddressingMode::AbsoluteX);

	// NOP
	InstructionTable[0xEA] = new CpuInstructionOpNOP(*this, AddressingMode::Implicit);

	// ORA
	InstructionTable[0x01] = new CpuInstructionOpORA(*this, AddressingMode::IndirectX);
	InstructionTable[0x05] = new CpuInstructionOpORA(*this, AddressingMode::ZeroPage);
	InstructionTable[0x09] = new CpuInstructionOpORA(*this, AddressingMode::Immediate);
	InstructionTable[0x0D] = new CpuInstructionOpORA(*this, AddressingMode::Absolute);
	InstructionTable[0x11] = new CpuInstructionOpORA(*this, AddressingMode::IndirectY);
	InstructionTable[0x15] = new CpuInstructionOpORA(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x19] = new CpuInstructionOpORA(*this, AddressingMode::AbsoluteY);
	InstructionTable[0x1D] = new CpuInstructionOpORA(*this, AddressingMode::AbsoluteX);

	// PHA
	InstructionTable[0x48] = new CpuInstructionOpPHA(*this, AddressingMode::Implicit);

	// PHP
	InstructionTable[0x08] = new CpuInstructionOpPHP(*this, AddressingMode::Implicit);

	// PLA
	InstructionTable[0x68] = new CpuInstructionOpPLA(*this, AddressingMode::Implicit);

	// PLP
	InstructionTable[0x28] = new CpuInstructionOpPLP(*this, AddressingMode::Implicit);

	// ROL
	InstructionTable[0x26] = new CpuInstructionOpROL(*this, AddressingMode::ZeroPage);
	InstructionTable[0x2A] = new CpuInstructionOpROL(*this, AddressingMode::Accumulator);
	InstructionTable[0x2E] = new CpuInstructionOpROL(*this, AddressingMode::Absolute);
	InstructionTable[0x36] = new CpuInstructionOpROL(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x3E] = new CpuInstructionOpROL(*this, AddressingMode::AbsoluteX);

	// ROR
	InstructionTable[0x66] = new CpuInstructionOpROR(*this, AddressingMode::ZeroPage);
	InstructionTable[0x6A] = new CpuInstructionOpROR(*this, AddressingMode::Accumulator);
	InstructionTable[0x6E] = new CpuInstructionOpROR(*this, AddressingMode::Absolute);
	InstructionTable[0x76] = new CpuInstructionOpROR(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x7E] = new CpuInstructionOpROR(*this, AddressingMode::AbsoluteX);

	// RTI
	InstructionTable[0x40] = new CpuInstructionOpRTI(*this, AddressingMode::Implicit);

	// RTS
	InstructionTable[0x60] = new CpuInstructionOpRTS(*this, AddressingMode::Implicit);

	// SBC
	InstructionTable[0xE1] = new CpuInstructionOpSBC(*this, AddressingMode::IndirectX);
	InstructionTable[0xE5] = new CpuInstructionOpSBC(*this, AddressingMode::ZeroPage);
	InstructionTable[0xE9] = new CpuInstructionOpSBC(*this, AddressingMode::Immediate);
	InstructionTable[0xED] = new CpuInstructionOpSBC(*this, AddressingMode::Absolute);
	InstructionTable[0xF1] = new CpuInstructionOpSBC(*this, AddressingMode::IndirectY);
	InstructionTable[0xF5] = new CpuInstructionOpSBC(*this, AddressingMode::ZeroPageX);
	InstructionTable[0xFD] = new CpuInstructionOpSBC(*this, AddressingMode::AbsoluteX);
	InstructionTable[0xF9] = new CpuInstructionOpSBC(*this, AddressingMode::AbsoluteY);

	// SEC
	InstructionTable[0x38] = new CpuInstructionOpSEC(*this, AddressingMode::Implicit);

	// SED
	InstructionTable[0xF8] = new CpuInstructionOpSED(*this, AddressingMode::Implicit);

	// SEI
	InstructionTable[0x78] = new CpuInstructionOpSEI(*this, AddressingMode::Implicit);

	// STA
	InstructionTable[0x81] = new CpuInstructionOpSTA(*this, AddressingMode::IndirectX);
	InstructionTable[0x85] = new CpuInstructionOpSTA(*this, AddressingMode::ZeroPage);
	InstructionTable[0x8D] = new CpuInstructionOpSTA(*this, AddressingMode::Absolute);
	InstructionTable[0x91] = new CpuInstructionOpSTA(*this, AddressingMode::IndirectY);
	InstructionTable[0x95] = new CpuInstructionOpSTA(*this, AddressingMode::ZeroPageX);
	InstructionTable[0x99] = new CpuInstructionOpSTA(*this, AddressingMode::AbsoluteY);
	InstructionTable[0x9D] = new CpuInstructionOpSTA(*this, AddressingMode::AbsoluteX);

	// STX
	InstructionTable[0x86] = new CpuInstructionOpSTX(*this, AddressingMode::ZeroPage);
	InstructionTable[0x8E] = new CpuInstructionOpSTX(*this, AddressingMode::Absolute);
	InstructionTable[0x96] = new CpuInstructionOpSTX(*this, AddressingMode::ZeroPageY);

	// STY
	InstructionTable[0x84] = new CpuInstructionOpSTY(*this, AddressingMode::ZeroPage);
	InstructionTable[0x8C] = new CpuInstructionOpSTY(*this, AddressingMode::Absolute);
	InstructionTable[0x94] = new CpuInstructionOpSTY(*this, AddressingMode::ZeroPageX);

	// TAX
	InstructionTable[0xAA] = new CpuInstructionOpTAX(*this, AddressingMode::Implicit);

	// TAY
	InstructionTable[0xA8] = new CpuInstructionOpTAY(*this, AddressingMode::Implicit);

	// TSX
	InstructionTable[0xBA] = new CpuInstructionOpTSX(*this, AddressingMode::Implicit);

	// TXA
	InstructionTable[0x8A] = new CpuInstructionOpTXA(*this, AddressingMode::Implicit);

	// TXS
	InstructionTable[0x9A] = new CpuInstructionOpTXS(*this, AddressingMode::Implicit);

	// TYA
	InstructionTable[0x98] = new CpuInstructionOpTYA(*this, AddressingMode::Implicit);
}

void nes::CPU::DeallocateInstructionTable()
{
	for (const auto& instruction : InstructionTable)
	{
		if (instruction.second)
		{
			delete instruction.second;
		}
	}

	InstructionTable.clear();
}

void nes::CPU::ProcessOpCode(Byte opCode)
{
	// Execute the instruction
	// The instruction moves the program counter and updates the current cycle
	CpuInstructionBase* instruction = InstructionTable[opCode.value];
	if (instruction != nullptr)
	{
		instruction->PrintDebugInformation();
		instruction->Execute();
	}
}

void nes::CPU::PushStack(Byte value)
{
	// Stack grows downwards
	std::uint16_t address = RamRef.STACK_START_ADDRESS - SP.value;
	RamRef.WriteByte(address, value);

	// Move stack pointer
	--SP.value;
}

nes::Byte nes::CPU::PopStack()
{
	// Move stack pointer
	++SP.value;

	// Stack grows downwards
	std::uint16_t address = RamRef.STACK_START_ADDRESS - SP.value;
	Byte value = RamRef.ReadByte(address);

	// Clear value from stack
	RamRef.ClearByte(address);

	return value;
}

void nes::CPU::SetStatusFlag(StatusFlags flag)
{
	P.value |= static_cast<std::uint8_t>(flag);
}

void nes::CPU::ClearStatusFlag(StatusFlags flag)
{
	P.value &= ~static_cast<std::uint8_t>(flag);
}

bool nes::CPU::IsStatusFlagSet(StatusFlags flag) const
{
	return ((P.value & static_cast<std::uint8_t>(flag)) != 0);
}

bool nes::CPU::IsStatusFlagClear(StatusFlags flag) const
{
	return ((P.value & static_cast<std::uint8_t>(flag)) == 0);
}

void nes::CPU::UpdateZeroStatusFlag(Byte byte)
{
	P.bit1 = (byte.value == 0) ? 1 : 0;
}

void nes::CPU::UpdateNegativeStatusFlag(Byte byte)
{
	P.bit7 = IsNthBitSet(byte, 7) ? 1 : 0;
}
