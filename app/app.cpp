#include "app.hpp"
#include "editor/editor_main.hpp"

#include <wx/image.h>
#include <wx/imagpng.h>

bool nes::NesEmulatorApplication::OnInit()
{
	// Add support for .png files
	wxImage::AddHandler(new wxPNGHandler);

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
