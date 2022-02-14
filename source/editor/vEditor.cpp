#include "editor/vEditor.h"

namespace vaxe
{
    vEditor::vEditor()
    {
        m_project = std::make_shared<vProject>();

        // Add some windows
        std::shared_ptr<vLayer_Dock> newDock = std::make_shared<vLayer_Dock>();
        newDock->OnCreate();
        m_editorLayers.push_back(newDock);

        std::shared_ptr<vLayer_Hierarchy> newHierarchy = std::make_shared<vLayer_Hierarchy>();
        newHierarchy->OnCreate();
        newHierarchy->SetScene(m_project->GetCurrentScene());
        m_editorLayers.push_back(newHierarchy);

        std::shared_ptr<vLayer_Properties> newProperties = std::make_shared<vLayer_Properties>();
        newProperties->OnCreate();
        newProperties->SetHierarchy(newHierarchy);
        m_editorLayers.push_back(newProperties);

        std::shared_ptr<vLayer_FileSystem> newFileSystem = std::make_shared<vLayer_FileSystem>();
        newFileSystem->OnCreate();
        newFileSystem->SetProject(m_project);
        m_editorLayers.push_back(newFileSystem);
    }

    vEditor::~vEditor()
    {

    }

    int vEditor::Run()
    {
        SDL_GLContext gl_context = SDL_GL_CreateContext(m_window.GetWindow());
        SDL_GL_SetSwapInterval(-1);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForSDLRenderer(m_window.GetWindow());
        ImGui_ImplSDLRenderer_Init(m_renderer.GetRenderer());

        /*

        auto testRenderer = m_scene->CreateEntity("SpriteTest");
        auto& sprite = testRenderer.AddComponent<SpriteRenderer>();
        sprite.m_texture = std::make_shared<vTexture>(m_renderer.GetRenderer(), "../images/gearIcon.png");

        auto testRenderer2 = m_scene->CreateEntity("SpriteTest2");
        auto& sprite2 = testRenderer2.AddComponent<SpriteRenderer>();
        sprite2.m_texture = std::make_shared<vTexture>(m_renderer.GetRenderer(), "../images/xjyfdug7f3g81.png");

        */

        // Prepare some performance related values

        SDL_Event event;
        Uint32 frameTime;
        Uint32 frameStart;
        Uint32 frameDelay = 1000 / 60;

        while (!exit)
        {
            frameStart = SDL_GetTicks();
            
            while(SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) exit = true;
                    break;
                case SDL_QUIT:
                    exit = true;
                    break;
                }
            }

            /// Emulate Cycle

            // Start the Dear ImGui frame
            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame(m_window.GetWindow());
            ImGui::NewFrame();

            for (std::shared_ptr<vLayer> layer : m_editorLayers)
            {
                layer->OnUpdate();
                layer->OnDraw();
            }

            

            ImGui::Begin("Scene View");
            int contentX = ImGui::GetContentRegionAvail().x;
            int contentY = ImGui::GetContentRegionAvail().y;
            m_editorBuffer.ChangeTextureSize(contentX, contentY);
            m_renderer.PerformSceneRender(m_project->GetCurrentScene(), &m_editorBuffer);
            ImGui::Image((ImTextureID)m_editorBuffer.GetTexture(), ImGui::GetContentRegionAvail());
            ImGui::End();

            
            
            ImGui::Render();
            SDL_SetRenderDrawColor(m_renderer.GetRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(m_renderer.GetRenderer());
            ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
            
            SDL_RenderPresent(m_renderer.GetRenderer());
            
            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }

        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        
        return 0;
    }
}