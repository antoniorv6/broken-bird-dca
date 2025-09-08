#include <MainGameState.hpp>
#include <GameOverState.hpp>
#include <StateMachine.hpp>
#include <iostream>

MainGameState::MainGameState()
{
}

void MainGameState::init()
{
}

void MainGameState::handleInput()
{
    if(IsKeyPressed(KEY_SPACE))
    {
        this->player.vy = FLAP_VY;
    }
}

void MainGameState::update(float deltaTime)
{
    this->player.vy += GRAVITY * deltaTime;
    this->player.y += this->player.vy * deltaTime;

    Rectangle player_bbox = {this->player.x - 17.f / 2.f, this->player.y - 17.f / 2, 17.f, 17.f};

    //Control de spawn de tuberias
    this->spawnTimer += deltaTime;
    if(spawnTimer >= spawnEvery)
    {
        this->spawnTimer = 0.f;
        float gapY = 120.f + (float)GetRandomValue(0,210);
        PipePair pipes;
        pipes.top = {450.f, 0.f, PIPE_W, gapY - GAP_H / 2.f};
        pipes.bot = {450.f, gapY + GAP_H/2.f, PIPE_W, 640.f - (gapY - GAP_H / 2.f)};
        this->pipes.emplace_back(pipes);
    }

    for(auto &p : this->pipes)
    {
        p.top.x -= PIPE_SPEED * deltaTime;
        p.bot.x -= PIPE_SPEED * deltaTime;
        Rectangle top_rectangle = {p.top.x, p.top.y, p.top.w, p.top.h};
        Rectangle bottom_rectangle = {p.bot.x, p.bot.y, p.bot.w, p.bot.h};

        if(CheckCollisionRecs(player_bbox, top_rectangle) || CheckCollisionRecs(player_bbox, bottom_rectangle))
        {
            this->state_machine->add_state(std::make_unique<GameOverState>(), true);
        }
    }

    while(!this->pipes.empty() && (this->pipes.front().top.x + this->pipes.front().top.w < 0.0f))
    {
        this->pipes.pop_front();
    }

}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    DrawCircle((int)this->player.x, (int)this->player.y, this->player.radius, RED);

    for(PipePair p : this->pipes)
    {
        DrawRectangle((int)p.top.x, (int)p.top.y, (int)p.top.w, (int)p.top.h, GREEN);
        DrawRectangle((int)p.bot.x, (int)p.bot.y, (int)p.bot.w, (int)p.bot.h, GREEN);
    }

    EndDrawing();
}