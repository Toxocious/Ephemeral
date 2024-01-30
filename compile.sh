case "$(uname -s)" in
    Linux*)
        echo "~ Compiling for Linux"
        # Add Linux-specific commands or actions here
        premake5 --cc=clang --file=Build.lua gmake2
        ;;

    CYGWIN*|MINGW*|MSYS*)
        echo "~ Compiling for Windows"
        premake5 --file=Build.lua vs2022
        ;;

    Darwin*)
        echo "Compiling for macOS is not currently supported"
        # Add macOS-specific commands or actions here
        ;;

    *)
        echo "Unknown operating system; quitting"
        ;;
esac
