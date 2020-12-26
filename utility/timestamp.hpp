#ifndef NES_UTLITY_TIMESTAMP_HPP
#define NES_UTLITY_TIMESTAMP_HPP

#include <chrono>

namespace nes
{
    /**
     * Generate a new timestamp using the current system time
     * The generated timestamp will have millisecond precision
     * @return  Time since Epoch in milliseconds based off of the system's clock
     */
    inline constexpr long long GenerateUnixTimestamp()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }
}

#endif //! NES_UTILITY_TIMESTAMP_HPP
