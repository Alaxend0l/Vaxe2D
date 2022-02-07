#include "apps/app_pico8.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "core/vWindow.h"
#include "core/vMemory.h"

#include <iostream>

namespace vaxe
{
    int vApp_Pico8::Run()
    {
        vWindow window { 160, 144, "Game Boy" };
        vMemory memory { 0x10000, MEMORY_ENDIAN_BIG };
        

        /* Loop until the user closes the window */
        while (!window.ShouldClose())
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */
            glfwSwapBuffers(window.GetGLFWWindow());

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
        return 0;
    }
}