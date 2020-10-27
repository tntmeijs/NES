#include "app_frame.hpp"
#include "global_ids.hpp"

#include <wx/menu.h>

nes::NesEmulatorApplicationFrame::NesEmulatorApplicationFrame(const wxString& title) :
	wxFrame(nullptr, NES_ID_MAIN_FRAME, title)
{
	auto* const mainMenuBar = new wxMenuBar();

	mainMenuBar->Append(ConstructFileMenu(), "&File");
	mainMenuBar->Append(ConstructDebugMenu(), "&Debug");
	mainMenuBar->Append(ConstructHelpMenu(), "&Help");

	SetMenuBar(mainMenuBar);
}

wxMenu* const nes::NesEmulatorApplicationFrame::ConstructFileMenu() const
{
	auto* const fileMenu = new wxMenu();
	fileMenu->Append(NES_ID_FILE_ROM_OPEN, "&Open ROM");

	return fileMenu;
}

wxMenu* const nes::NesEmulatorApplicationFrame::ConstructDebugMenu() const
{
	auto* const debugToolSubmenu = new wxMenu();
	debugToolSubmenu->AppendCheckItem(NES_ID_DEBUG_TOOLS_CPU_LOG, "CPU Log");
	debugToolSubmenu->AppendCheckItem(NES_ID_DEBUG_TOOLS_CPU_REGISTER_SPY, "Register Spy");
	debugToolSubmenu->AppendCheckItem(NES_ID_DEBUG_TOOLS_CPU_CONTROLLER, "CPU Controller");

	auto* const debugMenu = new wxMenu();
	debugMenu->AppendSubMenu(debugToolSubmenu, "Tools");

	return debugMenu;
}

wxMenu* const nes::NesEmulatorApplicationFrame::ConstructHelpMenu() const
{
	auto* const helpMenu = new wxMenu();
	helpMenu->Append(NES_ID_HELP_VERSION, "Version");
	helpMenu->Append(NES_ID_HELP_VERSION, "About");

	return helpMenu;
}
