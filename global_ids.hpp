#ifndef NES_GLOBAL_IDS_HPP
#define NES_GLOBAL_IDS_HPP

/**
 * This file contains all IDs used throughout this application
 * WxWidgets uses these IDs on the GUI elements
 */
namespace nes
{
	// Frames
	inline constexpr int NES_ID_MAIN_FRAME = 0;

	// Menu bar file menu
	inline constexpr int NES_ID_FILE_ROM_OPEN = 1000;

	// Menu bar debug menu
	inline constexpr int NES_ID_DEBUG_TOOLS_CPU_LOG = 2000;
	inline constexpr int NES_ID_DEBUG_TOOLS_CPU_REGISTER_SPY = 2001;
	inline constexpr int NES_ID_DEBUG_TOOLS_CPU_CONTROLLER = 2002;

	// Menu bar help menu
	inline constexpr int NES_ID_HELP_VERSION = 3000;
	inline constexpr int NES_ID_HELP_ABOUT = 3001;
}

#endif //! NES_GLOBAL_IDS_HPP
