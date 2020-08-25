#ifndef NES_UI_PANEL_HPP
#define NES_UI_PANEL_HPP

#include "ui_element.hpp"

#include <cstdint>
#include <string>

namespace nes
{
    class UIPanel : public UIElement
    {
    public:
        /**
         * Create a new panel
         * @param   viewportWidth   Total width of the viewport in pixels
         * @param   viewportHeight  Total height of the viewport in pixels
         * @param   x               Panel X coordinate in pixels from the top-left viewport corner
         * @param   y               Panel Y coordinate in pixels from the top-left viewport corner
         * @param   width           Width of the panel as a percentage (0.0f - 1.0f) of the viewport width
         * @param   height          Height of the panel as a percentage (0.0f - 1.0f) of the viewport height
         */
        UIPanel(
            std::uint32_t viewportWidth,
            std::uint32_t viewportHeight,
            std::uint32_t x,
            std::uint32_t y,
            float width,
            float height);

        /**
         * Record UI draw commands
         */
        void Draw() const final override;

    protected:
        /**
         * Any derived classes should implement this method to render their UI
         */
        virtual void DrawImpl() const;

    private:
        std::uint32_t X;
        std::uint32_t Y;
        std::uint32_t ViewportWidth;
        std::uint32_t ViewportHeight;

        float Width;
        float Height;

        std::string PanelName;
    };
}

#endif //! NES_UI_PANEL_HPP
