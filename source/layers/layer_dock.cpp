#include "layers/layer_dock.h"

namespace vaxe
{
    int vLayer_Dock::OnCreate()
    {
        m_dockNodeFlags = ImGuiDockNodeFlags_None;
        m_windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        
        
        m_windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        return 0;
    }

    int vLayer_Dock::OnUpdate()
    {
        return 0;
    }

    int vLayer_Dock::OnDraw()
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::Begin("Vaxe2D Dockspace", &m_open, m_windowFlags);
        //ImGui::PopStyleVar(2);
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_dockNodeFlags);
        if (ImGui::BeginMenuBar())
        {
            ImGui::MenuItem("TEST");
            ImGui::EndMenuBar();
        }

        ImGui::End();
        return 0;
    }

    int vLayer_Dock::OnDestroy()
    {
        return 0;
    }
}