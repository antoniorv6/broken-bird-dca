#include <MainGameState.hpp>
#include <GameOverState.hpp>
#include <StateMachine.hpp>
#include <Components.hpp>
#include <iostream>

MainGameState::MainGameState()
{
    physics_system = PhysicsSystem();
}

MainGameState::~MainGameState()
{
    UnloadTexture(this->birdSprite);
    UnloadTexture(this->pipeSprite);
}

void MainGameState::init()
{

    //Entidad del jugador
    //auto player = registry.create();
    //Añadimos componente de físicas al jugador
    //registry.emplace<PhysicsComponent>(player, 128.0f, 256.0f, 0.0f, 0.0f);
    //registry.emplace<RenderComponent>(player, LoadTexture("assets/yellowbird-downflap.png"), 0,0);

    //Comentario sin sentido
    //this->birdSprite = LoadTexture("assets/yellowbird-downflap.png");
    //this->pipeSprite = LoadTexture("assets/pipe-green.png");
    //this->backgroundSprite = LoadTexture("assets/background-day.png");
//
    //this->player.width = this->birdSprite.width;
    //this->player.height = this->birdSprite.height;
//
    //this->PIPE_W = (float)this->pipeSprite.width;
    //this->PIPE_H = (float)this->pipeSprite.height;
//
    //this->GAP_H = this->player.height * 4.5f;
    //
    //// Asegurar que el gap mínimo permita pasar al pájaro cómodamente
    //if (this->GAP_H < this->player.height * 3.0f) {
    //    this->GAP_H = this->player.height * 3.0f;
    //}
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
    //this->player.vy += GRAVITY * deltaTime;
    //this->player.y += this->player.vy * deltaTime;
//
    //Rectangle player_bbox = {
    //    this->player.x - this->player.width/2, 
    //    this->player.y - this->player.height/2, 
    //    this->player.width, 
    //    this->player.height
    //};
//
    ////Control de spawn de tuberias
    this->spawnTimer += deltaTime;
    if(spawnTimer >= spawnEvery)
    {
        this->spawnTimer = 0.f;
        int window_width = GetScreenWidth();
        int window_height = GetScreenHeight();
        float pipe_y_offset_top = GetRandomValue(PIPE_H/2.f, window_height/2);

        auto pipe = registry.create();
        registry.emplace<PhysicsComponent>(pipe, 
            float(window_width), (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2.f, window_height/2.f), -PIPE_SPEED, 0.f
        );
        registry.emplace<RenderComponent>(pipe, LoadTexture("assets/pipe-green.png"), PIPE_W, PIPE_H);

        //PipePair pipes;
        //pipes.top = {(float)window_width, -pipe_y_offset_top, this->PIPE_W, this->PIPE_H};
        //pipes.bot = {(float)window_width, (PIPE_H - pipe_y_offset_top) + GetRandomValue(PIPE_H/2.f, window_height/2.f), this->PIPE_W, this->PIPE_H};
        //pipes.scored = 0;
        //this->pipes.emplace_back(pipes);
    }

    physics_system.update(registry, deltaTime); 
//
    //for(auto &p : this->pipes)
    //{
    //    p.top.x -= PIPE_SPEED * deltaTime;
    //    p.bot.x -= PIPE_SPEED * deltaTime;
//
    //    if(CheckCollisionRecs(player_bbox, p.top) || CheckCollisionRecs(player_bbox, p.bot))
    //    {
    //        this->state_machine->add_state(std::make_unique<GameOverState>(), true);
    //    }
//
    //    if(!p.scored && p.top.x + PIPE_W < this->player.x && p.bot.x + PIPE_W < this->player.x)
    //    {
    //        this->points+=1;
    //        p.scored = true;
    //    }
    //}
//
    //while(!this->pipes.empty() && (this->pipes.front().top.x + this->pipes.front().top.width < 0.0f))
    //{
    //    this->pipes.pop_front();
    //}

}

void MainGameState::render()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    render_system.update(registry);

    //Rectangle player_bbox = {this->player.x - this->player.radius, this->player.y  - this->player.radius,  this->player.radius*2,  this->player.radius*2};
    //DrawRectanglePro(player_bbox, {0, 0}, 0, PURPLE);
    //DrawTexture(this->backgroundSprite, 0, 0, WHITE);
    //DrawTexture(this->birdSprite, 
    //            (int)(this->player.x - this->player.width/2), 
    //            (int)(this->player.y - this->player.height/2), 
    //            WHITE);
//
    //for(const PipePair& p : this->pipes)
    //{
    //    DrawTextureEx(this->pipeSprite, {p.top.x + PIPE_W, p.top.y + PIPE_H}, 180.f, 1.f, WHITE);
    //    // Tubería inferior - normal
    //    DrawTextureEx(this->pipeSprite, {p.bot.x, p.bot.y}, 0.f, 1.f, WHITE);
    //}
//
    //DrawText(std::to_string(points).c_str(), 30, 30, 24, WHITE);

    EndDrawing();
}