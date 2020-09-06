#ifndef NES_UI_ROM_BROWSER_HPP
#define NES_UI_ROM_BROWSER_HPP

#include <functional>
#include <string>

namespace nes
{
	/**
	 * Editor UI element that allows users to load ROMs
	 * This element does not create an ImGui window, therefore, it is expected to
	 * either be part of an existing window, or a menu bar
	 */
	class UIRomBrowser
	{
	public:
		/**
		 * Callback that fires whenever a ROM should be loaded
		 * @param	romPath		Absolute path to the ROM file that should be loaded
		 */
		std::function<void(const std::string& romPath)> OnLoadRom;

	public:
		/**
		 * Render the UI for this panel
		 */
		void Draw() const;
	};
}

#endif //! NES_UI_ROM_BROWSER_HPP
