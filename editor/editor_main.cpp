#include "editor_main.hpp"
#include "editor_service.hpp"

nes::EditorMain::EditorMain(const EditorService& editorService) :
	EmulatorEditorUI(nullptr),
	EditorLogic(editorService)
{}

void nes::EditorMain::OnLoadRomFromDisk(wxCommandEvent& event)
{}

void nes::EditorMain::OnDisplayAboutDialog(wxCommandEvent& event)
{}
