///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "editor_ui.h"

///////////////////////////////////////////////////////////////////////////
using namespace nes;

Root::Root( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

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
	NextInstruction = MainToolbar->AddTool( wxID_ANY, wxT("Execute Instruction"), wxBitmap( wxT("../resources/next.png"), wxBITMAP_TYPE_ANY ), wxNullBitmap, wxITEM_NORMAL, wxT("Execute the next instruction"), wxT("Execute the next instruction"), NULL );

	MainToolbar->Realize();

	wxBoxSizer* Container;
	Container = new wxBoxSizer( wxVERTICAL );

	DebugOutput = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM|wxNB_FIXEDWIDTH );
	InfoPage = new wxScrolledWindow( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	InfoPage->SetScrollRate( 5, 5 );
	wxBoxSizer* InfoContainer;
	InfoContainer = new wxBoxSizer( wxVERTICAL );


	InfoPage->SetSizer( InfoContainer );
	InfoPage->Layout();
	InfoContainer->Fit( InfoPage );
	DebugOutput->AddPage( InfoPage, wxT("Info"), true );
	WarningPage = new wxScrolledWindow( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	WarningPage->SetScrollRate( 5, 5 );
	wxBoxSizer* WarningContainer1;
	WarningContainer1 = new wxBoxSizer( wxVERTICAL );


	WarningPage->SetSizer( WarningContainer1 );
	WarningPage->Layout();
	WarningContainer1->Fit( WarningPage );
	DebugOutput->AddPage( WarningPage, wxT("Warning"), false );
	ErrorPage = new wxScrolledWindow( DebugOutput, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	ErrorPage->SetScrollRate( 5, 5 );
	wxBoxSizer* ErrorContainer;
	ErrorContainer = new wxBoxSizer( wxVERTICAL );


	ErrorPage->SetSizer( ErrorContainer );
	ErrorPage->Layout();
	ErrorContainer->Fit( ErrorPage );
	DebugOutput->AddPage( ErrorPage, wxT("Error"), false );

	Container->Add( DebugOutput, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( Container );
	this->Layout();
	StatusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	FileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Root::OnLoadRomFromDisk ), this, LoadRomFromDisk->GetId());
	HelpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Root::OnDisplayAboutDialog ), this, AboutInfo->GetId());
	this->Connect( NextInstruction->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Root::OnExecuteNextInstruction ) );
}

Root::~Root()
{
	// Disconnect Events
	this->Disconnect( NextInstruction->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( Root::OnExecuteNextInstruction ) );

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
