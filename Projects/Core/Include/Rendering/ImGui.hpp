#ifndef EPH_RENDERING_IMGUI_HPP
#define EPH_RENDERING_IMGUI_HPP 1

#include <assert.h>
#include <imgui.h>
#include <string>

namespace Ephemeral
{
    namespace Rendering
    {
        auto Add_Text( float x, float y, std::wstring text, ImColor color = ImColor( 222.f, 222.f, 222.f, 1.f ) ) -> void
        {
            auto DrawList = ImGui::GetForegroundDrawList();
            auto wText    = std::string( text.begin(), text.end() );

            DrawList->AddText( ImVec2( x + 1, y + 1 ), ImColor( 0, 0, 0, 255 ), wText.c_str() );
            DrawList->AddText( ImVec2( x, y ), color, wText.c_str() );
        }

        auto RGBA_To_ImVec4( int r, int g, int b, float a = 1.0f ) -> ImVec4
        {
            return ImVec4( ( float ) r / 255, ( float ) g / 255, ( float ) b / 255, a );
        }

        namespace Overlay
        {
            auto Debug_Stats( float x, float y ) -> void
            {
                Add_Text( x, y, L"Test" );
                Add_Text( x + 20, y + 20, L"Bing bong" );

                //     std::string name = "None";
                //     // if ( m_HoveredEntity )
                //     // {
                //     //     name = m_HoveredEntity.GetComponent<TagComponent>().Tag;
                //     // }
                //     ImGui::Text( "Hovered Entity: %s", name.c_str() );

                //     ImGui::Text( "Renderer2D Stats:" );
                //     ImGui::Text( " ~ Draw Calls: N/A" );
                //     ImGui::Text( " ~ Quads: N/A" );
                //     ImGui::Text( " ~ Vertices: N/A" );
                //     ImGui::Text( " ~ Indices: N/A" );

                //     ImGui::Text( "Object Stats:" );
                //     ImGui::Text( " ~ Total Objects: N/A" );
                //     ImGui::Text( " ~ Total NPCs: N/A" );
                //     ImGui::Text( " ~ Total Warps: N/A" );
            }
        }
    }
}

#endif
