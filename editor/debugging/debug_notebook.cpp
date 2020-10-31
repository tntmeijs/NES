#include "debug_notebook.hpp"
#include "debug_notebook_page.hpp"
#include "editor/editor_logger.hpp"

#include <string_view>

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
	
	ListenForLogs();
}

void nes::DebugNotebook::ListenForLogs() const
{
	EditorLogger::GetInstance().AddInformationListener([&](std::string_view message) {
		InformationLog->Log(message);
	});

	EditorLogger::GetInstance().AddWarningListener([&](std::string_view message) {
		WarningLog->Log(message);
	});

	EditorLogger::GetInstance().AddErrorListener([&](std::string_view message) {
		ErrorLog->Log(message);
	});
}
