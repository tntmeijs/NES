#include "app_frame.hpp"

nes::NesEmulatorApplicationFrame::NesEmulatorApplicationFrame(const wxString& title) :
	wxFrame(nullptr, wxID_ANY, title)
{
	Centre();
}
