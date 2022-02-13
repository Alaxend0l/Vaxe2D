#pragma once

#include "layers/layer_hierarchy.h"

namespace vaxe
{
    class vLayer_Properties : public vLayer
    {
    public:
        int OnCreate()  override;
        int OnUpdate()  override;
        int OnDraw()    override;
        int OnDestroy() override;
        void SetHierarchy(const std::shared_ptr<vLayer_Hierarchy>& hierarchy) { m_hierarchy = hierarchy; }

    private:
        std::shared_ptr<vLayer_Hierarchy> m_hierarchy;

    };
}