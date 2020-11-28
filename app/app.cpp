#include "app.hpp"
#include "editor/editor_main.hpp"

bool nes::NesEmulatorApplication::OnInit()
{
	auto* const editor = new EditorMain();
	editor->Show();
	return true;
}
