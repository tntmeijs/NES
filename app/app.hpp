#ifndef NES_APP_HPP
#define NES_APP_HPP

#include <wx/app.h>

namespace nes
{
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
		bool OnInit() final override;
	};
}

#endif //! NES_APP_HPP
