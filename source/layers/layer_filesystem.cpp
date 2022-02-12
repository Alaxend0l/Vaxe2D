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

        ImGui::End();
        return 0;
    }

    int vLayer_FileSystem::OnDestroy()
    {
        return -1;
    }
}
