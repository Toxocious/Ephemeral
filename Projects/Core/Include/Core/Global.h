#pragma once

#ifndef EPH_CORE_GLOBAL_H
#    define EPH_CORE_GLOBAL_H

#    include <filesystem>

namespace Ephemeral
{
    class Global
    {
    public:
        static std::filesystem::path GetCoreAssetPath();
    };
}

#endif
