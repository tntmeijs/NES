#ifndef NES_GLOBALS_HPP
#define NES_GLOBALS_HPP

#include <string_view>

namespace nes
{
    /**
     * Static class that holds global information about the project
     */
    class Globals final
    {
    public:
        /** Version information text that will be displayed in the version dialog */
		static constexpr std::string_view DIALOG_VERSION_INFO = "Unreleased version.\nPlease check back later.";

        /** Information that will be displayed in the about dialog */
        static constexpr std::string_view DIALOG_ABOUT_INFO = "Found an issue?\nPlease report it here: https://github.com/tntmeijs/NES";

    private:
        Globals();
    };
}

#endif //! NES_GLOBALS_HPP
