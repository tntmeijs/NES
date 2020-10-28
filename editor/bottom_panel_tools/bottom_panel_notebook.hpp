#ifndef NES_EDITOR_BOTTOM_PANEL_NOTEBOOK_HPP
#define NES_EDITOR_BOTTOM_PANEL_NOTEBOOK_HPP

#include <wx/notebook.h>

class wxWindow;

namespace nes
{
	/**
	 * Editor panel meant to be shown at the bottom of the window
	 * Contains a notebook with tabs for easy access to the redirected input and
	 * error streams
	 */
	class BottomPanelNotebook final : public wxNotebook
	{
	public:
		/**
		 * Create a new notebook panel and all its widgets
		 * @param	parent	Parent that holds this notebook
		 */
		BottomPanelNotebook(wxWindow* const parent);
	};
}

#endif //! NES_EDITOR_BOTTOM_PANEL_NOTEBOOK_HPP
