#include "ui_cpu_controller.hpp"
#include "cpu/cpu.hpp"

#include <imgui.h>

nes::UICpuController::UICpuController(CPU& cpuRef) :
	CpuRef(cpuRef)
{}

void nes::UICpuController::Draw() const
{
	ImGui::Text("Program Counter:");
	ImGui::SameLine();

	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##decrease_pc", ImGuiDir_Left))
	{
		CpuRef.MoveProgramCounter(-1);
	}

	ImGui::SameLine();
	if (ImGui::ArrowButton("##increase_pc", ImGuiDir_Right))
	{
		CpuRef.MoveProgramCounter(1);
	}

	ImGui::PopButtonRepeat();
	ImGui::SameLine();

	// Manually set the program counter to a specific address
	int address = CpuRef.GetProgramCounter();
	if (ImGui::InputInt("##set_pc_manually", &address, 0))
	{
		CpuRef.SetProgramCounterToAddress(address);
	}

	// Display the memory location in hexadecimal notation
	ImGui::SameLine();
	ImGui::Text("0x%04X", CpuRef.GetProgramCounter());

	// Execute the next instruction
	ImGui::PushButtonRepeat(true);
	if (ImGui::Button("Execute Instruction"))
	{
		CpuRef.ExecuteAndIncrementPC();
	}
	ImGui::PopButtonRepeat();

	ImGui::SameLine();

	// Execute the current instruction
	if (ImGui::Button("Repeat Instruction"))
	{
		CpuRef.ExecuteCurrentInstruction(); 
	}
}
