#include <Components.hpp>
#include <PhysicsSystem.hpp>

void PhysicsSystem::update(entt::registry& registry, float deltaTime)
{
    auto view = registry.view<PhysicsComponent>();
    for (auto [entity, phys] : view.each())
    {
        phys.x += phys.vx * deltaTime;
        phys.y += phys.vy * deltaTime;
    };
}


