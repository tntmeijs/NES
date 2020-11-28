#ifndef NES_EDITOR_MAIN_HPP
#define NES_EDITOR_MAIN_HPP

#include "generated_ui/editor_ui.h"

namespace nes
{
	class EditorService;

	class EditorMain final : public EmulatorEditorUI
	{
	public:
		/**
		 * Create a new editor instance
		 * @param	editorService	Object that contains the editor business logic
		 */
		EditorMain(const EditorService& editorService);

		/**
		 * Start listening to the editor logs and dump the results to the output
		 */
		void ListenForLogs();

	private:
		/**
		 * Called when load from disk in the main menu is clicked
		 * @param	event	WxWidgets event data
		 */
		void OnLoadRomFromDisk(wxCommandEvent& event) override;

		/**
		 * Called when the about button in the main menu is clicked
		 * @param	event	WxWidgets event data
		 */
		void OnDisplayAboutDialog(wxCommandEvent& event) override;

	private:
		const EditorService& EditorLogic;
	};
}

#endif //! NES_EDITOR_MAIN_HPP
