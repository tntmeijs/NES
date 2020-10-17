#ifndef NES_CPU_STATUS_FLAGS_HPP
#define NES_CPU_STATUS_FLAGS_HPP

namespace nes
{
    /**
     * All processor status flags
     */
    enum class StatusFlags
    {
        Carry               = (1 << 0),
        Zero                = (1 << 1),
        InterruptDisable    = (1 << 2),
        DecimalMode         = (1 << 3),
        Overflow            = (1 << 6),
        Negative            = (1 << 7)
    };
}

#endif //! NES_CPU_STATUS_FLAGS_HPP
