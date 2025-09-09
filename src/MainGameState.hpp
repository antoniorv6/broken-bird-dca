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
    float width, height;
};

struct PipePair {Rectangle top, bot; uint8_t scored;};

class MainGameState : public GameState
{
    public:
        MainGameState();
        ~MainGameState();

        void init() override;
        void handleInput() override;
        void update(float deltaTime) override;
        void render() override;

        void pause(){};
        void resume(){};

    
    private:
        char entered_key;
        Bird player;
        float GRAVITY = 900.f;
        float FLAP_VY = -300.f;
        float GAP_H = 140.f, PIPE_W = 70.f;
        float PIPE_SPEED = 180.f;
        float spawnTimer = 0.f, spawnEvery = 1.8f; 
        std::deque<PipePair> pipes;
        uint8_t points = 0;

        Texture2D birdSprite;
        Texture2D pipeSprite;
};