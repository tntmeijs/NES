#ifndef NES_EDITOR_SERVICE_HPP
#define NES_EDITOR_SERVICE_HPP

namespace nes
{
    /**
     * Contains all editor business logic
     * UI is handled by the @see EditorRootFrame instead
     */
    class EditorService final
    {
    public:
        /**
         * Allocate resources and set initial states
         */
        bool Initialize();
    };
}

#endif //! NES_EDITOR_SERVICE_HPP
