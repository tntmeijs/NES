#include "debug_notebook.hpp"

nes::DebugNotebook::DebugNotebook(wxWindow* const parent) :
	wxNotebook(parent, wxID_ANY)
{
	AddPage(new wxNotebookPage(this, -1), "stdout");
	AddPage(new wxNotebookPage(this, -1), "stderr");
	Layout();
}
