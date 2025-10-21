#include <RenderSystem.hpp>
#include <Components.hpp>
#include <raylib.h>
#include <iostream>

void RenderSystem::update(entt::registry& registry)
{
    auto view = registry.view<const RenderComponent, const PhysicsComponent>();
    for (auto [entity, rend, phys] : view.each())
    {
        DrawTextureEx(rend.texture, {(float)phys.x, (float)phys.y}, 0.f, 1.f, WHITE);
    };
}