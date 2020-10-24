#include "cpu_instruction_op_asl.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpASL::CpuInstructionOpASL(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "ASL")
{}

void nes::CpuInstructionOpASL::ExecuteImpl()
{
	std::uint8_t old = CpuRef.A;
	CpuRef.A = (CpuRef.A << 1);

	// Set carry to the old contents of bit 7
	if ((old & static_cast<std::uint8_t>(StatusFlags::Negative)) != 0)
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
