#ifndef NES_CPU_HPP
#define NES_CPU_HPP

#include "cpu_logger.hpp"
#include "flags/cpu_status_flags.hpp"
#include "instructions/cpu_instruction_addressing_mode.hpp"

#include <cstdint>
#include <string_view>
#include <unordered_map>

namespace nes
{
    class RAM;

    /**
     * Emulates a MOS Technology 6502 microprocessor as seen in the NES
     */
    class CPU
    {
    public:
        /**
         * Check if a 256-byte page boundary was crossed between two addresses
         * @param   before  Initial address
         * @param   after   Address to check against
         * @return  True when a page boundary was crossed, false when not
         */
        static bool DidProgramCounterCrossPageBoundary(std::uint16_t before, std::uint16_t after);

    public:
        /**
         * All available registers
         */
        enum class RegisterType
        {
            A,  // A register
            X,  // X register
            Y,  // Y register
            P,  // P register (flags)
            SP  // Stack pointer
        };

    public:
        /**
         * Create a new CPU object
         * @param   ramRef  Reference to the RAM
         */
        CPU(RAM& ramRef);

        CPU(const CPU& other)               = default;
        CPU(CPU&& other)                    = default;
        CPU& operator=(const CPU& other)    = default;
        CPU& operator=(CPU&& other)         = default;

        /**
         * Deallocate any used resources
         */
        ~CPU();

        /**
         * Reset the vector back to the default memory address
         * This address is given by the reset vector at 0xFFFD and 0xFFFC
         */
        void SetProgramCounterToResetVector();

        /**
         * Manually move the program counter to a specific address in memory
         * @param   address     Address to set the program counter to
         */
        void SetProgramCounterToAddress(std::uint16_t address);

        /**
         * Fetch the opcode at the program counter and attempt to execute the
         * instruction
         */
        void ExecuteInstruction();

        /**
         * Manually move the program counter N number of bytes relative to its
         * current memory address
         * @param   offset  Number of bytes to move the program counter
         */
        void MoveProgramCounter(std::int32_t offset);

        /**
         * Update the current cycle index
         * @param   offset  Number of cycles to add to the current cycle
         */
        void UpdateCurrentCycle(std::uint8_t offset);

        /**
         * Returns the value of the byte in RAM at the specified address
         * @param   address     Address to read from
         * @return  Value of the byte in RAM
         */
        std::uint8_t ReadRamValueAtAddress(std::uint16_t address) const;

        /**
         * Write a byte to RAM at the specified address
         * @param   address     Address to write to
         * @param   value       Value to write to RAM
         */
        void WriteRamValueAtAddress(std::uint16_t address, std::uint8_t value) const;

        /**
         * Get the current value of the program counter accounting for the offset
         * in RAM
         * @return  Current value of the program counter
         */
        std::uint16_t GetProgramCounter() const;

        /**
         * Get the current value of the stack pointer
         * @return  Current value of the stack pointer
         */
        std::uint16_t GetStackPointer() const;

        /**
         * Retrieve the value of a register
         * @param   type    Register to retrieve its value for
         * @return  Register's value
         */
        std::uint8_t GetRegister(RegisterType type) const;

        /**
         * Retrieve the current cycle index
         * @return  Current cycle
         */
        std::uint64_t GetCurrentCycle() const;

        /**
         * Reset the CPU to its default state
         */
        void SetDefaultState();

        /**
         * Retrieve the target address of an instruction based on the addressing
         * mode specified
         * @param   mode    Addressing mode to use
         * @return  Target address of the instruction
         */
        std::uint16_t GetTargetAddress(AddressingMode mode) const;

    private:
        /**
         * Create a look-up table for all instructions
         */
        void AllocateInstructionTable();

        /**
         * Deallocate the look-up table for instructions
         */
        void DeallocateInstructionTable();

        /**
         * Execute the proper op-code
         * @param   opCode  Op-code to execute
         */
        void ProcessOpCode(std::uint8_t opCode);

        /**
         * Push a value to the stack
         * @param   value   Value to push to the stack
         */
        void PushStack(std::uint8_t value);

        /**
         * Pop a value from the stack
         * @return  Value popped from the stack
         */
        std::uint8_t PopStack();

        /**
         * Set a processor status flag
         * @param   flag    Flag to set
         */
        void SetStatusFlag(StatusFlags flag);

        /**
         * Clear a processor status flag
         * @param   flag    Flag to clear
         */
        void ClearStatusFlag(StatusFlags flag);

        /**
         * Check if a status flag has been set
         * @param   flag    Flag to check
         * @return  True when the flag is set, false when clear
         */
        bool IsStatusFlagSet(StatusFlags flag) const;

        /**
         * Check if a status flag has been cleared
		 * @param   flag    Flag to check
		 * @return  True when the flag is clear, false when set
         */
        bool IsStatusFlagClear(StatusFlags flag) const;

