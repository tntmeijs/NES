#ifndef NES_EDITOR_MAIN_HPP
#define NES_EDITOR_MAIN_HPP

#include "generated_ui/editor_ui.h"

namespace nes
{
	class EditorMain final : public EmulatorEditorUI
	{
	public:
		EditorMain();

	private:
		void OnLoadRomFromDisk(wxCommandEvent& event) override;

		void OnDisplayAboutDialog(wxCommandEvent& event) override;
	};
}

#endif //! NES_EDITOR_MAIN_HPP
