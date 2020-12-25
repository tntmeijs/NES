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
		EditorMain(EditorService& editorService);

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

		/**
		 * Execute the next CPU instruction
		 * @param	event	WxWidgets event data
		 */
		void OnExecuteNextInstruction(wxCommandEvent& event) override;

		/**
		 * Keep executing instructions until the cycle counter equals or exceeds
		 * the specified value
		 * @param	event	WxWidgets event data
		 */
		void OnExecuteUntilCycle(wxCommandEvent& event) override;

	private:
		EditorService& EditorLogic;
	};
}

#endif //! NES_EDITOR_MAIN_HPP
