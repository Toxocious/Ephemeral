#include <Core/Ephemeral.h>

#include <Util/Math/ImVec.h>

namespace Ephemeral
{
    ImVec2 operator+( const ImVec2 & lhs, const ImVec2 & rhs )
    {
        return ImVec2( lhs.x + rhs.x, lhs.y + rhs.y );
    }
}
