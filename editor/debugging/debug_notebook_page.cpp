#include "debug_notebook_page.hpp"

nes::DebugNotebookPage::DebugNotebookPage(wxWindow* const parent) :
	wxListBox(parent, wxID_ANY)
{}

void nes::DebugNotebookPage::Log(std::string_view message)
{
	Append(message.data());
}

void nes::DebugNotebookPage::ClearHistory()
{
	Clear();
}
