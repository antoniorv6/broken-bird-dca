#include <MainGameState.hpp>
#include <GameOverState.hpp>
#include <StateMachine.hpp>
#include <iostream>

MainGameState::MainGameState()
{
}

MainGameState::~MainGameState()
{
    UnloadTexture(this->birdSprite);
    UnloadTexture(this->pipeSprite);
}

void MainGameState::init()
{
    this->birdSprite = LoadTexture("assets/yellowbird-downflap.png");
    this->pipeSprite = LoadTexture("assets/pipe-green.png");

    this->player.width = this->birdSprite.width;
    this->player.height = this->birdSprite.height;
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

    Rectangle player_bbox = {this->player.x - this->player.width, this->player.y  - this->player.height,  this->player.width,  this->player.height};

    //Control de spawn de tuberias
    this->spawnTimer += deltaTime;
    if(spawnTimer >= spawnEvery)
    {
        this->spawnTimer = 0.f;
        float gapY = 120.f + (float)GetRandomValue(0,210);
        PipePair pipes;
        pipes.top = {450.f, 0.f, PIPE_W, gapY - GAP_H / 2.f};
        pipes.bot = {450.f, gapY + GAP_H/2.f, PIPE_W, 640.f - (gapY - GAP_H / 2.f)};
        pipes.scored = 0;
        this->pipes.emplace_back(pipes);
    }

    for(auto &p : this->pipes)
    {
        p.top.x -= PIPE_SPEED * deltaTime;
        p.bot.x -= PIPE_SPEED * deltaTime;

        if(CheckCollisionRecs(player_bbox, p.top) || CheckCollisionRecs(player_bbox, p.bot))
        {
            this->state_machine->add_state(std::make_unique<GameOverState>(), true);
        }

        if(!p.scored && p.top.x + PIPE_W < this->player.x && p.bot.x + PIPE_W < this->player.x)
        {
            this->points+=1;
            p.scored = true;
        }
    }

    while(!this->pipes.empty() && (this->pipes.front().top.x + this->pipes.front().top.width < 0.0f))
    {
        this->pipes.pop_front();
    }

}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    //Rectangle player_bbox = {this->player.x - this->player.radius, this->player.y  - this->player.radius,  this->player.radius*2,  this->player.radius*2};
    //DrawRectanglePro(player_bbox, {0, 0}, 0, PURPLE);
    DrawTexture(this->birdSprite, 
                (int)(this->player.x - this->player.width/2), 
                (int)(this->player.y - this->player.height/2), 
                WHITE);

    for(PipePair p : this->pipes)
    {
        DrawRectangle((int)p.top.x, (int)p.top.y, (int)p.top.width, (int)p.top.height, GREEN);
        DrawRectangle((int)p.bot.x, (int)p.bot.y, (int)p.bot.width, (int)p.bot.height, GREEN);
    }

    DrawText(std::to_string(points).c_str(), 30, 30, 24, WHITE);

    EndDrawing();
}