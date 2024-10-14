#pragma once

#ifndef EPH_CORE_CAMERA_H
#    define EPH_CORE_CAMERA_H

#    include <Core/Ephemeral.h>

#    include <MathGeoLib/Geometry/Frustum.h>

namespace Ephemeral
{
    class Camera
    {
    public:
        enum class RotationType
        {
            None,
            FirstPerson,
            Orbit
        };

    public:
        Camera( const char * id );
        ~Camera();

    public:
        void CameraMovement();
        void UpdateFrustum( int sizeX, int sizeY );

        void Zoom( float value );
        void LookAt( const float3 & position );

        inline const Frustum & GetFrustum() const
        {
            return frustum;
        }

        inline const char * GetID() const
        {
            return m_ID;
        }

    public:
        bool isActive = true;

        bool wasd_move = true;
        bool rf_move   = true;
        bool pan_move  = true;
        bool zoom_move = true;

        RotationType rotation = RotationType::FirstPerson;
        float3       pivot    = float3::zero;

        Frustum frustum;

        float m_Near = 0.1f;
        float m_Far  = 1000.f;

    private:
        const char * m_ID = "";

        float2 m_LastRight  = { -1.f, -1.f };
        float2 m_LastMiddle = { -1.f, -1.f };

        float m_FOV = 60.f;

        float m_PanSpeed   = 0.5f;
        float m_OrbitSpeed = 0.1f;
        float m_ZoomSpeed  = 15.f;
        float m_MoveSpeed  = 15.f;
        float m_TurboSpeed = 2.f;
    };
}

#endif
