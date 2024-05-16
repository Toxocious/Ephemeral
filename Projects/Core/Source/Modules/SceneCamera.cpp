#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/SceneCamera.h>

namespace Ephemeral
{
    SceneCamera::SceneCamera( bool enabled )
        : Module( "SceneCamera", enabled )
    {
    }

    SceneCamera::~SceneCamera()
    {
    }

    bool SceneCamera::CleanUp()
    {
        for ( auto camera : m_Cameras )
        {
            delete camera;
        }

        return true;
    }

    bool SceneCamera::Initialize()
    {
        auto height = App->m_Window->GetHeight();
        auto width  = App->m_Window->GetWidth();

        m_Scene = CreateCamera( "Scene" );
        m_Scene->frustum.SetVerticalFovAndAspectRatio( DegToRad( 70.f ), ( float ) width / ( float ) height );

        return true;
    }

    UpdateStatus SceneCamera::PreUpdate()
    {
        for ( auto camera : m_Cameras )
        {
            if ( camera->isActive )
            {
                camera->CameraMovement();
            }
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    Camera * SceneCamera::CreateCamera( const char * id )
    {
        for ( auto camera : m_Cameras )
        {
            if ( strcmp( camera->GetID(), id ) == 0 )
            {
                return camera;
            }
        }

        Camera * newCamera = new Camera( id );
        m_Cameras.push_back( newCamera );

        return newCamera;
    }

    void SceneCamera::UpdateShaders( Camera * camera )
    {
        // auto gridShader = App->m_Renderer->GetShader( "Grid" );
        // gridShader->Use();
    }
}
