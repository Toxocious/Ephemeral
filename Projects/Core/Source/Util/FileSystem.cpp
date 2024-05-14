#include <Core/Ephemeral.h>

#include <Util/FileSystem.h>

#include <filesystem>
#include <fstream>
#include <stack>

namespace Ephemeral
{
    namespace fs = std::filesystem;

    /**
     * Returns a Folder * which contains all folders inside of the given file path.
     */
    Folder * FileSystem::GetFolders( std::string path )
    {
        Folder *             parent = new Folder( path, nullptr );
        std::stack<Folder *> stack;
        stack.push( parent );

        while ( !stack.empty() )
        {
            Folder * folder = stack.top();
            stack.pop();

            for ( const auto & entry : fs::directory_iterator( folder->full_path ) )
            {
                if ( entry.is_directory() )
                {
                    Folder * f = new Folder( ( entry.path().u8string() + '/' ).c_str(), folder );
                    stack.push( f );
                    folder->folders.push_back( f );
                }
                else
                {
                    folder->files[entry.path().filename().string()] = LastTimeWrite(
                        ( folder->full_path + entry.path().filename().string() ).c_str()
                    );
                }
            }
        }

        return parent;
    }

    /**
     * Returns a fs::path to /Projects/Core/Assets
     */
    std::filesystem::path FileSystem::GetCoreAssetPath()
    {
        namespace fs = std::filesystem;

        std::string currentPath = fs::current_path().string();
        size_t      pos         = currentPath.find_last_of( fs::path::preferred_separator );

        if ( pos != std::string::npos )
        {
            std::string parentPath = currentPath.substr( 0, pos );
            std::string childPath  = parentPath + "\\Core\\Assets";

            if ( fs::exists( childPath ) )
            {
                return childPath;
            }
            else
            {
                EPH_CORE_WARN( "Child path '{0}' does not exist.", childPath );
            }
        }

        return std::filesystem::current_path();
    }

    /**
     * Returns a string containing the full OS path.
     */
    std::string FileSystem::GetFullPath( const char * path )
    {
        return fs::absolute( path ).string();
    }

    /**
     * Opens a text file and returns its contents.
     */
    std::string FileSystem::OpenTextFile( const char * path )
    {
        try
        {
            std::ifstream in( path, std::ios::in | std::ios::binary );
            if ( in )
            {
                std::string contents;

                in.seekg( 0, std::ios::end );
                contents.resize( in.tellg() );
                in.seekg( 0, std::ios::beg );
                in.read( &contents[0], contents.size() );
                in.close();

                return contents;
            }
            throw path;
        }
        catch ( ... )
        {
            EPH_CORE_WARN( "Cannot open file with path '{0}'", path );
            throw path;
        }
    }

    /**
     * Returns a string containing the type of extension of a file.
     */
    std::string FileSystem::GetFileExtension( const char * file, bool with_dot )
    {
        std::string f( file );
        std::string ext;

        for ( auto i = f.rbegin(); i != f.rend(); ++i )
        {
            if ( *i != '.' )
            {
                ext.push_back( std::tolower( *i ) );
            }
            else
            {
                if ( with_dot )
                {
                    ext.push_back( std::tolower( *i ) );
                }
                break;
            }
        }

        std::reverse( ext.begin(), ext.end() );

        return ext;
    }

    /**
     * Normalizes a given file path.
     */
    std::string FileSystem::NormalizePath( const std::string & path )
    {
        std::string ret;

        auto i = path.begin();
        while ( i != path.end() )
        {
            if ( *i == '\\' )
            {
                ret.push_back( '/' );
            }
            else
            {
                ret.push_back( *i );
            }

            ++i;
        }

        return ret;
    }

    /**
     * Checks to see if a given file path exists.
     */
    bool FileSystem::Exists( const char * path )
    {
        try
        {
            return fs::exists( path );
        }
        catch ( const std::filesystem::filesystem_error & e )
        {
            EPH_CORE_WARN( "Failed to check if the path exists due to '{0}'", e.what() );
        }

        return false;
    }

    /**
     * Returns the last time at which a file was written to.
     */
    uint64_t FileSystem::LastTimeWrite( const char * path )
    {
        struct stat time;

        if ( stat( path, &time ) == 0 )
        {
            return time.st_mtime;
        }

        return 0ULL;
    }

    /**
     * Constructs a new Folder object.
     */
    Folder::Folder( std::string n, Folder * parent )
        : full_path( FileSystem::NormalizePath( n ) ), parent( parent )
    {
        for ( auto i = full_path.rbegin(); i != full_path.rend(); ++i )
        {
            if ( i != full_path.rbegin() )
            {
                if ( *i == '/' || *i == '\\' || *i == '//' )
                {
                    break;
                }

                name.push_back( *i );
            }
        }

        std::reverse( name.begin(), name.end() );
    }
}
