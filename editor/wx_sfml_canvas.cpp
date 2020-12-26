#include "wx_sfml_canvas.hpp"

nes::wxSfmlCanvas::wxSfmlCanvas(
	wxWindow* parent,
	wxWindowID id,
	const wxPoint& position,
	const wxSize& size, long style) :
	wxControl(parent, id, position, size, style)
{
	create(GetHandle());
}

nes::wxSfmlCanvas::~wxSfmlCanvas()
{}

void nes::wxSfmlCanvas::OnUpdate()
{}

void nes::wxSfmlCanvas::OnIdle(wxIdleEvent&)
{
	Refresh();
}

void nes::wxSfmlCanvas::OnPaint(wxPaintEvent&)
{
	// Prepare to be repainted
	wxPaintDC dc(this);

	// Give the derived class a chance to update
	OnUpdate();

	// Display on screen
	display();
}
