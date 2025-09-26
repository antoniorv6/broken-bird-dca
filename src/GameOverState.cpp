#include <GameOverState.hpp>
#include <MainGameState.hpp>
#include <iostream>

GameOverState::GameOverState()
{
}

void GameOverState::init()
{
}

void GameOverState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE))
    {
        this->states_machine.add_state(std::make_unique<MainGameState>())
    }
}

void GameOverState::update(float deltaTime)
{
   

}

void GameOverState::render()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawText("GAME OVER", (GetScreenWidth()/2) - 24, GetScreenHeight()/2, 24, BLACK);
    EndDrawing();
}