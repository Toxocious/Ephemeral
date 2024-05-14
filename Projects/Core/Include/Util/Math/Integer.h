#pragma once

#ifndef EPH_CORE_UTIL_MATH_H
#    define EPH_CORE_UTIL_MATH_H

#    include <Core/Ephemeral.h>

#    include <string>

struct ImVec2;

namespace Ephemeral
{
    class IntegerUtil
    {
    public:
        IntegerUtil();
        IntegerUtil( int val );
        IntegerUtil( int x, int y );
        ~IntegerUtil();

        void Set( int val );
        void Set( int x, int y );
        void Set( const ImVec2 & vec );

        int *       ptr();
        const int * ptr() const;

        std::string ToString() const;

        IntegerUtil operator+( const IntegerUtil & c ) const;
        IntegerUtil operator-( const IntegerUtil & c ) const;
        IntegerUtil operator*( const IntegerUtil & c ) const;

    public:
        int x = 0;
        int y = 0;
    };
}

#endif
