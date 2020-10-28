#include "app.hpp"
#include "editor/root_frame.hpp"

bool nes::NesEmulatorApplication::OnInit()
{
	auto* const mainFrame = new EditorRootFrame("NES Emulator | Tahar Meijs");
	mainFrame->Show(true);

	return true;
}
