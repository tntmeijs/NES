#include "editor_main.hpp"
#include "editor_service.hpp"
#include "editor_logger.hpp"

#include <wx/listbox.h>

#include <string_view>

nes::EditorMain::EditorMain(const EditorService& editorService) :
	EmulatorEditorUI(nullptr),
	EditorLogic(editorService)
{}

void nes::EditorMain::ListenForLogs()
{
	auto& logger = EditorLogger::GetInstance();

	logger.AddInformationListener([&](std::string_view msg) {
		auto index = InfoLogList->Append(msg.data());
		auto scroll = EnableAutoScrollCheckbox->GetValue();

		if (scroll)
		{
			InfoLogList->EnsureVisible(index);
		}
	});

	logger.AddWarningListener([&](std::string_view msg) {
		auto index = WarningLogList->Append(msg.data());
		auto scroll = EnableAutoScrollCheckbox->GetValue();

		if (scroll)
		{
			WarningLogList->EnsureVisible(index);
		}
	});

	logger.AddErrorListener([&](std::string_view msg) {
		auto index = ErrorLogList->Append(msg.data());
		auto scroll = EnableAutoScrollCheckbox->GetValue();

		if (scroll)
		{
			ErrorLogList->EnsureVisible(index);
		}
	});
}

void nes::EditorMain::OnLoadRomFromDisk(wxCommandEvent& event)
{}

void nes::EditorMain::OnDisplayAboutDialog(wxCommandEvent& event)
{
	auto* dialog = new AboutDialog(this);
	dialog->ShowModal();
}
