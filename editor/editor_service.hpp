#ifndef NES_EDITOR_SERVICE_HPP
#define NES_EDITOR_SERVICE_HPP

#include "utility/bit_tools.hpp"

#include <array>
#include <cstdint>
#include <functional>
#include <string_view>

namespace nes
{
    class CPU;
    class RAM;
    class RomFile;

    /**
     * Contains all editor business logic
     * UI is handled by the @see EditorRootFrame instead
     */
    class EditorService final
    {
    public:
        /**
         * Allocate resources and set initial states
         */
        bool Initialize();

        /**
         * Deallocate used resources
         */
        void Destroy();

        /**
         * Attempt to a load a NES ROM from disk
         * @param   path    Path to the ROM file
         * @return  True on success, false on failure
         */
        bool TryLoadRomFile(std::string_view path);

        /**
         * Check if a ROM has been loaded into memory
         * @return  True if a ROM file has been loaded into memory, false otherwise
         */
        bool HasLoadedRom() const;

        /**
         * Execute the next CPU instruction
         */
        void ExecuteNextCpuInstruction() const;

        /**
         * Set the address of the program counter to the specified value
         * @param   address     Address to set the program counter to
         */
        void SetCpuProgramCounter(std::uint16_t address) const;

        /**
         * Retrieve the current value of the CPU's program counter
         * @return  Program counter's value
         */
        std::uint16_t GetCpuProgramCounterValue() const;

        /**
         * Retrieve the current execution cycle of the CPU
         * @return  Current cycle
         */
        std::uint64_t GetCpuCurrentCycle() const;

        /**
         * Get the raw value of the stack pointer register
         * @return  Value of the stack pointer
         */
        std::uint8_t GetStackPointerValue() const;

    public:
        /**
         * Called whenever the editor has to update the stack visualization
         * The function argument passed is a copy of the current stack
         */
        std::function<void(std::array<Byte, 256>)> OnUpdateStackVisualization;

    private:
		CPU* Cpu;
		RAM* Ram;
		RomFile* ActiveRom;
    };
}

#endif //! NES_EDITOR_SERVICE_HPP
