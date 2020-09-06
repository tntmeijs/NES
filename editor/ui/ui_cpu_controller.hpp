#ifndef NES_UI_CPU_CONTROLLER_HPP
#define NES_UI_CPU_CONTROLLER_HPP

namespace nes
{
	class CPU;

	/**
	 * Editor UI element that helps visualize and / or control the state of the CPU
	 * This element does not create an ImGui window, therefore, it is expected to
	 * either be part of an existing window, or a menu bar
	 */
	class UICpuController
	{
	public:
		/**
		 * Create a new CPU controller object
		 * @param	cpuRef	Reference to the CPU object to control
		 */
		UICpuController(CPU& cpuRef);

		/**
		 * Render the UI for this panel
		 */
		void Draw() const;

	private:
		CPU& CpuRef;
	};
}

#endif //! NES_UI_CPU_CONTROLLER_HPP
