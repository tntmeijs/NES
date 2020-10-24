#include "cpu_instruction_op_plp.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpPLP::CpuInstructionOpPLP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "PLP")
{}

void nes::CpuInstructionOpPLP::ExecuteImpl()
{
	std::uint8_t fromStack = CpuRef.PopStack();

	CpuRef.MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 0);
	CpuRef.MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 1);
	CpuRef.MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 2);
	CpuRef.MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 3);
	CpuRef.MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 6);
	CpuRef.MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 7);

	CycleCount = 4;
}
