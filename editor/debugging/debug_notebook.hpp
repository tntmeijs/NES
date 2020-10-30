#ifndef NES_EDITOR_DEBUG_NOTEBOOK_HPP
#define NES_EDITOR_DEBUG_NOTEBOOK_HPP

#include <wx/notebook.h>

#include <string_view>

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
		 * Log an informational message to the console
		 * @param	info	Message to log
		 */
		void LogInfo(std::string_view info);

		/**
		 * Log a warning message to the console
		 * @param	warning		Message to log
		 */
		void LogWarning(std::string_view warning);

		/**
		 * Log an error message to the console
		 * @param	error	Message to log
		 */
		void LogError(std::string_view error);

	private:
		DebugNotebookPage* const InformationLog;
		DebugNotebookPage* const WarningLog;
		DebugNotebookPage* const ErrorLog;
	};
}

#endif //! NES_EDITOR_DEBUG_NOTEBOOK_HPP
