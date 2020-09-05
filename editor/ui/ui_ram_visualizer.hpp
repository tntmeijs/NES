#ifndef NES_UI_RAM_VISUALIZER_HPP
#define NES_UI_RAM_VISUALIZER_HPP

#include "ui_panel.hpp"

namespace nes
{
	class RAM;
	class CPU;

	/**
	 * Editor UI element to visualize the current state of the RAM
	 */
	class UIRamVisualizer : public UIPanel
	{
	public:
		/**
		 * Create a new RAM visualizer object
		 * @param	ramRef	Reference to the RAM object to visualize
		 * @param	cpuRef	Reference to the CPU object that uses the RAM object
		 */
		UIRamVisualizer(const RAM& ramRef, const CPU& cpuRef);

	protected:
		/**
		 * Render the UI for this panel
		 */
		virtual void DrawImpl() const override;

	private:
		const RAM& RamRef;
		const CPU& CpuRef;
	};
}

#endif //! NES_UI_RAM_VISUALIZER_HPP
