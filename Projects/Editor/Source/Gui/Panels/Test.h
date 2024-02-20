#pragma once

#include <Util/Base.h>

#include <filesystem>

// #include <Scene/Entity.h>
// #include <Scene/Scene.h>

namespace Ephemeral
{
    class TestPanel
    {
    public:
        TestPanel();

        void OnImGuiRender();

    private:
        std::filesystem::path m_BaseDirectory;
        std::filesystem::path m_CurrentDirectory;
    };
}
