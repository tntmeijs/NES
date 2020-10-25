#include "cpu_instruction_op_bvs.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpBVS::CpuInstructionOpBVS(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "BVS")
{}

void nes::CpuInstructionOpBVS::ExecuteImpl()
{
	CycleCount = 2;

	// Overflow flag is set
	if (CpuRef.IsStatusFlagSet(StatusFlags::Overflow))
	{
		std::int8_t displacement = CpuRef.ReadRamValueAtAddress(CpuRef.PC + 1).value;

		std::uint16_t initialPC = CpuRef.PC;
		std::uint16_t currentPC = initialPC + displacement;

		// Perform branching
		CpuRef.MoveProgramCounter(displacement);

		if (CpuRef.DidProgramCounterCrossPageBoundary(initialPC, currentPC))
		{
			CycleCount += 2;
		}
		else
		{
			CycleCount += 1;
		}
	}
}
