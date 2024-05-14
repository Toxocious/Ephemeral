#include <Core/Ephemeral.h>

#include <Util/Math/Integer.h>

namespace Ephemeral
{
    IntegerUtil::IntegerUtil()
    {
    }

    IntegerUtil::IntegerUtil( int val )
        : x( val ), y( val )
    {
    }

    IntegerUtil::IntegerUtil( int x, int y )
        : x( x ), y( y )
    {
    }

    IntegerUtil::~IntegerUtil()
    {
    }

    void IntegerUtil::Set( int val )
    {
        x = y = val;
    }

    void IntegerUtil::Set( int x, int y )
    {
        this->x = x;
        this->y = y;
    }

    void IntegerUtil::Set( const ImVec2 & vec )
    {
        x = ( int ) vec.x;
        y = ( int ) vec.y;
    }

    int * IntegerUtil::ptr()
    {
        return &x;
    }

    const int * IntegerUtil::ptr() const
    {
        return &x;
    }

    std::string IntegerUtil::ToString() const
    {
        return std::string( "(" + std::to_string( x ) + ", " + std::to_string( y ) + ")" );
    }

    IntegerUtil IntegerUtil::operator+( const IntegerUtil & c ) const
    {
        return IntegerUtil( x - c.x, y - c.y );
    }

    IntegerUtil IntegerUtil::operator-( const IntegerUtil & c ) const
    {
        return IntegerUtil( x - c.x, y - c.y );
    }

    IntegerUtil IntegerUtil::operator*( const IntegerUtil & c ) const
    {
        return IntegerUtil( x * c.x, y * c.y );
    }
}
