#include <Core/Ephemeral.h>

#include <Core/Global.h>

#include <filesystem>

namespace Ephemeral
{
    std::filesystem::path Global::GetCoreAssetPath()
    {
        namespace fs = std::filesystem;

        std::string currentPath = fs::current_path().string();
        size_t      pos         = currentPath.find_last_of( fs::path::preferred_separator );

        if ( pos != std::string::npos )
        {
            std::string parentPath = currentPath.substr( 0, pos );

            // Append the child directory name to the parent directory path
            std::string childPath = parentPath + "\\Core\\Assets";

            if ( fs::exists( childPath ) )
            {
                EPH_CORE_TRACE( "Global::GetCoreAssetPath() = {0}", childPath );

                return childPath;
            }
            else
            {
                EPH_CORE_WARN( "Child path '{0}' does not exist.", childPath );
            }
        }

        return std::filesystem::current_path();
    }
}
