#pragma once

#include <Rendering/Layer.h>

#include <Events/AppEvent.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

namespace Ephemeral
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent( Event & e ) override;

        void Begin();
        void End();

        void BlockEvents( bool block )
        {
            m_BlockEvents = block;
        }

        void SetDarkThemeColors();

        uint32_t GetActiveWidgetID() const;

    private:
        bool m_BlockEvents = true;
    };
}
