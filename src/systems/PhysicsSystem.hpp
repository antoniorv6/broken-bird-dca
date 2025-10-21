#pragma once
#include <entt/entt.hpp>

class PhysicsSystem
{
    public:
        PhysicsSystem(){};
        ~PhysicsSystem(){};
        void update(entt::registry& registry, float deltaTime);
};
