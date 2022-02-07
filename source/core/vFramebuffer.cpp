#include "core/vFramebuffer.h"

namespace vaxe
{
    vFramebuffer::vFramebuffer(uint32_t width, uint32_t height) : m_width(width), m_height(height)
    {
        m_data = std::vector<unsigned char>(width * height * 3);

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
        glTexImage2D
            (
            GL_TEXTURE_2D, 0,
            GL_RGB, width, height, 0,
            GL_RGB, GL_UNSIGNED_BYTE, &m_data[0]
            );

        ClearBuffer();
    }

    void vFramebuffer::ClearBuffer()
    {
        for (auto colorValue : m_data)
        {
            colorValue = 0;
        }
    }

    void vFramebuffer::Render(vWindow& window)
    {
        GLuint readFboId = 0;
        glGenFramebuffers(1, &readFboId);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, readFboId);
        glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, (GLuint)m_data[0], 0);
        glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, window.GetWindowWidth(), window.GetWindowHeight(), GL_COLOR_BUFFER_BIT, GL_LINEAR);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glDeleteFramebuffers(1, &readFboId);
    }
}