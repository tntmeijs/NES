#ifndef NES_EDITOR_DEBUG_NOTEBOOK_HPP
#define NES_EDITOR_DEBUG_NOTEBOOK_HPP

#include <wx/notebook.h>

class wxWindow;

namespace nes
{
	class DebugNotebookPage;

	/**
	 * Editor panel meant to be shown at the bottom of the window
	 * Contains a notebook with tabs for easy access to the redirected input and
	 * error streams
	 */
	class DebugNotebook final : public wxNotebook
	{
	public:
		/**
		 * Create a new notebook panel and all its widgets
		 * @param	parent	Parent that holds this notebook
		 */
		DebugNotebook(wxWindow* const parent);

		/**
		 * Set all information logs to automatically scroll
		 * @param	scroll		True to automatically scroll, false to disable
		 */
		void AutoScrollAllLogs(bool scroll) const;

	private:
		/**
		 * Register the log debug pages to the events of the editor logger
		 */
		void ListenForLogs() const;

	private:
		DebugNotebookPage* const InformationLog;
		DebugNotebookPage* const WarningLog;
		DebugNotebookPage* const ErrorLog;
		DebugNotebookPage* const DebugLog;
	};
}

#endif //! NES_EDITOR_DEBUG_NOTEBOOK_HPP
