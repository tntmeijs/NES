#ifndef NES_CPU_INSTRUCTION_BASE_HPP
#define NES_CPU_INSTRUCTION_BASE_HPP

namespace nes
{
	class CPU;

	/**
	 * Abstract base class for each CPU instruction
	 */
	class CpuInstructionBase
	{
	public:
		/**
		 * Create a new CPU instruction
		 * @param	cpuRef	Reference to the CPU object
		 */
		CpuInstructionBase(CPU& cpuRef);

		CpuInstructionBase(const CpuInstructionBase& other)				= default;
		CpuInstructionBase(CpuInstructionBase&& other)					= default;
		CpuInstructionBase& operator=(const CpuInstructionBase& other)	= default;
		CpuInstructionBase& operator=(CpuInstructionBase&& other)		= default;
		virtual ~CpuInstructionBase()									= default;

		/**
		 * Override this function with the instruction's logic
		 */
		virtual void Execute() = 0;

	protected:
		CPU& CpuRef;
	};
}

#endif //! NES_CPU_INSTRUCTION_BASE_HPP
