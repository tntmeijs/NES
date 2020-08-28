#ifndef NES_EDITOR_HPP
#define NES_EDITOR_HPP

// SFML forward declarations
namespace sf
{
    class Event;
    class RenderWindow;
    class Time;
}

namespace nes
{
    class UIPanel;
    class CPU;
    class RAM;

    class Editor
    {
    public:
        /**
         * Create a new editor instance
         * @param   window  SFML window to render the UI to
         * @param   cpu     Reference to the emulator's CPU object
         * @param   ram     Reference to the emulator's RAM object
         */
        Editor(sf::RenderWindow& window, const CPU& cpu, const RAM& ram);

        /*
         * Initialize the NES editor
         */
        void Initialize();

        /**
         * Update NES editor state
         * @param   deltaTime   Time between main loop ticks
         */
        void Update(const sf::Time deltaTime);

        /**
         * SFML input, allows the editor to respond to the user
         * @param   event   SFML event object
         */
        void ProcessEvent(const sf::Event event) const;

        /**
         * Render all UI
         */
        void DrawUI() const;

        /**
         * Clean up all editor resources
         */
        void Destroy();

    private:
        /**
         * Style the UI
         */
        void ApplyStyle();

    private:
        sf::RenderWindow& WindowRef;

        const CPU& CpuRef;
        const RAM& RamRef;

        const UIPanel* TestPanel;
    };
}

#endif //! NES_EDITOR_HPP
