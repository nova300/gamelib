#pragma once
#include <raymath.h>

namespace Math
{
    struct float2;
    struct float3;
    struct float4;
}


constexpr Vector2 operator Math::float2()
{
    
}

namespace Math
{
    struct float2
    {
        float x;
        float y;

        //arithmetics
        float2 operator+(float2 const& obj)
        {
            return Vector2Add(*this, obj);
        }

        //internal casts

        //external casts
        operator Vector2()
        {
            return Vector2{x, y};
        }
    };

    struct float3
    {
        float x;
        float y;
        float z;

        //internal casts
        operator Math::float2()
        {
            return Math::float2{x , y};
        }

        //external casts
        operator Vector2()
        {
            return Vector2{x, y};
        }
        operator Vector3()
        {
            return Vector3{x, y, z};
        }
    };

    struct float4
    {
        float x;
        float y;
        float z;
        float w;

        //internal casts
        operator Math::float2()
        {
            return Math::float2{x, y};
        }
        operator Math::float3()
        {
            return Math::float3{x, y, z};
        }

        //external casts
        operator Vector2()
        {
            return Vector2{x, y};
        }
        operator Vector3()
        {
            return Vector3{x, y, z};
        }
        operator Vector4()
        {
            return Vector4{x, y, z, w};
        }

    };


};