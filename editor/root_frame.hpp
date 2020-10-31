#ifndef NES_EDITOR_ROOT_FRAME_HPP
#define NES_EDITOR_ROOT_FRAME_HPP

#include <wx/event.h>
#include <wx/frame.h>
#include <wx/string.h>

#include <cstdint>
#include <string_view>

class wxCheckBox;
class wxMenu;
class wxPanel;
class wxStatusBar;

namespace nes
{
	class DebugNotebook;

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

		void BindEvents();

	private:
		void OnLoadRom(wxCommandEvent& event);

		void OnAutoScrollUpdate(wxCommandEvent& event);

	private:
		wxPanel* const MainPanel;
		wxCheckBox* const AutoScrollCheckbox;
		wxStatusBar* const StatusBar;

		DebugNotebook* const LogNotebook;
	};
}

#endif //! NES_EDITOR_ROOT_FRAME_HPP
