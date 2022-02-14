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

        if (showDemo)
        {
            ImGui::ShowDemoWindow();
        }

        ImGui::Begin("Vaxe2D Dockspace", &m_open, m_windowFlags);
        //ImGui::PopStyleVar(2);
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_dockNodeFlags);
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                
                if (ImGui::MenuItem("New")) {}
                if (ImGui::MenuItem("Open", "Ctrl+O")) {}
                if (ImGui::BeginMenu("Open Recent"))
                {
                    ImGui::MenuItem("fish_hat.c");
                    ImGui::MenuItem("fish_hat.inl");
                    ImGui::MenuItem("fish_hat.h");
                    if (ImGui::BeginMenu("More.."))
                    {
                        ImGui::MenuItem("Hello");
                        ImGui::MenuItem("Sailor");
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenu();
                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {}
                if (ImGui::MenuItem("Save As..")) {}

                ImGui::Separator();
                if (ImGui::BeginMenu("Options"))
                {
                    static bool enabled = true;
                    ImGui::MenuItem("Enabled", "", &enabled);
                    ImGui::BeginChild("child", ImVec2(0, 60), true);
                    for (int i = 0; i < 10; i++)
                        ImGui::Text("Scrolling Text %d", i);
                    ImGui::EndChild();
                    static float f = 0.5f;
                    static int n = 0;
                    ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
                    ImGui::InputFloat("Input", &f, 0.1f);
                    ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Colors"))
                {
                    float sz = ImGui::GetTextLineHeight();
                    for (int i = 0; i < ImGuiCol_COUNT; i++)
                    {
                        const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
                        ImVec2 p = ImGui::GetCursorScreenPos();
                        ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
                        ImGui::Dummy(ImVec2(sz, sz));
                        ImGui::SameLine();
                        ImGui::MenuItem(name);
                    }
                    ImGui::EndMenu();
                }

                // Here we demonstrate appending again to the "Options" menu (which we already created above)
                // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
                // In a real code-base using it would make senses to use this feature from very different code locations.
                if (ImGui::BeginMenu("Options")) // <-- Append!
                {
                    static bool b = true;
                    ImGui::Checkbox("SomeOption", &b);
                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Disabled", false)) // Disabled
                {
                    IM_ASSERT(0);
                }
                if (ImGui::MenuItem("Checked", NULL, true)) {}
                if (ImGui::MenuItem("Quit", "Alt+F4")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("About"))
            {
                ImGui::MenuItem("Show Demo", "", &showDemo);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::End();
        return 0;
    }

    int vLayer_Dock::OnDestroy()
    {
        return 0;
    }
}