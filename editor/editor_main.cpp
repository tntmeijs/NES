#include "editor_main.hpp"
#include "editor_service.hpp"
#include "editor_logger.hpp"

#include <wx/filedlg.h>
#include <wx/listbox.h>
#include <wx/msgdlg.h>

#include <string>
#include <string_view>

nes::EditorMain::EditorMain(EditorService& editorService) :
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

	logger.AddCpuListener([&](std::string_view msg) {
		auto index = CpuLogList->Append(msg.data());
		auto scroll = EnableAutoScrollCheckbox->GetValue();

		if (scroll)
		{
			CpuLogList->EnsureVisible(index);
		}
	});

	logger.AddAnyListener([&](std::string_view msg) {
		auto index = AllLogList->Append(msg.data());
		auto scroll = EnableAutoScrollCheckbox->GetValue();

		if (scroll)
		{
			AllLogList->EnsureVisible(index);
		}
	});
}

void nes::EditorMain::OnLoadRomFromDisk(wxCommandEvent& event)
{
	wxFileDialog fileDialog(this, "Load a NES rom", "./", "", "NES rom files (*.nes)|*.nes", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	
	if (fileDialog.ShowModal() == wxID_CANCEL)
	{
		// User canceled the dialog
		return;
	}

	auto& logger = EditorLogger::GetInstance();

	std::string path = fileDialog.GetPath();
	if (EditorLogic.TryLoadRomFile(path))
	{
		EditorLogger::GetInstance().LogInformation("Loaded ROM file: " + path);
	}
	else
	{
		EditorLogger::GetInstance().LogError("Failed to load ROM file: " + path);

		// Display error alert
		wxMessageDialog alert(this, "Unable to load ROM, check the error log", "Error", wxOK | wxICON_ERROR);
		alert.ShowModal();
	}

	//#DEBUG: Remove once CPU works
	if (fileDialog.GetFilename() == "nestest.nes")
	{
		logger.LogWarning("DEBUG: Setting program counter to 0xC000 to make nestest work!");
		EditorLogic.SetCpuProgramCounter(0xC000);
	}
}

void nes::EditorMain::OnDisplayAboutDialog(wxCommandEvent& event)
{
	AboutDialog dialog(this);
	dialog.ShowModal();
}

void nes::EditorMain::OnExecuteNextInstruction(wxCommandEvent& event)
{
	if (!EditorLogic.HasLoadedRom())
	{
		EditorLogger::GetInstance().LogError("Cannot execute instruction without a ROM");
		return;
	}

	EditorLogic.ExecuteNextCpuInstruction();
}

void nes::EditorMain::OnExecuteUntilCycle(wxCommandEvent& event)
{
	if (!EditorLogic.HasLoadedRom())
	{
		EditorLogger::GetInstance().LogError("Cannot execute instruction without a ROM");
		return;
	}

	auto targetCycle = ExecuteUntilCycleValue->GetValue();
	auto currentCycle = EditorLogic.GetCpuCurrentCycle();

	while (currentCycle < targetCycle)
	{
		EditorLogic.ExecuteNextCpuInstruction();
		currentCycle = EditorLogic.GetCpuCurrentCycle();
	}
}
