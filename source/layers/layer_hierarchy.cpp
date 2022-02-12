#include "layers/layer_hierarchy.h"

namespace vaxe
{
    void DrawRowsBackground(int row_count, float line_height, float x1, float x2, float y_offset, ImU32 col_even, ImU32 col_odd)
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        float y0 = ImGui::GetCursorScreenPos().y + (float)(int)y_offset;

        int row_display_start;
        int row_display_end;
        ImGui::CalcListClipping(row_count, line_height, &row_display_start, &row_display_end);
        for (int row_n = row_display_start; row_n < row_display_end; row_n++)
        {
            ImU32 col = (row_n & 1) ? col_odd : col_even;
            if ((col & IM_COL32_A_MASK) == 0)
                continue;
            float y1 = y0 + (line_height * row_n);
            float y2 = y1 + line_height;
            draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
        }
    }

    int vLayer_Hierarchy::OnCreate()
    {
        return -1;
    }

    int vLayer_Hierarchy::OnUpdate()
    {
        return -1;
    }

    int vLayer_Hierarchy::OnDraw()
    {
        ImGui::Begin("Scene Hierarchy");

        ImGui::Text("Scene: [SCENE HERE]");

        float x1 = ImGui::GetCurrentWindow()->WorkRect.Min.x;
        float x2 = ImGui::GetCurrentWindow()->WorkRect.Max.x;
        float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
        float item_offset_y = -item_spacing_y * 0.5f;
        float line_height = ImGui::GetTextLineHeight() + item_spacing_y;
        DrawRowsBackground(m_scene->registry.size(), line_height, x1, x2, item_offset_y, 0, ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, 0.5f)));

        m_scene->registry.each([&](auto entityID)
        {
            vEntity entity{ entityID , m_scene.get() };
            DrawEntityNode(entity);
        });

        if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            m_selectedEntity = {};

        // Right-click on blank space
        if (ImGui::BeginPopupContextWindow(0, 1, false))
        {
            if (ImGui::MenuItem("Create Empty Entity"))
                m_scene->CreateEntity("Empty Entity");

            ImGui::EndPopup();
        }

        ImGui::End();

        

        
        return 0;
    }

    int vLayer_Hierarchy::OnDestroy()
    {
        return -1;
    }

    void vLayer_Hierarchy::DrawEntityNode(vEntity entity)
    {
        auto& info = entity.GetComponent<EntityInfo>();
		
		ImGuiTreeNodeFlags flags = ((m_selectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = false;

        if (info.isEnabled)
        {
            opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, info.name.c_str());
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255,255,255,120));
		    opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, info.name.c_str());
            ImGui::PopStyleColor();
        }

        
		if (ImGui::IsItemClicked())
		{
            m_selectedEntity = entity;
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, info.name.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_scene->DestroyEntity(entity);
			if (m_selectedEntity == entity)
				m_selectedEntity = {};
		}

        
    }

    
}