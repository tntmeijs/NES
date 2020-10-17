#ifndef NES_CPU_B_FLAGS_HPP
#define NES_CPU_B_FLAGS_HPP

namespace nes
{
    /**
     * "B flags" as described here:
     * https://wiki.nesdev.com/w/index.php/Status_flags#The_B_flag
     */
    enum class BFlag
    {
        Instruction = ((1 << 4) | (1 << 5)),
        Interrupt = (1 << 5)
    };
}

#endif //! NES_CPU_B_FLAGS_HPP
