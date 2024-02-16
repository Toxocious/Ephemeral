#ifndef EPH_CORE_WINDOW_HPP
#define EPH_CORE_WINDOW_HPP 1

#include <memory>
#include <string>

struct GLFWwindow;

namespace Ephemeral
{
    namespace Core
    {
        class Window
        {
        public:
            Window( int width, int height, const std::string & title );
            ~Window();

            void Run() const noexcept;

            bool shouldClose() const noexcept;
            void pollEvents() const noexcept;
            void swapBuffers() const noexcept;

            std::pair<int, int> getWindowSize() const noexcept;

            void Window::SetImGuiTheme();

        private:
            int                 m_Width;
            int                 m_Height;
            const std::string & m_Title;

            GLFWwindow * m_Window;
        };
    }
}

#endif
