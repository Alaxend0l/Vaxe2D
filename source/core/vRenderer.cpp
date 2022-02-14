#include "core/vRenderer.h"

namespace vaxe
{
    vRenderer::vRenderer(SDL_Window* window, byte_4 flags) : m_window(window), m_flags(flags)
    {
        m_renderer = SDL_CreateRenderer(m_window, -1, m_flags);
        //m_renderTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    }

    vRenderer::~vRenderer()
    {
        SDL_DestroyRenderer(m_renderer);
    }

    void vRenderer::PerformRender(SDL_Texture* texture)
    {
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }

    int vRenderer::PerformSceneRender(std::shared_ptr<vScene> scene, vFramebuffer* buffer)
    {
        //Begin and Clear the Rendering
        SDL_SetRenderTarget(m_renderer, buffer->GetTexture());
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 255, 255);
        SDL_RenderClear(m_renderer);

        //Display all graphics in the scene
        /*
        scene->GetRegistry().each([&](auto entityID)
        {
            vEntity entity{ entityID , scene.get() };
            
            if (entity.HasComponent<SpriteRenderer>())
            {
                auto& info = entity.GetComponent<EntityInfo>();

                if (info.isEnabled)
                {
                    auto& transform = entity.GetComponent<Transform2D>();
                    auto& sprite = entity.GetComponent<SpriteRenderer>();

                    SDL_Rect spriteRect;

                    spriteRect.x = transform.position.x;
                    spriteRect.y = transform.position.y;
                    spriteRect.w = sprite.m_texture->GetTextureWidth() * transform.scale.x;
                    spriteRect.h = sprite.m_texture->GetTextureHeight() * transform.scale.y;

                    SDL_RenderCopyEx(m_renderer, sprite.m_texture->GetTexture(), NULL, &spriteRect, transform.rotation, NULL, SDL_FLIP_NONE);
                }
                
            }
        });
        */

        //Reset Render Target
        //SDL_RenderPresent(m_renderer);
        SDL_SetRenderTarget(m_renderer, NULL);
        return 0;
    }
}