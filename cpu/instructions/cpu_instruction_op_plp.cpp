#include "cpu_instruction_op_plp.hpp"
#include "cpu/cpu.hpp"
#include "utility/bit_tools.hpp"

nes::CpuInstructionOpPLP::CpuInstructionOpPLP(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "PLP")
{}

void nes::CpuInstructionOpPLP::ExecuteImpl()
{
	std::uint8_t fromStack = CpuRef.PopStack();

	MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 0);
	MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 1);
	MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 2);
	MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 3);
	MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 6);
	MatchBitStateOfNthBit(CpuRef.P.value, fromStack, 7);

	CycleCount = 4;
}
