#ifndef NES_CPU_HPP
#define NES_CPU_HPP

#include <cstdint>

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
         * Create a new CPU object
         * @param   ramRef  Reference to the RAM
         */
        CPU(const RAM& ramRef);

        // DEBUG CODE, JUST NEED A WAY TO RUN THIS CODE FROM main.cpp
        void Entry();

        /**
         * Step to the next instruction and process it
         */
        void NextInstruction();

        /**
         * Get the current value of the program counter
         * @return  Current value of the program counter
         */
        const std::uint16_t GetProgramCounter() const;

    private:
        /**
         * All possible addressing modes
         */
        enum class AddressingMode
        {
            Absolute,
            AbsoluteX,
            AbsoluteY,
            Accumulator,
            Immediate,
            Implicit,
            Indirect,
            IndirectX,
            IndirectY,
            Relative,
            ZeroPage,
            ZeroPageX,
            ZeroPageY,
        };

    private:
        // DEBUG CODE, READ WHATEVER BYTE IS AT THE PC
        char ReadAtPC();

        void ADC(AddressingMode mode);
        void AND(AddressingMode mode);
        void ASL(AddressingMode mode);
        void BCC(AddressingMode mode);
        void BCS(AddressingMode mode);
        void BEQ(AddressingMode mode);
        void BIT(AddressingMode mode);
        void BMI(AddressingMode mode);
        void BNE(AddressingMode mode);
        void BPL(AddressingMode mode);
        void BRK(AddressingMode mode);
        void BVC(AddressingMode mode);
        void BVS(AddressingMode mode);
        void CLC(AddressingMode mode);
        void CLD(AddressingMode mode);
        void CLI(AddressingMode mode);
        void CLV(AddressingMode mode);
        void CMP(AddressingMode mode);
        void CPX(AddressingMode mode);
        void CPY(AddressingMode mode);
        void DEC(AddressingMode mode);
        void DEX(AddressingMode mode);
        void DEY(AddressingMode mode);
        void EOR(AddressingMode mode);
        void INC(AddressingMode mode);
        void INX(AddressingMode mode);
        void INY(AddressingMode mode);
        void JMP(AddressingMode mode);
        void JSR(AddressingMode mode);
        void LDA(AddressingMode mode);
        void LDX(AddressingMode mode);
        void LDY(AddressingMode mode);
        void LSR(AddressingMode mode);
        void NOP(AddressingMode mode);
        void ORA(AddressingMode mode);
        void PHA(AddressingMode mode);
        void PHP(AddressingMode mode);
        void PLA(AddressingMode mode);
        void PLP(AddressingMode mode);
        void ROL(AddressingMode mode);
        void ROR(AddressingMode mode);
        void RTI(AddressingMode mode);
        void RTS(AddressingMode mode);
        void SBC(AddressingMode mode);
        void SEC(AddressingMode mode);
        void SED(AddressingMode mode);
        void SEI(AddressingMode mode);
        void STA(AddressingMode mode);
		void STX(AddressingMode mode);
		void STY(AddressingMode mode);
        void TAX(AddressingMode mode);
        void TAY(AddressingMode mode);
        void TSX(AddressingMode mode);
        void TXA(AddressingMode mode);
        void TXS(AddressingMode mode);
        void TYA(AddressingMode mode);

    private:
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
        // Lives in address 0x100 to 0x1FF
        // Wraps around when its capacity is exceeded
        std::uint8_t S;

        // Program counter
        std::uint16_t PC;

        // RAM
        const RAM& RamRef;
    };
}

#endif //! NES_CPU_HPP
