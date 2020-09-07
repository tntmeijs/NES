#ifndef NES_UI_RAM_VISUALIZER_HPP
#define NES_UI_RAM_VISUALIZER_HPP

namespace nes
{
	class RAM;
	class CPU;

	/**
	 * Editor UI element to visualize the current state of the RAM
	 * This element does not create an ImGui window, therefore, it is expected to
	 * either be part of an existing window, or a menu bar
	 */
	class UIRamVisualizer
	{
	public:
		/**
		 * Create a new RAM visualizer object
		 * @param	ramRef	Reference to the RAM object to visualize
		 * @param	cpuRef	Reference to the CPU object that uses the RAM object
		 */
		UIRamVisualizer(const RAM& ramRef, const CPU& cpuRef);

		/**
		 * Render the UI for this panel
		 */
		void Draw() const;

	private:
		const RAM& RamRef;
		const CPU& CpuRef;
	};
}

#endif //! NES_UI_RAM_VISUALIZER_HPP
