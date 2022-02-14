#pragma once

#include "layers/vLayer.h"

#include "filesystem/vProject.h"

namespace vaxe
{
    class vLayer_FileSystem : public vLayer
    {
    public:
        int OnCreate()  override;
        int OnUpdate()  override;
        int OnDraw()    override;
        int OnDestroy() override;
        void SetProject(const std::shared_ptr<vProject>& project) { m_project = project; }

    private:

        void ShowFileMenu();
        std::shared_ptr<vProject> m_project;

        std::string m_filesystem_createfolder_name;
    };
}