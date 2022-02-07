#include "apps/app_chip8.h"

#include "core/vWindow.h"
#include "core/vMemory.h"
#include "core/vFramebuffer.h"

#include <iostream>

#define WIDTH 64
#define HEIGHT 32

namespace vaxe
{
    int vApp_Chip8::Run()
    {
        vWindow window { WIDTH * 4, HEIGHT * 4, "CHIP-8" };
        vMemory memory { 4096 , MEMORY_ENDIAN_BIG };
        vFramebuffer framebuffer {WIDTH, HEIGHT};
        

        /* Loop until the user closes the window */
        while (!window.ShouldClose())
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            framebuffer.Render(window);

            /* Swap front and back buffers */
            glfwSwapBuffers(window.GetGLFWWindow());

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}