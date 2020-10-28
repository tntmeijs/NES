#include "root_frame.hpp"
#include "debugging/debug_notebook.hpp"

#include <wx/menu.h>

nes::EditorRootFrame::EditorRootFrame(const wxString& title) :
	wxFrame(nullptr, wxID_ANY, title)
{
	AppendMainMenuBar();

	auto* bottomPanel = new DebugNotebook(this);
}

void nes::EditorRootFrame::AppendMainMenuBar()
{
	auto* const mainMenuBar = new wxMenuBar();
	mainMenuBar->Append(ConstructFileMenu(), "&File");
	mainMenuBar->Append(ConstructHelpMenu(), "&Help");
	SetMenuBar(mainMenuBar);
}

wxMenu* const nes::EditorRootFrame::ConstructFileMenu() const
{
	auto* const fileMenu = new wxMenu();
	fileMenu->Append(wxID_ANY, "&Open ROM");

	return fileMenu;
}

wxMenu* const nes::EditorRootFrame::ConstructHelpMenu() const
{
	auto* const helpMenu = new wxMenu();
	helpMenu->Append(wxID_ANY, "Version");
	helpMenu->Append(wxID_ANY, "About");

	return helpMenu;
}
