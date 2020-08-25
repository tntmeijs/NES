#ifndef NES_UI_ELEMENT_HPP
#define NES_UI_ELEMENT_HPP

#include "utility/object_id.hpp"

namespace nes
{
    /**
     * Abstract base class for all UI elements
     */
    class UIElement : public ObjectID
    {
    public:
        /**
         * Record UI draw commands
         */
        virtual void Draw() const = 0;
    };
}

#endif //! NES_UI_ELEMENT_HPP