        /**
         * Check if bit N has been set
         * @param   byte    Byte to check
         * @param   n       Bit to check
         * @return  True when the flag is set, false when clear
         */
		bool IsNthBitSet(std::uint8_t byte, std::uint8_t n) const;

        /**
         * Check if bit N has been cleared
         * @param   byte    Byte to check
         * @param   n       Bit to check
         * @return  True when the flag is clear, false when set
         */
        bool IsNthBitClear(std::uint8_t byte, std::uint8_t n) const;

        /**
         * Set a bit when the input bit is set, clear a bit when the input bit is
         * clear. This is useful when matching bits at specific indices.
         * @param   target  Byte whose bits will be updated
         * @param   source  Byte whose bits will be compared against
         * @param   n       Bit index to compare
         */
        void MatchBitStateOfNthBit(std::uint8_t& target, std::uint8_t source, std::uint8_t n) const;

        /**
         * Set or clear the zero flag based on the value of the byte passed
         * @param   byte    Byte to check
         */
        void UpdateZeroStatusFlag(std::uint8_t byte);

        /**
         * Set or clear the negative flag based on the value of the byte passed
         * @param   byte    Byte to check
         */
        void UpdateNegativeStatusFlag(std::uint8_t byte);

    private:
        // Give all instructions access to the private and protected members of CPU
        // Friend classes are quite useful here as the instructions would be a massive
        // pain to write if we were to use getter and setter functions only
		friend class CpuInstructionBase;
		friend class CpuInstruction;
		friend class CpuInstructionOpADC;
		friend class CpuInstructionOpAND;
		friend class CpuInstructionOpASL;
		friend class CpuInstructionOpBCC;
		friend class CpuInstructionOpBCS;
		friend class CpuInstructionOpBEQ;
		friend class CpuInstructionOpBIT;
		friend class CpuInstructionOpBMI;
		friend class CpuInstructionOpBNE;
		friend class CpuInstructionOpBPL;
		friend class CpuInstructionOpBRK;
		friend class CpuInstructionOpBVC;
		friend class CpuInstructionOpBVS;
		friend class CpuInstructionOpCLC;
		friend class CpuInstructionOpCLD;
		friend class CpuInstructionOpCLI;
		friend class CpuInstructionOpCLV;
		friend class CpuInstructionOpCMP;
		friend class CpuInstructionOpCPX;
		friend class CpuInstructionOpCPY;
		friend class CpuInstructionOpDEC;
		friend class CpuInstructionOpDEX;
		friend class CpuInstructionOpDEY;
		friend class CpuInstructionOpEOR;
		friend class CpuInstructionOpINC;
		friend class CpuInstructionOpINX;
		friend class CpuInstructionOpINY;
		friend class CpuInstructionOpJMP;
		friend class CpuInstructionOpJSR;
		friend class CpuInstructionOpLDA;
		friend class CpuInstructionOpLDX;
		friend class CpuInstructionOpLDY;
		friend class CpuInstructionOpLSR;
		friend class CpuInstructionOpNOP;
		friend class CpuInstructionOpORA;
		friend class CpuInstructionOpPHA;
		friend class CpuInstructionOpPHP;
		friend class CpuInstructionOpPLA;
		friend class CpuInstructionOpPLP;
		friend class CpuInstructionOpROL;
		friend class CpuInstructionOpROR;
		friend class CpuInstructionOpRTI;
		friend class CpuInstructionOpRTS;
		friend class CpuInstructionOpSBC;
		friend class CpuInstructionOpSEC;
		friend class CpuInstructionOpSED;
		friend class CpuInstructionOpSEI;
		friend class CpuInstructionOpSTA;
		friend class CpuInstructionOpSTX;
		friend class CpuInstructionOpSTY;
		friend class CpuInstructionOpTAX;
		friend class CpuInstructionOpTAY;
		friend class CpuInstructionOpTSX;
		friend class CpuInstructionOpTXA;
		friend class CpuInstructionOpTXS;
		friend class CpuInstructionOpTYA;

        // Accumulator
        std::uint8_t A;

        // Index registers
        std::uint8_t X;
        std::uint8_t Y;

        // Processor status flag bits
        // 0 - carry flag
        // 1 - zero flag
        // 2 - interrupt disable
        // 3 - decimal mode (enable BCD mode) does not affect the 2A03
        // 4 - break command
        // 5 - unused bit
        // 6 - overflow flag
        // 7 - negative flag
        std::uint8_t P;

        // Stack pointer
        std::uint8_t SP;

        // Program counter
        std::uint16_t PC;

        // RAM
        RAM& RamRef;

        // CPU logger
        CpuLogger Logger;

        // Keep track of the current CPU cycle to allow for synchronization
        std::uint64_t CurrentCycle;

        // Look-up table for instructions
        std::unordered_map<std::uint16_t, CpuInstructionBase*> InstructionTable;
    };
}

#endif //! NES_CPU_HPP
