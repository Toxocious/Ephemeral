#pragma once

#ifndef EPH_CORE_FILE_SYSTEM_H
#    define EPH_CORE_FILE_SYSTEM_H

#    include <Core/Ephemeral.h>

namespace Ephemeral
{
    struct Folder
    {
        friend class FileSystem;

    public:
        Folder * parent = nullptr;

        std::unordered_map<std::string, uint64_t> files; // <filename, last_time_write>
        std::vector<Folder *>                     folders;
        std::string                               full_path;

        std::string name;

        bool operator==( const std::string & path ) const
        {
            return full_path.compare( path ) == 0;
        }

    private:
        Folder() = default;
        Folder( std::string n, Folder * parent = nullptr );

        ~Folder()
        {
            for ( auto i = folders.begin(); i != folders.end(); ++i )
            {
                delete *i;
            }
        }
    };

    class FileSystem
    {
    public:
        static std::string OpenTextFile( const char * path );

        static bool Exists( const char * path );

        static uint64_t LastTimeWrite( const char * path );

        static std::string GetFileExtension( const char * file, bool with_dot = false );
        static std::string GetFullPath( const char * path );

        static std::filesystem::path GetCoreAssetPath();

        static Folder * GetFolders( std::string path );

        static std::string NormalizePath( const std::string & path );
    };
}

#endif
