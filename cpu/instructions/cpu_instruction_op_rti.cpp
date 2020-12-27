#include "cpu_instruction_op_rti.hpp"
#include "cpu/cpu.hpp"
#include "cpu/cpu_status_flags.hpp"
#include "utility/bit_tools.hpp"

nes::CpuInstructionOpRTI::CpuInstructionOpRTI(CPU& cpuRef, AddressingMode addressingMode) :
	CpuInstructionBase(cpuRef, addressingMode, "RTI")
{
	AutoUpdateProgramCounter = false;
}

void nes::CpuInstructionOpRTI::ExecuteImpl()
{
	CycleCount = 6;

	CpuRef.P = (CpuRef.PopStack());
	CpuRef.P.value |= static_cast<std::uint8_t>(StatusFlags::Constant);

	Byte lsb = CpuRef.PopStack();
	Byte msb = CpuRef.PopStack();
	CpuRef.PC = ConstructAddressFromBytes(msb, lsb);
}
