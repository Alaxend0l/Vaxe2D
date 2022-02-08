#pragma once

#include <string>

// libs

#include "GL/glew.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_thread.h>
#include "GL/gl.h"

namespace vaxe
{
    class vWindow
    {
    public:
        vWindow(uint32_t width, uint32_t height, std::string name);
        ~vWindow();

        // Generic Functions

        bool ShouldClose() { return false; }

        // Getters and Setters

        SDL_Window* GetSDLWindow() { return m_window; }
        uint32_t GetWindowWidth() { return m_width; }
        uint32_t GetWindowHeight() { return m_height; }
    private:
        SDL_Window* m_window;

        std::string m_name;

        uint32_t m_width;
        uint32_t m_height;
    };
}