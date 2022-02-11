#include "core/vWindow.h"

namespace vaxe
{
    vWindow::vWindow(byte_4 width, byte_4 height, std::string name) : m_width(width), m_height(height), m_name(name)
    {
        /* Initialize the library */
        SDL_Init(SDL_INIT_EVERYTHING);

        // Setup window
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute( SDL_GL_ACCELERATED_VISUAL, 1 ); 
        SDL_DisplayMode current;
        SDL_GetCurrentDisplayMode(0, &current);

        m_window = SDL_CreateWindow(
            name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_RENDERER_ACCELERATED | SDL_WINDOW_RESIZABLE);
    }

    vWindow::~vWindow()
    {
        SDL_DestroyWindow(m_window);
    }
}