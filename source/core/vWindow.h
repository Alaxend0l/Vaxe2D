#pragma once

#include <string>

#include "types/vByte4.h"

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
        vWindow(byte_4 width, byte_4 height, std::string name);
        ~vWindow();

        // Generic Functions

        bool ShouldClose() { return false; }

        // Getters and Setters

        SDL_Window* GetSDLWindow() { return m_window; }
        byte_4 GetWindowWidth() { return m_width; }
        byte_4 GetWindowHeight() { return m_height; }
    private:
        SDL_Window* m_window;

        std::string m_name;

        byte_4 m_width;
        byte_4 m_height;
    };
}