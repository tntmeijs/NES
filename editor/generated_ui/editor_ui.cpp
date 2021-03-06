///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "editor_ui.h"

///////////////////////////////////////////////////////////////////////////
using namespace nes;

EmulatorEditorUI::EmulatorEditorUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 640,360 ), wxDefaultSize );

	MainMenuBar = new wxMenuBar( 0 );
	FileMenu = new wxMenu();
	wxMenuItem* LoadRomFromDisk;
	LoadRomFromDisk = new wxMenuItem( FileMenu, wxID_OPEN, wxString( wxT("Load...") ) , wxT("Open a ROM file from disk"), wxITEM_NORMAL );
	FileMenu->Append( LoadRomFromDisk );

	MainMenuBar->Append( FileMenu, wxT("File") );

	HelpMenu = new wxMenu();
	wxMenuItem* AboutInfo;
	AboutInfo = new wxMenuItem( HelpMenu, wxID_ANY, wxString( wxT("About...") ) , wxEmptyString, wxITEM_NORMAL );
	HelpMenu->Append( AboutInfo );

	MainMenuBar->Append( HelpMenu, wxT("Help") );

	this->SetMenuBar( MainMenuBar );

	wxBoxSizer* Container;
	Container = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* CpuControls;
	CpuControls = new wxBoxSizer( wxHORIZONTAL );

	ExecuteNext = new wxButton( this, wxID_ANY, wxT("Execute next instruction"), wxDefaultPosition, wxDefaultSize, 0 );
	ExecuteNext->SetToolTip( wxT("Execute the next instruction at address pointed to by the program counter") );

	CpuControls->Add( ExecuteNext, 0, wxALL, 5 );

	Divider = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	CpuControls->Add( Divider, 0, wxEXPAND | wxALL, 5 );

	ExecuteUntilCycleValue = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL|wxSP_ARROW_KEYS, 0, 65536, 0 );
	CpuControls->Add( ExecuteUntilCycleValue, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND|wxSHAPED, 5 );

	ExecuteUntilCycle = new wxButton( this, wxID_ANY, wxT("Execute until cycle"), wxDefaultPosition, wxDefaultSize, 0 );
	ExecuteUntilCycle->SetToolTip( wxT("Keep executing instructions until the specified cycle has been reached (blocks the UI thread)") );

	CpuControls->Add( ExecuteUntilCycle, 0, wxALL, 5 );


	Container->Add( CpuControls, 0, wxEXPAND, 5 );

	GameWindow = new EditorGameWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	Container->Add( GameWindow, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* FileExplorerLogStack;
	FileExplorerLogStack = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* FileBrowserContainer;
	FileBrowserContainer = new wxBoxSizer( wxVERTICAL );

	FileBrowserTitle = new wxStaticText( this, wxID_ANY, wxT("FILE BROWSER"), wxDefaultPosition, wxDefaultSize, 0 );
	FileBrowserTitle->Wrap( -1 );
	FileBrowserContainer->Add( FileBrowserTitle, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	FileBrowser = new wxGenericDirCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDIRCTRL_3D_INTERNAL|wxDIRCTRL_EDIT_LABELS|wxSUNKEN_BORDER, wxT("*.nes"), 0 );

	FileBrowser->ShowHidden( false );
	FileBrowserContainer->Add( FileBrowser, 1, wxALL|wxEXPAND, 5 );


	FileExplorerLogStack->Add( FileBrowserContainer, 2, wxEXPAND, 5 );

	wxBoxSizer* Logger;
	Logger = new wxBoxSizer( wxVERTICAL );

	LogOutputTitle = new wxStaticText( this, wxID_ANY, wxT("LOG OUTPUT"), wxDefaultPosition, wxDefaultSize, 0 );
	LogOutputTitle->Wrap( -1 );
	Logger->Add( LogOutputTitle, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	DebugOutput = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM );
	AllPanel = new wxPanel( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* AllLogSizer;
	AllLogSizer = new wxBoxSizer( wxVERTICAL );

	AllLogList = new wxListBox( AllPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	AllLogSizer->Add( AllLogList, 1, wxEXPAND, 5 );


	AllPanel->SetSizer( AllLogSizer );
	AllPanel->Layout();
	AllLogSizer->Fit( AllPanel );
	DebugOutput->AddPage( AllPanel, wxT("All"), true );
	CpuPanel = new wxPanel( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* CpuLogSizer;
	CpuLogSizer = new wxBoxSizer( wxVERTICAL );

	CpuLogList = new wxListBox( CpuPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	CpuLogSizer->Add( CpuLogList, 1, wxEXPAND, 5 );


	CpuPanel->SetSizer( CpuLogSizer );
	CpuPanel->Layout();
	CpuLogSizer->Fit( CpuPanel );
	DebugOutput->AddPage( CpuPanel, wxT("CPU"), false );
	InfoPanel = new wxPanel( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* InfoLogSizer;
	InfoLogSizer = new wxBoxSizer( wxVERTICAL );

	InfoLogList = new wxListBox( InfoPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	InfoLogSizer->Add( InfoLogList, 1, wxEXPAND, 5 );


	InfoPanel->SetSizer( InfoLogSizer );
	InfoPanel->Layout();
	InfoLogSizer->Fit( InfoPanel );
	DebugOutput->AddPage( InfoPanel, wxT("Info"), false );
	WarningPanel = new wxPanel( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* WarningLogSizer;
	WarningLogSizer = new wxBoxSizer( wxVERTICAL );

	WarningLogList = new wxListBox( WarningPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	WarningLogSizer->Add( WarningLogList, 1, wxEXPAND, 5 );


	WarningPanel->SetSizer( WarningLogSizer );
	WarningPanel->Layout();
	WarningLogSizer->Fit( WarningPanel );
	DebugOutput->AddPage( WarningPanel, wxT("Warning"), false );
	ErrorPanel = new wxPanel( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* ErrorLogSizer;
	ErrorLogSizer = new wxBoxSizer( wxVERTICAL );

	ErrorLogList = new wxListBox( ErrorPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	ErrorLogSizer->Add( ErrorLogList, 1, wxEXPAND, 5 );


	ErrorPanel->SetSizer( ErrorLogSizer );
	ErrorPanel->Layout();
	ErrorLogSizer->Fit( ErrorPanel );
	DebugOutput->AddPage( ErrorPanel, wxT("Error"), false );

	Logger->Add( DebugOutput, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* Row;
	Row = new wxBoxSizer( wxHORIZONTAL );

	EnableAutoScrollCheckbox = new wxCheckBox( this, wxID_ANY, wxT("Automatically scroll logs"), wxDefaultPosition, wxDefaultSize, 0 );
	EnableAutoScrollCheckbox->SetValue(true);
	EnableAutoScrollCheckbox->SetToolTip( wxT("Make the logs scroll to the most recent entry automatically (disable this if you would like to scroll through the logs yourself)") );

	Row->Add( EnableAutoScrollCheckbox, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	DumpLogs = new wxButton( this, wxID_ANY, wxT("Dump logs to disk"), wxDefaultPosition, wxDefaultSize, 0 );
	DumpLogs->SetToolTip( wxT("Save the logged information to disk") );

	Row->Add( DumpLogs, 0, wxALL, 5 );


	Row->Add( 0, 0, 1, wxEXPAND, 5 );

	ClearLogsButton = new wxButton( this, wxID_ANY, wxT("Clear all logs"), wxDefaultPosition, wxDefaultSize, 0 );
	ClearLogsButton->SetToolTip( wxT("Clear all log channels") );

	Row->Add( ClearLogsButton, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	Logger->Add( Row, 0, wxEXPAND, 5 );


	FileExplorerLogStack->Add( Logger, 7, wxEXPAND, 5 );

	wxBoxSizer* Stack;
	Stack = new wxBoxSizer( wxVERTICAL );

	StackVisualizerTitle = new wxStaticText( this, wxID_ANY, wxT("CPU STACK"), wxDefaultPosition, wxDefaultSize, 0 );
	StackVisualizerTitle->Wrap( -1 );
	Stack->Add( StackVisualizerTitle, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	StackVisualization = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	Stack->Add( StackVisualization, 1, wxALL|wxEXPAND, 5 );


	FileExplorerLogStack->Add( Stack, 1, wxEXPAND, 5 );


	Container->Add( FileExplorerLogStack, 1, wxEXPAND, 5 );


	this->SetSizer( Container );
	this->Layout();
	StatusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	FileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EmulatorEditorUI::OnLoadRomFromDisk ), this, LoadRomFromDisk->GetId());
	HelpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EmulatorEditorUI::OnDisplayAboutDialog ), this, AboutInfo->GetId());
	ExecuteNext->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnExecuteNextInstruction ), NULL, this );
	ExecuteUntilCycle->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnExecuteUntilCycle ), NULL, this );
	FileBrowser->Connect( wxEVT_DIRCTRL_FILEACTIVATED, wxCommandEventHandler( EmulatorEditorUI::OnRomSelectedFromTree ), NULL, this );
	DumpLogs->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnDumpLogsToDisk ), NULL, this );
	ClearLogsButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnClearAllLogs ), NULL, this );
}

EmulatorEditorUI::~EmulatorEditorUI()
{
	// Disconnect Events
	ExecuteNext->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnExecuteNextInstruction ), NULL, this );
	ExecuteUntilCycle->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnExecuteUntilCycle ), NULL, this );
	FileBrowser->Disconnect( wxEVT_DIRCTRL_FILEACTIVATED, wxCommandEventHandler( EmulatorEditorUI::OnRomSelectedFromTree ), NULL, this );
	DumpLogs->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnDumpLogsToDisk ), NULL, this );
	ClearLogsButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnClearAllLogs ), NULL, this );

}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* Container;
	Container = new wxBoxSizer( wxVERTICAL );

	Title = new wxStaticText( this, wxID_ANY, wxT("NES Emulator"), wxDefaultPosition, wxDefaultSize, 0 );
	Title->Wrap( -1 );
	Title->SetFont( wxFont( 20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	Container->Add( Title, 0, wxALL, 5 );

	Subtitle = new wxStaticText( this, wxID_ANY, wxT("An open-source C++ emulator"), wxDefaultPosition, wxDefaultSize, 0 );
	Subtitle->Wrap( -1 );
	Container->Add( Subtitle, 0, wxALL, 5 );

	HorizontalDivider = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	Container->Add( HorizontalDivider, 0, wxEXPAND | wxALL, 5 );

	wxGridSizer* CreditsContainer;
	CreditsContainer = new wxGridSizer( 0, 2, 0, 0 );

	AuthorLabel = new wxStaticText( this, wxID_ANY, wxT("Author"), wxDefaultPosition, wxDefaultSize, 0 );
	AuthorLabel->Wrap( -1 );
	CreditsContainer->Add( AuthorLabel, 0, wxALL, 5 );

	AuthorValue = new wxStaticText( this, wxID_ANY, wxT("Tahar Meijs"), wxDefaultPosition, wxDefaultSize, 0 );
	AuthorValue->Wrap( -1 );
	CreditsContainer->Add( AuthorValue, 0, wxALL, 5 );

	SourceCodeLabel = new wxStaticText( this, wxID_ANY, wxT("Source code"), wxDefaultPosition, wxDefaultSize, 0 );
	SourceCodeLabel->Wrap( -1 );
	CreditsContainer->Add( SourceCodeLabel, 0, wxALL, 5 );

	SourceCodeHyperlink = new wxHyperlinkCtrl( this, wxID_ANY, wxT("View on GitHub"), wxT("https://github.com/tntmeijs/NES"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	CreditsContainer->Add( SourceCodeHyperlink, 0, wxALL, 5 );

	IconsLabel = new wxStaticText( this, wxID_ANY, wxT("Icons by Kenney"), wxDefaultPosition, wxDefaultSize, 0 );
	IconsLabel->Wrap( -1 );
	CreditsContainer->Add( IconsLabel, 0, wxALL, 5 );

	IconsHyperlink = new wxHyperlinkCtrl( this, wxID_ANY, wxT("View on kenney.nl"), wxT("https://kenney.nl/assets/game-icons"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	CreditsContainer->Add( IconsHyperlink, 0, wxALL, 5 );


	Container->Add( CreditsContainer, 1, wxEXPAND, 5 );


	this->SetSizer( Container );
	this->Layout();
	Container->Fit( this );

	this->Centre( wxBOTH );
}

AboutDialog::~AboutDialog()
{
}
