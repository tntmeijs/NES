#include "app.hpp"
#include "editor/editor_main.hpp"

bool nes::NesEmulatorApplication::OnInit()
{
	auto success = EditorLogic.Initialize();

	Editor = new EditorMain(EditorLogic);
	Editor->Show();
	Editor->ListenForLogs();

	return success;
}

int nes::NesEmulatorApplication::OnExit()
{
	EditorLogic.Destroy();
	return 0;
}
