#ifndef NES_EDITOR_DEBUG_NOTEBOOK_PAGE_HPP
#define NES_EDITOR_DEBUG_NOTEBOOK_PAGE_HPP

#include <string_view>

#include <wx/listbox.h>

namespace nes
{
    class DebugNotebookPage final : public wxListBox
    {
    public:
        /**
         * Create a new notebook page
         * @param   notebook    Notebook this page belongs to
         */
        DebugNotebookPage(wxWindow* const parent);

        /**
         * Log a message to this page
         * @param   message     Message to log
         */
        void Log(std::string_view message);

        /**
         * Clear all log history
         */
        void ClearHistory();
    };
}

#endif //! NES_EDITOR_DEBUG_NOTEBOOK_PAGE_HPP
