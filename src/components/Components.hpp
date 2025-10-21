#include <cstdint>
#include <raylib.h>

struct InputComponent
{
    uint8_t flap;
};

struct PlayerComponent
{
    uint8_t dead = 0;
};

//Primer componente de físicas
struct PhysicsComponent 
{
    float x;
    float y;
    float vx;
    float vy;
};

struct RenderComponent
{
    Texture2D texture;
    float width;
    float height;
};