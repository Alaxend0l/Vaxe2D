#include "layers/layer_filesystem.h"

#include "ImGuiFileDialog.h"

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
        ImVec2 button_sz = {100, 50};
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

        /// Right Click Context Menu
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Import File..."))
            {
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");
            }

            ImGui::Separator();

            if (ImGui::BeginMenu("Create Folder"))
            {
                ImGui::InputText("Name##CreateFolderPopup", &m_filesystem_createfolder_name);
                if (ImGui::Button("Create Folder##CreateFolderPopup"))
                {
                    m_project->CreateSubDirectoryInCurrentDirectory(m_filesystem_createfolder_name);
                    m_project->SaveProject();
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndMenu();
            }
            ImGui::EndPopup();
        }

        ShowFileMenu();

        ImGui::End();
        return 0;
    }

    int vLayer_FileSystem::OnDestroy()
    {
        return -1;
    }

    void vLayer_FileSystem::ShowFileMenu()
    {
        if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) 
        {
            // action if OK
            if (ImGuiFileDialog::Instance()->IsOk())
            {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
            // action
            }
            
            // close
            ImGuiFileDialog::Instance()->Close();
        }
    }
}
