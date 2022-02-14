#pragma once

#include "layers/vLayer.h"

namespace vaxe
{
    class vLayer_Dock : public vLayer
    {
    public:
        int OnCreate()  override;
        int OnUpdate()  override;
        int OnDraw()    override;
        int OnDestroy() override;
    private:
        bool showDemo;
    };
}