#ifndef NES_APP_FRAME_HPP
#define NES_APP_FRAME_HPP

#include <wx/frame.h>
#include <wx/string.h>

#include <cstdint>
#include <string_view>

namespace nes
{
	/**
	 * Main frame of the GUI application
	 */
	class NesEmulatorApplicationFrame final : public wxFrame
	{
	public:
		/**
		 * Create a new application frame
		 * @param	title	Title of the application
		 */
		NesEmulatorApplicationFrame(const wxString& title);
	};
}

#endif //! NES_APP_FRAME_HPP
