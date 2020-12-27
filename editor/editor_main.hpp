#ifndef NES_EDITOR_MAIN_HPP
#define NES_EDITOR_MAIN_HPP

#include "generated_ui/editor_ui.h"
#include "utility/bit_tools.hpp"

#include <string_view>

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
		 * Called when a ROM is selected using the integrated tree file explorer
		 * @param	event	WxWidgets event data
		 */
		void OnRomSelectedFromTree(wxCommandEvent& event) override;

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

		/**
		 * Clear all logs on the output pane
		 * @param	event	WxWidgets event data
		 */
		void OnClearAllLogs(wxCommandEvent& event) override;

		/**
		 * Save all logs to disk
		 * Each logging channel will be saved to its own file
		 * The files will be placed in a "logs" folder in the working directory
		 */
		void OnDumpLogsToDisk(wxCommandEvent& event) override;

	private:
		/**
		 * Load a ROM file into memory from a location on disk
		 * @param	path	Path to the ROM file
		 */
		void LoadRomFromDisk(std::string_view path);

		/**
		 * Write all lines from a list box to a file
		 * @param	widget					List box widget to read from
		 * @param	filePath				Path to the output file
		 */
		void WriteListBoxContentToFile(
			const wxListBox* const widget,
			std::string_view filePath) const;

		/**
		 * Recreate the stack visualization
		 * @param	stack	Copy of the current stack state
		 */
		void UpdateStackVisualization(std::array<Byte, 256> stack);

	private:
		EditorService& EditorLogic;
	};
}

#endif //! NES_EDITOR_MAIN_HPP
