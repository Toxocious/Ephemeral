#ifndef EPH_RENDERING_IMGUI_HPP
#define EPH_RENDERING_IMGUI_HPP 1

#include <assert.h>
#include <imgui.h>
#include <string>

namespace Ephemeral
{
    namespace Rendering
    {
        auto Add_Text( float x, float y, std::wstring text, ImColor color ) -> void
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
    }
}

#endif
