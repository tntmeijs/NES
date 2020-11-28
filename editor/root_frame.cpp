#include "root_frame.hpp"
#include "debugging/debug_notebook.hpp"
#include "editor_logger.hpp"

#include <wx/checkbox.h>
#include <wx/filedlg.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>

#include <string>

nes::EditorRootFrame::EditorRootFrame(const wxString& title) :
	wxFrame(nullptr, wxID_ANY, title),
	MainPanel(new wxPanel(this)),
	AutoScrollCheckbox(new wxCheckBox(MainPanel, wxID_JUMP_TO, "Auto Scroll")),
	StatusBar(CreateStatusBar()),
	LogNotebook(new DebugNotebook(MainPanel))
{
	AutoScrollCheckbox->SetValue(true);
	LogNotebook->AutoScrollAllLogs(true);

	auto* vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(AutoScrollCheckbox);
	vbox->Add(LogNotebook, 1, wxEXPAND);

	MainPanel->SetSizer(vbox);

	AppendMainMenuBar();
	BindEvents();
	BindLogToStatusBar();
	SetMinSize(GetEffectiveMinSize());
	
	Editor.Initialize();
}

nes::EditorRootFrame::~EditorRootFrame()
{
	Editor.Destroy();
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

void nes::EditorRootFrame::BindLogToStatusBar() const
{
	EditorLogger::GetInstance().AddInformationListener([&](std::string_view msg) {
		StatusBar->SetStatusText(msg.data());
	});

	EditorLogger::GetInstance().AddWarningListener([&](std::string_view msg) {
		StatusBar->SetStatusText(msg.data());
	});

	EditorLogger::GetInstance().AddErrorListener([&](std::string_view msg) {
		StatusBar->SetStatusText(msg.data());
	});
}

void nes::EditorRootFrame::OnLoadRom(wxCommandEvent& event)
{
	auto* const fileDialog = new wxFileDialog(MainPanel, "Load a NES ROM file");
	if (fileDialog->ShowModal() == wxID_OK)
	{
		std::string path = fileDialog->GetPath();

		if (Editor.TryLoadRomFile(path))
		{
			EditorLogger::GetInstance().LogInformation("Loaded ROM file: " + path);
		}
		else
		{
			EditorLogger::GetInstance().LogError("Failed to load ROM file: " + path);

			// Display error alert
			auto* const alert = new wxMessageDialog(fileDialog, "Unable to load ROM, check the error log", "Error", wxOK | wxICON_ERROR);
			alert->ShowModal();
		}
	}
	else
	{
		EditorLogger::GetInstance().LogError("Failed to open file dialog");
	}
}

void nes::EditorRootFrame::OnAutoScrollUpdate(wxCommandEvent& event)
{
	LogNotebook->AutoScrollAllLogs(AutoScrollCheckbox->GetValue());
}
