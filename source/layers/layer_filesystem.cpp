#include "layers/layer_filesystem.h"

namespace vaxe
{
    int vLayer_FileSystem::OnCreate()
    {
        return -1;
    }

    int vLayer_FileSystem::OnUpdate()
    {
        return -1;
    }

    int vLayer_FileSystem::OnDraw()
    {
        ImGui::Begin("File System");
        ImVec2 button_sz = {50, 50};
        ImGuiStyle& style = ImGui::GetStyle();
        float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;

        int directoryAmount = m_project->GetCurrentDirectory()->GetFolderAmount();
        int fileAmount = m_project->GetCurrentDirectory()->GetFileAmount();

        if (!m_project->CurrentDirectoryIsRoot())
        {
            ImGui::PushID(0xFFFFFFF);
            if (ImGui::Button("...", button_sz))
            {
                m_project->GoUpDirectory();
                ImGui::PopID();
            }
            else
            {
                ImGui::SameLine();
                ImGui::PopID();
            }
            
        }

        for (int n = 0; n < directoryAmount; n++)
        {
            ImGui::PushID(n);
            if (ImGui::Button(m_project->GetCurrentDirectory()->GetDirectoryAtIndex(n)->GetName().c_str(), button_sz))
            {
                m_project->SetNewDirectory(m_project->GetCurrentDirectory()->GetDirectoryAtIndex(n));
                ImGui::PopID();
                break;
            }
            float last_button_x2 = ImGui::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
            if (n + 1 < directoryAmount && next_button_x2 < window_visible_x2)
                ImGui::SameLine();
            ImGui::PopID();
        }

        ImGui::End();
        return 0;
    }

    int vLayer_FileSystem::OnDestroy()
    {
        return -1;
    }
}
