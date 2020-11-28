///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/hyperlink.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace nes
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class EmulatorEditorUI
	///////////////////////////////////////////////////////////////////////////////
	class EmulatorEditorUI : public wxFrame
	{
		private:

		protected:
			wxMenuBar* MainMenuBar;
			wxMenu* FileMenu;
			wxMenu* HelpMenu;
			wxToolBar* MainToolbar;
			wxToolBarToolBase* NextInstruction;
			wxNotebook* DebugOutput;
			wxScrolledWindow* InfoPage;
			wxScrolledWindow* WarningPage;
			wxScrolledWindow* ErrorPage;
			wxStatusBar* StatusBar;

			// Virtual event handlers, overide them in your derived class
			virtual void OnLoadRomFromDisk( wxCommandEvent& event ) = 0;
			virtual void OnDisplayAboutDialog( wxCommandEvent& event ) = 0;
			virtual void OnExecuteNextInstruction( wxCommandEvent& event ) = 0;


		public:

			EmulatorEditorUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("NES Emulator | Tahar Meijs"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1280,720 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

			~EmulatorEditorUI();

	};

	///////////////////////////////////////////////////////////////////////////////
	/// Class AboutDialog
	///////////////////////////////////////////////////////////////////////////////
	class AboutDialog : public wxDialog
	{
		private:

		protected:
			wxStaticText* Title;
			wxStaticText* Subtitle;
			wxStaticLine* HorizontalDivider;
			wxStaticText* AuthorLabel;
			wxStaticText* AuthorValue;
			wxStaticText* SourceCodeLabel;
			wxHyperlinkCtrl* SourceCodeHyperlink;
			wxStaticText* IconsLabel;
			wxHyperlinkCtrl* IconsHyperlink;

		public:

			AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About the Project"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
			~AboutDialog();

	};

} // namespace nes

