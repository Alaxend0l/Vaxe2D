#pragma once

#include "layers/vLayer.h"
#include "entity/vScene.h"
#include "entity/vEntity.h"
#include "entity/vComponent.h"

namespace vaxe
{
    class vLayer_Hierarchy : public vLayer
    {
    public:
        int OnCreate()  override;
        int OnUpdate()  override;
        int OnDraw()    override;
        int OnDestroy() override;
        void SetScene(const std::shared_ptr<vScene>& scene) { m_scene = scene; }
    private:
        void DrawEntityNode(vEntity entity);
        std::shared_ptr<vScene> m_scene;
        vEntity m_selectedEntity;

        friend class vLayer_Properties;
    };
}