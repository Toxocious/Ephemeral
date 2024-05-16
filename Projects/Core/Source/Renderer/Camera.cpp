#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Renderer/Camera.h>

#include <MathGeoLib/Math/Quat.h>

namespace Ephemeral
{
    Camera::Camera( const char * id )
        : m_ID( id )
    {
        frustum.SetFrame( { 2.f, 7.f, -10.f }, float3::unitZ, float3::unitY );
        frustum.SetKind( FrustumProjectiveSpace::FrustumSpaceGL, FrustumHandedness::FrustumLeftHanded );
        frustum.SetViewPlaneDistances( 0.1f, 1000.f );

        m_FOV = DegToRad( 60.f );
    }

    Camera::~Camera()
    {
    }

    void Camera::CameraMovement()
    {
        // Not if it is being handled by IMGUI
        ImGuiIO & io = ImGui::GetIO();
        ( void ) io;
        if ( io.WantCaptureKeyboard || io.WantCaptureMouse )
        {
            return;
        }

        auto window = App->m_Window->GetGLFWWindow();

        if ( wasd_move )
        {
            // Forward -- Zooms in
            if ( glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS )
            {
                Zoom( m_MoveSpeed * App->GetDeltaTime() );
            }

            // Backward -- Zooms out
            if ( glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS )
            {
                Zoom( -m_MoveSpeed * App->GetDeltaTime() );
            }

            // Left
            if ( glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS )
            {
                frustum.Translate( frustum.Front().Cross( frustum.Up() ) * m_MoveSpeed * App->GetDeltaTime() );
            }

            // Right
            if ( glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS )
            {
                frustum.Translate( -frustum.Front().Cross( frustum.Up() ) * m_MoveSpeed * App->GetDeltaTime() );
            }
        }
    }

    void Camera::UpdateFrustum( int sizeX, int sizeY )
    {
        if ( frustum.Type() == FrustumType::PerspectiveFrustum )
        {
            frustum.SetVerticalFovAndAspectRatio( m_FOV, ( float ) sizeX / ( float ) sizeY );
        }
        else
        {
            float aspect = ( float ) sizeX / ( float ) sizeY;
            frustum.SetOrthographic( frustum.OrthographicWidth(), frustum.OrthographicWidth() / aspect );
        }
    }

    void Camera::Zoom( float value )
    {
        if ( frustum.Type() == FrustumType::PerspectiveFrustum )
        {
            frustum.Translate( frustum.Front() * value );
        }
        else
        {
            value        *= -2.f;
            float aspect  = frustum.OrthographicWidth() / frustum.OrthographicHeight();
            if ( frustum.OrthographicWidth() + value > 0.f )
            {
                frustum.SetOrthographic( frustum.OrthographicWidth() + value, ( frustum.OrthographicWidth() + value ) / aspect );
            }
        }
    }

    void Camera::LookAt( const float3 & position )
    {
        Quat lookAt = Quat::LookAt( frustum.Front(), ( position - frustum.Pos() ).Normalized(), frustum.Up(), float3::unitY );
        frustum.SetFront( lookAt * frustum.Front() );
        frustum.SetUp( lookAt * frustum.Up() );
    }
}

