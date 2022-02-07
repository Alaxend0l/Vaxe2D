#include "core/vWindow.h"

namespace vaxe
{
    vWindow::vWindow(uint32_t width, uint32_t height, std::string name) : m_width(width), m_height(height), m_name(name)
    {
        /* Initialize the library */
        glfwInit();

        /* Create a windowed mode window and its OpenGL context */
        m_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

        /* Make the window's context current */
        glfwMakeContextCurrent(m_window);
    }

    vWindow::~vWindow()
    {
        glfwTerminate();
    }
}