#include "ui_panel.hpp"

#include <imgui.h>

#include <cstdint>
#include <cmath>

void nes::UIPanel::Create(
	std::uint32_t viewportWidth,
	std::uint32_t viewportHeight,
	std::uint32_t x,
	std::uint32_t y,
	float width,
	float height)
{
	X = x;
	Y = y;
	ViewportWidth = viewportWidth;
	ViewportHeight = viewportHeight;
	Width = width;
	Height = height;
	PanelName = "UI_PANEL_" + std::to_string(ElementID);
}

void nes::UIPanel::Draw() const
{
	ImGui::Begin(PanelName.c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	float panelWidth	= std::ceil(Width * static_cast<float>(ViewportWidth));
	float panelHeight	= std::ceil(Height * static_cast<float>(ViewportHeight));

	ImGui::SetWindowPos(PanelName.c_str(), { static_cast<float>(X), static_cast<float>(Y) });
	ImGui::SetWindowSize(PanelName.c_str(), { panelWidth, panelHeight });

	DrawImpl();

	ImGui::End();
}

void nes::UIPanel::DrawImpl() const
{}
