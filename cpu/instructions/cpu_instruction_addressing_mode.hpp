#ifndef NES_CPU_INSTRUCTION_ADDRESSING_MODE_HPP
#define NES_CPU_INSTRUCTION_ADDRESSING_MODE_HPP

namespace nes
{
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
        ZeroPageY
    };
}

#endif //! NES_CPU_INSTRUCTION_ADDRESSING_MODE_HPP
