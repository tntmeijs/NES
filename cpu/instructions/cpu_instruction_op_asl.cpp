#include "cpu_instruction_op_asl.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

nes::CpuInstructionOpASL::CpuInstructionOpASL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ASL")
{}

void nes::CpuInstructionOpASL::ExecuteImpl()
{
	std::uint8_t old = CpuRef.A.value;
	CpuRef.A.value = (CpuRef.A.value << 1);

	// Set carry to the old contents of bit 7
	if (IsNthBitSet(old, static_cast<std::uint8_t>(StatusFlags::Negative)))
	{
		CpuRef.SetStatusFlag(StatusFlags::Carry);
	}
	else
	{
		CpuRef.ClearStatusFlag(StatusFlags::Carry);
	}

	CpuRef.UpdateZeroStatusFlag(CpuRef.A);
	CpuRef.UpdateNegativeStatusFlag(CpuRef.A);
}
