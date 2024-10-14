#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/Scene.h>

#include <Renderer/Viewport.h>

namespace Ephemeral
{
    Scene::Scene( bool enabled )
        : Module( "Scene", enabled )
    {
    }

    Scene::~Scene()
    {
    }

    bool Scene::CleanUp()
    {
        return true;
    }

    bool Scene::Initialize()
    {
        return true;
    }

    bool Scene::Start()
    {
        m_SceneViewport = App->m_Renderer->GetViewport( "Scene" );

        return true;
    }

    UpdateStatus Scene::Update()
    {
        if ( m_SceneViewport == nullptr )
        {
            m_SceneViewport = App->m_Renderer->GetViewport( "Scene" );

            if ( m_SceneViewport == nullptr )
            {
                // EPH_CORE_WARN( "Couldn't get scene viewport for scene '{0}'.", "Scene" );
                return UpdateStatus::UPDATE_ERROR;
            }
        }

        // EPH_CORE_WARN( "Updating Scene '{0}'.", "Scene" );

        m_SceneViewport->Begin();

        {
            static auto shader = App->m_Renderer->GetShader( "Default" );
            shader->Use();
            shader->SetMat4( "model", float4x4::identity );
        }

        m_SceneViewport->End();

        return UpdateStatus::UPDATE_CONTINUE;
    }
}
