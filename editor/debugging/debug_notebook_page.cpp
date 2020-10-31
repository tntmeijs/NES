#include "debug_notebook_page.hpp"

nes::DebugNotebookPage::DebugNotebookPage(wxWindow* const parent) :
	wxListBox(parent, wxID_ANY),
	AllowAutomaticScroll(true)
{}

void nes::DebugNotebookPage::Log(std::string_view message)
{
	auto index = Append(message.data());

	if (AllowAutomaticScroll)
	{
		EnsureVisible(index);
	}
}

void nes::DebugNotebookPage::ClearHistory()
{
	Clear();
}
