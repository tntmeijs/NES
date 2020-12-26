#include "editor_game_window.hpp"

nes::EditorGameWindow::EditorGameWindow(
	wxWindow* parent,
	wxWindowID id,
	const wxPoint& position,
	const wxSize& size,
	long style) :
	wxSfmlCanvas(parent, id, position, size, style)
{}

void nes::EditorGameWindow::OnUpdate()
{
	clear();
}
