#pragma once
#include <GameState.hpp>
extern "C" {
    #include <raylib.h>
}
#include <deque>

struct Bird {
    float x = 200.0f;
    float y = 200.0f;
    float vy = 0.0f;
    float radius = 12.0f;
};

struct Rect {float x,y,w,h; };
struct PipePair {Rect top, bot;};

class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState() = default;

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Bird player;
        const float GRAVITY = 900.f;
        const float FLAP_VY = -300.f;
        const float GAP_H = 140.f, PIPE_W = 70.f;
        const float PIPE_SPEED = 180.f;
        float spawnTimer = 0.f, spawnEvery = 1.8f; 
        std::deque<PipePair> pipes;
};