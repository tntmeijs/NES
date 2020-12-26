#include "wx_sfml_canvas.hpp"

BEGIN_EVENT_TABLE(nes::wxSfmlCanvas, wxControl)
EVT_IDLE(nes::wxSfmlCanvas::OnIdle)
END_EVENT_TABLE()

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

void nes::wxSfmlCanvas::OnIdle(wxIdleEvent& event)
{
	// Give the derived class a chance to update
	OnUpdate();

	// SFML render call
	display();

	// Draw the widget again
	event.RequestMore();
}

void nes::wxSfmlCanvas::OnPaint(wxPaintEvent& event)
{
	// Prepare to be repainted
	wxPaintDC dc(this);

	// Give the derived class a chance to update
	OnUpdate();

	// Display on screen
	display();
}
