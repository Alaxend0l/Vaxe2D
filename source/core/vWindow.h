#pragma once

#include <string>

// libs

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "GL/GL.h"

namespace vaxe
{
    class vWindow
    {
    public:
        vWindow(uint32_t width, uint32_t height, std::string name);
        ~vWindow();

        // Generic Functions

        bool ShouldClose() { return glfwWindowShouldClose(m_window); }

        // Getters and Setters

        GLFWwindow* GetGLFWWindow() { return m_window; }
        uint32_t GetWindowWidth() { return m_width; }
        uint32_t GetWindowHeight() { return m_height; }
    private:
        GLFWwindow* m_window;

        std::string m_name;

        uint32_t m_width;
        uint32_t m_height;
    };
}