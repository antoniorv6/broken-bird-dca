#include <GameOverState.hpp>
#include <iostream>

GameOverState::GameOverState()
{
}

void GameOverState::init()
{
}

void GameOverState::handleInput()
{
   
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