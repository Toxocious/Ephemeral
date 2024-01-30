# Update all submodules
echo "~ Updating submodules"
git submodule update --recursive


# Generate necessary project files using Premake5
echo ""
echo "~ Beginning compilation"
case "$(uname -s)" in
    Linux*)
        echo "  ~ Compiling for Linux"
        # Add Linux-specific commands or actions here
        premake5 --cc=clang --file=Build.lua gmake2
        ;;

    CYGWIN*|MINGW*|MSYS*)
        echo "  ~ Compiling for Windows"
        premake5 --file=Build.lua vs2022
        ;;

    Darwin*)
        echo "  ! Compiling for macOS is not currently supported; quitting"
        exit
        ;;

    *)
        echo "  ! Unknown operating system; quitting"
        exit
        ;;
esac


# Check for Vulkan SDK installation
echo ""
echo "~ Checking for Vulkan SDK"
if command -v vulkaninfo &> /dev/null; then
    echo "  ! Vulkan SDK is installed"
else
    echo "  ! Vulkan SDK is not installed; please install it onto your system and add it to your PATH"
fi
