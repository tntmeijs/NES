#ifndef NES_EDITOR_ROOT_FRAME_HPP
#define NES_EDITOR_ROOT_FRAME_HPP

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
	class EditorRootFrame final : public wxFrame
	{
	public:
		/**
		 * Create a new application frame
		 * @param	title	Title of the application
		 */
		EditorRootFrame(const wxString& title);

	private:
		/**
		 * Append the main menu bar to this frame
		 */
		void AppendMainMenuBar();

		/**
		 * Create the items for the file menu
		 * @return	File menu
		 */
		wxMenu* const ConstructFileMenu() const;

		/**
		 * Create the items for the help menu
		 * @return	Help menu
		 */
		wxMenu* const ConstructHelpMenu() const;
	};
}

#endif //! NES_EDITOR_ROOT_FRAME_HPP
