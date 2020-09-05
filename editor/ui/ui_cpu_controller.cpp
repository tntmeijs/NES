#include "ui_cpu_controller.hpp"
#include "cpu/cpu.hpp"

#include <imgui.h>

nes::UICpuController::UICpuController(CPU& cpuRef) :
	CpuRef(cpuRef)
{}

void nes::UICpuController::DrawImpl() const
{
	ImGui::Text("Current Address:\t0x%04X", CpuRef.GetProgramCounter());
	ImGui::PushButtonRepeat(true);
	if (ImGui::Button("Next Instruction"))
	{
		CpuRef.NextInstruction();
	}
	ImGui::PopButtonRepeat();
}
