#ifndef NES_OBJECT_ID
#define NES_OBJECT_ID

#include <cstdint>

namespace nes
{
    /**
     * Any class that inherits from this class gets its own unique ID
     */
    class ObjectID
    {
    public:
        /**
         * Generate a new ID
         */
        ObjectID()
        {
            // Keep a global ID variable to allow for easy ID generation
            static std::uint64_t idTracker = 0;
            ElementID = idTracker++;
        }

    protected:
        std::uint64_t ElementID;
    };
}

#endif //! NES_OBJECT_ID
