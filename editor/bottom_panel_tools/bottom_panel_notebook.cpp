#include "bottom_panel_notebook.hpp"

nes::BottomPanelNotebook::BottomPanelNotebook(wxWindow* const parent) :
	wxNotebook(parent, wxID_ANY)
{
	AddPage(new wxNotebookPage(this, -1), "stdout");
	AddPage(new wxNotebookPage(this, -1), "stderr");
	Layout();
}
