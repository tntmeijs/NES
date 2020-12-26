#ifndef NES_EDITOR_WX_SFML_CANVAS_HPP
#define NES_EDITOR_WX_SFML_CANVAS_HPP

#include <SFML/Graphics.hpp>
#include <wx/wx.h>

namespace nes
{
	/**
	 * Make SFML compatible with WxWidgets
	 * Reference: https://www.sfml-dev.org/tutorials/1.6/graphics-wxwidgets.php
	 */
    class wxSfmlCanvas : public wxControl, public sf::RenderWindow
    {
	public:
		/**
		 * Create a new SFML canvas control widget
		 * @param	parent		Parent window
		 * @param	id			Window ID
		 * @param	position	Position of this widget, defaults to wxDefaultPosition
		 * @param	size		Size of this widget, defaults to wxDefaultSize
		 * @param	style		Style flags, defaults to no flags
		 */
		wxSfmlCanvas(
			wxWindow* parent = nullptr,
			wxWindowID id = -1,
			const wxPoint& position = wxDefaultPosition,
			const wxSize& size = wxDefaultSize,
			long style = 0);

		/**
		 * Empty destructor
		 */
		virtual ~wxSfmlCanvas();

	private:

		DECLARE_EVENT_TABLE()

		/**
		 * Empty update function that can be implemented by a derived class
		 */
		virtual void OnUpdate();

		/**
		 * Triggers a repaint whenever the widget is idle
		 * This ensures maximum framerate for the SFML canvas
		 * @param	event	WxWidgets event data
		 */
		void OnIdle(wxIdleEvent& event);

		/**
		 * Draw to the window
		 * @param	event	WxWidgets event data
		 */
		void OnPaint(wxPaintEvent& event);
    };
}

#endif //! NES_EDITOR_WX_SFML_CANVAS_HPP
