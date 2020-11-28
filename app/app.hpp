#ifndef NES_APP_HPP
#define NES_APP_HPP

#include "editor/editor_service.hpp"

#include <wx/app.h>

namespace nes
{
	class EditorMain;

	/**
	 * Main window that holds the application
	 */
	class NesEmulatorApplication final : public wxApp
	{
	public:
		/**
		 * Initialize the application
		 * @return	True when initialized successfully, false otherwise
		 */
		bool OnInit() override;

		/**
		 * Called right before the application closes
		 * @return	Exit code
		 */
		int OnExit() override;

	private:
		EditorMain* Editor;
		EditorService EditorLogic;
	};
}

#endif //! NES_APP_HPP
