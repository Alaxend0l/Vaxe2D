#include "entity/vEntity.h"

namespace vaxe
{
    vEntity::vEntity(entt::entity handle, vScene* _scene) : entityHandle(handle), scene(_scene) {}
}