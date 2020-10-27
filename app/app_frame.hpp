#ifndef NES_APP_FRAME_HPP
#define NES_APP_FRAME_HPP

#include <wx/frame.h>
#include <wx/string.h>

#include <cstdint>
#include <string_view>

class wxMenu;

namespace nes
{
	/**
	 * Main frame of the GUI application
	 */
	class NesEmulatorApplicationFrame final : public wxFrame
	{
	public:
		/**
		 * Create a new application frame
		 * @param	title	Title of the application
		 */
		NesEmulatorApplicationFrame(const wxString& title);

	private:
		/**
		 * Create the items for the file menu
		 * @return	File menu
		 */
		wxMenu* const ConstructFileMenu() const;

		/**
		 * Create the items for the debug menu
		 * @return	Debug menu
		 */
		wxMenu* const ConstructDebugMenu() const;

		/**
		 * Create the items for the help menu
		 * @return	Help menu
		 */
		wxMenu* const ConstructHelpMenu() const;
	};
}

#endif //! NES_APP_FRAME_HPP
