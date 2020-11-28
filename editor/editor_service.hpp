#ifndef NES_EDITOR_SERVICE_HPP
#define NES_EDITOR_SERVICE_HPP

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
         * Execute the next CPU instruction
         */
        void ExecuteNextCpuInstruction() const;

    private:
		CPU* Cpu;
		RAM* Ram;
		RomFile* ActiveRom;
    };
}

#endif //! NES_EDITOR_SERVICE_HPP
