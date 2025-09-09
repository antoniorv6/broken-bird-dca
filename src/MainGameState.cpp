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
    this->backgroundSprite = LoadTexture("assets/background-day.png");

    this->player.width = this->birdSprite.width;
    this->player.height = this->birdSprite.height;

    this->PIPE_W = (float)this->pipeSprite.width;
    this->PIPE_H = (float)this->pipeSprite.height;

    this->GAP_H = this->player.height * 4.5f;
    
    // Asegurar que el gap mínimo permita pasar al pájaro cómodamente
    if (this->GAP_H < this->player.height * 3.0f) {
        this->GAP_H = this->player.height * 3.0f;
    }
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

    Rectangle player_bbox = {
        this->player.x - this->player.width/2, 
        this->player.y - this->player.height/2, 
        this->player.width, 
        this->player.height
    };

    //Control de spawn de tuberias
    this->spawnTimer += deltaTime;
    if(spawnTimer >= spawnEvery)
    {
        this->spawnTimer = 0.f;
        float minGapY = this->GAP_H/2 + 50.f; // Margen superior
        float maxGapY = 512.f - this->GAP_H/2 - 50.f; // Margen inferior (ajusta 640 a tu altura de pantalla)
        
        float gapY = minGapY + (float)GetRandomValue(0, (int)(maxGapY - minGapY));
        
        PipePair pipes;
        pipes.top = {450.f, 0.f, this->PIPE_W, gapY - this->GAP_H/2.f};
        pipes.bot = {450.f, gapY + this->GAP_H/2.f, this->PIPE_W, 512.f - (gapY + this->GAP_H/2.f)};
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
    DrawTexture(this->backgroundSprite, 0, 0, WHITE);
    DrawTexture(this->birdSprite, 
                (int)(this->player.x - this->player.width/2), 
                (int)(this->player.y - this->player.height/2), 
                WHITE);

    for(const PipePair& p : this->pipes)
    {
        Rectangle sourceRec = {0, 0, (float)this->pipeSprite.width, (float)this->pipeSprite.height};
        Rectangle destRecTop = {
            p.top.x + p.top.width/2,     // Centro X
            p.top.y + p.top.height,      // Parte inferior del rectángulo
            p.top.width, 
            p.top.height
        };
        Vector2 origin = {p.top.width/2, 0}; // Origen en el centro-abajo
        DrawTexturePro(this->pipeSprite, sourceRec, destRecTop, origin, 180.0f, WHITE);
        
        // Tubería inferior (normal)
        Rectangle destRecBot = {p.bot.x, p.bot.y, p.bot.width, p.bot.height};
        Vector2 originBot = {0, 0};
        DrawTexturePro(this->pipeSprite, sourceRec, destRecBot, originBot, 0.0f, WHITE);
    }

    DrawText(std::to_string(points).c_str(), 30, 30, 24, WHITE);

    EndDrawing();
}