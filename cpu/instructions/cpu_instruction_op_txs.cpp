#include "cpu_instruction_op_txs.hpp"
#include "cpu/cpu.hpp"

nes::CpuInstructionOpTXS::CpuInstructionOpTXS(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "TXS")
{}

void nes::CpuInstructionOpTXS::ExecuteImpl()
{
	CpuRef.SP = CpuRef.X;
	CycleCount = 2;
}
