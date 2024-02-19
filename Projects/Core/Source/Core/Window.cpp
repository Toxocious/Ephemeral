#include <Core/Window.hpp>
#include <Rendering/ImGui.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#define GL_SILENCE_DEPRECATION
#pragma comment( lib, "glew32s" )
#include <GL/glew.h>

#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>

#pragma comment( lib, "imgui" )
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

static void glfw_error_callback( int error, const char * description )
{
    fprintf( stderr, "GLFW Error %d: %s\n", error, description );
}

namespace Ephemeral
{
    namespace Core
    {
        Window::Window( int width, int height, const std::string & title )
            : m_Width( width ), m_Height( height ), m_Title( title )
        {
            glfwSetErrorCallback( glfw_error_callback );
            if ( !glfwInit() )
            {
                return;
            }

            const char * glsl_version = "#version 150";
            glfwWindowHint( GLFW_SAMPLES, 4 );
            glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
            glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
            glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
            // glfwWindowHint( GLFW_DECORATED, GL_FALSE ); // Removes title bar
            // glfwWindowHint( GLFW_VISIBLE, GL_FALSE ); // Makes window invisible

            m_Window = glfwCreateWindow( m_Width, m_Height, m_Title.c_str(), nullptr, nullptr );
            if ( m_Window == nullptr )
            {
                return;
            }

            glfwMakeContextCurrent( m_Window );
            glfwSwapInterval( 1 );

            // Initialize Glew
            glewExperimental = GL_TRUE;
            GLenum err       = glewInit();
            if ( GLEW_OK != err )
            {
                std::cerr << "Error: " << glewGetErrorString( err ) << std::endl;
            }
            std::cerr << "Status: Using GLEW " << glewGetString( GLEW_VERSION ) << std::endl;

            // Initialize Dear ImGui
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO & io = ImGui::GetIO();
            ( void ) io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

            Window::SetImGuiTheme();

            ImGui_ImplGlfw_InitForOpenGL( m_Window, false );
            ImGui_ImplOpenGL3_Init( glsl_version );
        }

        Window::~Window()
        {
            glfwDestroyWindow( m_Window );
            glfwTerminate();
        }

        void Window::Run() const noexcept
        {
            while ( !Window::shouldClose() )
            {
                Window::pollEvents();

                // Please note: this is old, OpenGL 1.1 code. It's here for simplicity.
                {
                    glBegin( GL_TRIANGLES );
                    glVertex2f( -0.5f, -0.5f );
                    glVertex2f( 0.5f, -0.5f );
                    glVertex2f( 0, 0.5f );
                    glEnd();
                }

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // Basic imgui window
                {
                    ImGui::Begin( "Another Window" );
                    ImGui::Text( "Hello from another window" );
                    ImGui::End();
                }

                Ephemeral::Rendering::Add_Text( 0.f, 0.f, L"Bing bong", ImColor( 255, 255, 255 ) );

                ImGui::Render();

                ImVec4 clear_color = Ephemeral::Rendering::RGBA_To_ImVec4( 22, 22, 28 );
                glClearColor( clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w );
                glClear( GL_COLOR_BUFFER_BIT );

                ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

                Window::swapBuffers();
            }
        }

        bool Window::shouldClose() const noexcept
        {
            return glfwWindowShouldClose( m_Window ) != 0;
        }

        void Window::pollEvents() const noexcept
        {
            glfwPollEvents();
        }

        void Window::swapBuffers() const noexcept
        {
            glfwSwapBuffers( m_Window );
        }

        std::pair<int, int> Window::getWindowSize() const noexcept
        {
            std::pair<int, int> sz {};
            glfwGetWindowSize( m_Window, &sz.first, &sz.second );
            return sz;
        }

        void Window::SetImGuiTheme()
        {
            ImGui::StyleColorsDark();

            auto & colors             = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4 { 0.1f, 0.105f, 0.11f, 1.0f };

            // Headers
            colors[ImGuiCol_Header]        = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_HeaderHovered] = ImVec4 { 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_HeaderActive]  = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };

            // Buttons
            colors[ImGuiCol_Button]        = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_ButtonHovered] = ImVec4 { 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_ButtonActive]  = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };

            // Frame BG
            colors[ImGuiCol_FrameBg]        = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_FrameBgHovered] = ImVec4 { 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_FrameBgActive]  = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };

            // Tabs
            colors[ImGuiCol_Tab]                = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabHovered]         = ImVec4 { 0.38f, 0.3805f, 0.381f, 1.0f };
            colors[ImGuiCol_TabActive]          = ImVec4 { 0.28f, 0.2805f, 0.281f, 1.0f };
            colors[ImGuiCol_TabUnfocused]       = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };

            // Title
            colors[ImGuiCol_TitleBg]          = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgActive]    = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
        }
    }
}
