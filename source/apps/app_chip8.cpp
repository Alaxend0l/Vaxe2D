#include "apps/app_chip8.h"

#include "core/vWindow.h"
#include "core/vRenderer.h"
#include "core/vMemory.h"
#include "core/vFramebuffer.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 64
#define HEIGHT 32

namespace vaxe
{
    int vApp_Chip8::Run()
    {
        vWindow window { WIDTH * 8, HEIGHT * 8, "CHIP-8" };
        vRenderer renderer { window.GetSDLWindow(), SDL_RENDERER_ACCELERATED};
        SDL_RenderSetLogicalSize(renderer.GetRenderer(), WIDTH, HEIGHT);

        SDL_GLContext gl_context = SDL_GL_CreateContext(window.GetSDLWindow());
        SDL_GL_SetSwapInterval(0);  // Enable vsync

        vMemory memory { 4096 , MEMORY_ENDIAN_BIG };
        vFramebuffer framebuffer {renderer.GetRenderer(), WIDTH, HEIGHT};

        int i = 0;
        

        /* Loop until the user closes the window */
        while (!quit)
        {
            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
                }
            }

            framebuffer.TESTONLY_SetValue(i, 0xFF);
            i++;

            framebuffer.UpdateTexture();
            renderer.PerformRender(framebuffer.GetTexture());

            SDL_Delay(1000 / 60);
        }
        
        return 0;
    }
}