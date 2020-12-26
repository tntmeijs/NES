#ifndef NES_EDITOR_GAME_WINDOW_HPP
#define NES_EDITOR_GAME_WINDOW_HPP

#include "wx_sfml_canvas.hpp"

namespace nes
{
	/**
	 * SFML window that will display the game
	 */
	class EditorGameWindow : public wxSfmlCanvas
	{
	public:
		/**
		 * Create a new editor game window
		 */
		EditorGameWindow(
			wxWindow* parent,
			wxWindowID id,
			const wxPoint& position,
			const wxSize& size,
			long style = 0);

	private:
		/**
		 * Called every frame
		 */
		void OnUpdate() final override;
	};
}

#endif //! NES_EDITOR_GAME_WINDOW_HPP
