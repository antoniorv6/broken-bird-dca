#include <cstdint>
#include <raylib.h>

struct PlayerComponent
{
    uint8_t dead = 0;
    uint8_t flap = 0;
};

//Primer componente de físicas
struct PhysicsComponent 
{
    float x;
    float y;
    float vx;
    float vy;
    uint8_t hasGravity;
};

struct RenderComponent
{
    Texture2D texture;
    float width;
    float height;
    float rotation;
};