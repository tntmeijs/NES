#ifndef NES_UI_CPU_CONTROLLER_HPP
#define NES_UI_CPU_CONTROLLER_HPP

#include "ui_panel.hpp"

namespace nes
{
	class CPU;

	/**
	 * Editor UI element that helps visualize and / or control the state of the CPU
	 */
	class UICpuController : public UIPanel
	{
	public:
		/**
		 * Create a new CPU visualizer object
		 * @param	cpuRef	Reference to the CPU object to control
		 */
		UICpuController(CPU& cpuRef);

	protected:
		virtual void DrawImpl() const override;

	private:
		CPU& CpuRef;
	};
}

#endif //! NES_UI_CPU_CONTROLLER_HPP
