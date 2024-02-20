#include <Core/Ephemeral.h>

#include "Test.h"

#include <assert.h>
#include <imgui.h>

namespace Ephemeral
{
    TestPanel::TestPanel()
        : m_BaseDirectory( "" ), m_CurrentDirectory( m_BaseDirectory )
    {
    }

    void TestPanel::OnImGuiRender()
    {
        ImGui::Begin( "Content Browser" );
        {
            ImGui::Text( "Rendering from application's Gui/Panels directory." );
        }
        ImGui::End();
    }
}
