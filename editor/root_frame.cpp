#include "root_frame.hpp"
#include "debugging/debug_notebook.hpp"
#include "editor_logger.hpp"

#include <wx/checkbox.h>
#include <wx/menu.h>
#include <wx/sizer.h>

nes::EditorRootFrame::EditorRootFrame(const wxString& title) :
	wxFrame(nullptr, wxID_ANY, title),
	AutoScrollCheckbox(new wxCheckBox(this, wxID_JUMP_TO, "Auto Scroll")),
	StatusBar(CreateStatusBar()),
	LogNotebook(new DebugNotebook(this))
{
	AutoScrollCheckbox->SetValue(true);
	LogNotebook->AutoScrollAllLogs(true);

	auto* vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(AutoScrollCheckbox);
	vbox->Add(LogNotebook, 1, wxEXPAND);

	SetSizer(vbox);
	AppendMainMenuBar();
	BindEvents();

	StatusBar->SetStatusText("Application initialized");
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
	fileMenu->Append(wxID_FILE, "&Open ROM");

	return fileMenu;
}

wxMenu* const nes::EditorRootFrame::ConstructHelpMenu() const
{
	auto* const helpMenu = new wxMenu();
	helpMenu->Append(wxID_ANY, "Version");
	helpMenu->Append(wxID_ANY, "About");

	return helpMenu;
}

void nes::EditorRootFrame::BindEvents()
{
	Connect(wxID_FILE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(EditorRootFrame::OnLoadRom));
	Connect(wxID_JUMP_TO, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(EditorRootFrame::OnAutoScrollUpdate));
}

void nes::EditorRootFrame::OnLoadRom(wxCommandEvent& event)
{
	EditorLogger::GetInstance().LogInformation("Press ROM LOAD");
}

void nes::EditorRootFrame::OnAutoScrollUpdate(wxCommandEvent& event)
{
	LogNotebook->AutoScrollAllLogs(AutoScrollCheckbox->GetValue());
}
