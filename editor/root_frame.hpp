#ifndef NES_EDITOR_ROOT_FRAME_HPP
#define NES_EDITOR_ROOT_FRAME_HPP

#include "editor_service.hpp"

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

		/**
		 * Deallocate resources
		 */
		~EditorRootFrame();

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

		/**
		 * Bind functions to events
		 */
		void BindEvents();

		/**
		 * Make all log output go to the status bar
		 */
		void BindLogToStatusBar() const;

	private:
		/**
		 * Called whenever a user wants to load a ROM file from disk
		 * @param	event	WxWidgets event
		 */
		void OnLoadRom(wxCommandEvent& event);

		/**
		 * Called whenever a user wants to change the log automatic scroll setting
		 * @param	event	WxWidgets event
		 */
		void OnAutoScrollUpdate(wxCommandEvent& event);

	private:
		EditorService Editor;

		wxPanel* const MainPanel;
		wxCheckBox* const AutoScrollCheckbox;
		wxStatusBar* const StatusBar;

		DebugNotebook* const LogNotebook;
	};
}

#endif //! NES_EDITOR_ROOT_FRAME_HPP
