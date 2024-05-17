#pragma once

#ifndef EPH_CORE_SCENE_CAMERA_H
#    define EPH_CORE_SCENE_CAMERA_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

#    include <Renderer/Camera.h>

namespace Ephemeral
{
    class SceneCamera : public Module
    {
    public:
        SceneCamera( bool enabled = true );
        ~SceneCamera();

        bool CleanUp() override;

        bool Initialize() override;

        UpdateStatus PreUpdate() override;

        Camera * CreateCamera( const char * id );
        Camera * GetCamera( const char * id );

        void UpdateShaders( Camera * camera );

    private:
        // void SetFov();

        // void FitToMap() const;

        // void SetTopView() const;
        // void SetFrontView() const;

    private:
        std::vector<Camera *> m_Cameras;
        Camera *              m_Scene = nullptr;
    };
}

#endif
