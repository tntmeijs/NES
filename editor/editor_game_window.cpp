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
	static float r = 0, g = 0, b = 0;
	r += 0.05f;
	g += 0.10;
	b += 0.15;

	if (r >= 256)
	{
		r = 0;
	}

	if (g >= 256)
	{
		g = 0;
	}

	if (b >= 256)
	{
		b = 0;
	}

	//#DEBUG: change clear color into something sensible like white or black
	clear(sf::Color(r, g, b));
}
