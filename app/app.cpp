#include "app.hpp"
#include "app_frame.hpp"

bool nes::NesEmulatorApplication::OnInit()
{
	auto* const mainFrame = new NesEmulatorApplicationFrame("NES Emulator | Tahar Meijs");
	mainFrame->Show(true);

	return true;
}
