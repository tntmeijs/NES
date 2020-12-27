#include "editor_main.hpp"
#include "editor_service.hpp"
#include "editor_logger.hpp"
#include "utility/timestamp.hpp"

#include <wx/filedlg.h>
#include <wx/listbox.h>
#include <wx/msgdlg.h>

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

nes::EditorMain::EditorMain(EditorService& editorService) :
	EmulatorEditorUI(nullptr),
	EditorLogic(editorService)
{
	StackVisualization->EnableVisibleFocus(false);
	
	// Update the CPU stack visualizer whenever the stack is changed
	EditorLogic.OnUpdateStackVisualization = [&](auto stack) { UpdateStackVisualization(stack); };
}

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

	std::string path = fileDialog.GetPath();
	LoadRomFromDisk(path);

	//#DEBUG: Remove once CPU works
	if (fileDialog.GetFilename() == "nestest.nes")
	{
		EditorLogger::GetInstance().LogWarning("DEBUG: Setting program counter to 0xC000 to make nestest work!");
		EditorLogic.SetCpuProgramCounter(0xC000);
	}
}

void nes::EditorMain::OnRomSelectedFromTree(wxCommandEvent& event)
{
	std::string path = FileBrowser->GetFilePath();
	LoadRomFromDisk(path);

	//#DEBUG: Remove once CPU works
	if (path.substr(path.find_last_of('/\\') + 1, path.size()) == "nestest.nes")
	{
		EditorLogger::GetInstance().LogWarning("DEBUG: Setting program counter to 0xC000 to make nestest work!");
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

	while (currentCycle <= targetCycle)
	{
		EditorLogic.ExecuteNextCpuInstruction();
		currentCycle = EditorLogic.GetCpuCurrentCycle();
		wxYieldIfNeeded();
	}
}

void nes::EditorMain::OnClearAllLogs(wxCommandEvent& event)
{
	AllLogList->Clear();
	CpuLogList->Clear();
	InfoLogList->Clear();
	WarningLogList->Clear();
	ErrorLogList->Clear();
}

void nes::EditorMain::OnDumpLogsToDisk(wxCommandEvent& event)
{
	auto timestamp_str = std::to_string(GenerateUnixTimestamp());

	WriteListBoxContentToFile(AllLogList, "./logs/" + timestamp_str + "_all.log");
	WriteListBoxContentToFile(CpuLogList, "./logs/" + timestamp_str + "_cpu.log");
	WriteListBoxContentToFile(InfoLogList, "./logs/" + timestamp_str + "_info.log");
	WriteListBoxContentToFile(WarningLogList, "./logs/" + timestamp_str + "_warning.log");
	WriteListBoxContentToFile(ErrorLogList, "./logs/" + timestamp_str + "_error.log");
}

void nes::EditorMain::LoadRomFromDisk(std::string_view path)
{
	if (EditorLogic.TryLoadRomFile(path))
	{
		EditorLogger::GetInstance().LogInformation("Loaded ROM file: " + std::string(path));
	}
	else
	{
		EditorLogger::GetInstance().LogError("Failed to load ROM file: " + std::string(path));

		// Display error alert
		wxMessageDialog alert(this, "Unable to load ROM, check the error log", "Error", wxOK | wxICON_ERROR);
		alert.ShowModal();
	}
}

void nes::EditorMain::WriteListBoxContentToFile(
	const wxListBox* const widget,
	std::string_view filePath) const
{
	auto& logger = EditorLogger::GetInstance();
	
	if (widget->IsEmpty())
	{
		return;
	}

	auto path = std::filesystem::path(filePath).remove_filename();
	if (!std::filesystem::exists(path))
	{
		std::filesystem::create_directories(path);
	}

	auto file = std::ofstream(filePath);
	if (!file.is_open())
	{
		logger.LogError("Unable to open " + std::string(filePath));
		logger.LogError("Failed to write content to disk.");
		logger.LogError("Check if you have write permissions in the working directory.");
		return;
	}

	// Save all items in the list box
	for (auto i = 0; i < widget->GetCount(); ++i)
	{
		file << widget->GetString(i) << std::endl;
	}

	file.close();
}

void nes::EditorMain::UpdateStackVisualization(std::vector<Byte> stack)
{
	// Utility function for converting value to its hexadecimal representation
	auto ByteToHexStr = [](const Byte& byte) -> auto
	{
		// Need to cast to a wider type to prevent the value from implicitly
		// being casted to a character
		auto value = static_cast<std::uint16_t>(byte.value);

		std::stringstream stream;
		stream << "0x";					// Pretty print hexadecimal values
		stream << std::hex;				// Write as hexadecimal
		stream << std::setw(2);			// Need all entries to be 0x__
		stream << std::setfill('0');	// Fill any unused values with zeros
		stream << value;				// Save the value

		return stream.str();
	};

	StackVisualization->Clear();

	for (auto& byte : stack)
	{
		StackVisualization->AppendString(ByteToHexStr(byte));
	}
}
