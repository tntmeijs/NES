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

	MainToolbar = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	ExecuteCpuInstruction = MainToolbar->AddTool( wxID_ANY, wxT("Execute CPU instruction"), wxBitmap( wxT("resources/next.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Execute the next CPU instruction"), wxT("Execute the next CPU instruction"), NULL );

	MainToolbar->Realize();

	wxBoxSizer* Container;
	Container = new wxBoxSizer( wxVERTICAL );

	EnableAutoScrollCheckbox = new wxCheckBox( this, wxID_ANY, wxT("Enable Auto Scroll"), wxDefaultPosition, wxDefaultSize, 0 );
	EnableAutoScrollCheckbox->SetValue(true);
	Container->Add( EnableAutoScrollCheckbox, 0, wxALL, 5 );

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

	Container->Add( DebugOutput, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( Container );
	this->Layout();
	StatusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	FileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EmulatorEditorUI::OnLoadRomFromDisk ), this, LoadRomFromDisk->GetId());
	HelpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( EmulatorEditorUI::OnDisplayAboutDialog ), this, AboutInfo->GetId());
	this->Connect( ExecuteCpuInstruction->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnExecuteNextInstruction ) );
}

EmulatorEditorUI::~EmulatorEditorUI()
{
	// Disconnect Events
	this->Disconnect( ExecuteCpuInstruction->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( EmulatorEditorUI::OnExecuteNextInstruction ) );

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
