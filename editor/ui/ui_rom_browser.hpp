#ifndef NES_UI_ROM_BROWSER_HPP
#define NES_UI_ROM_BROWSER_HPP

#include "ui_panel.hpp"

#include <functional>
#include <string>

namespace nes
{
	/**
	 * Editor UI element that allows users to load ROMs
	 */
	class UIRomBrowser : public UIPanel
	{
	public:
		/**
		 * Callback that fires whenever a ROM should be loaded
		 * @param	romPath		Absolute path to the ROM file that should be loaded
		 */
		std::function<void(const std::string& romPath)> OnLoadRom;

	protected:
		/**
		 * Render the UI for this panel
		 */
		virtual void DrawImpl() const override;
	};
}

#endif //! NES_UI_ROM_BROWSER_HPP
