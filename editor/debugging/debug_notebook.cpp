#include "debug_notebook.hpp"
#include "debug_notebook_page.hpp"

#include <iostream>

// Number of lines preserved in the log queue
constexpr unsigned int HISTORY_LENGTH = 10000;

nes::DebugNotebook::DebugNotebook(wxWindow* const parent) :
	wxNotebook(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_BOTTOM),
	InformationLog(new DebugNotebookPage(this)),
	WarningLog(new DebugNotebookPage(this)),
	ErrorLog(new DebugNotebookPage(this))
{
	AddPage(InformationLog, "Info");
	AddPage(WarningLog, "Warning");
	AddPage(ErrorLog, "Error");
	Layout();
}

void nes::DebugNotebook::LogInfo(std::string_view info)
{
	InformationLog->Log(info);
}

void nes::DebugNotebook::LogWarning(std::string_view warning)
{
	WarningLog->Log(warning);
}

void nes::DebugNotebook::LogError(std::string_view error)
{
	ErrorLog->Log(error);
}
