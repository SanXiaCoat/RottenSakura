#pragma once
#include "scene.h"
#include "self.h"
#include <random>

class game;

class selectLevel : public scene
{
public:
    selectLevel();
    ~selectLevel();
    void update(float deltaTime) override;
    void render() override;
    void init() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;
    

    void keyboardControl();
    void renderBackground();
    void renderSelections();

    

private:
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

    SDL_Texture* title;
    SDL_Texture* background;
    SDL_Texture* selection1;
    SDL_Texture* selection2;
    SDL_Texture* selection3;
    SDL_Texture* selection4;
    SDL_Texture* selection5;
    SDL_Texture* selection6;
    SDL_Texture* selection7;
    SDL_Texture* selection8;
    SDL_Texture* selection9;
    SDL_Texture* selection10;
    SDL_Texture* selection11;

    //实例与玩家
    game &game;
    Player player;

    //字体
    TTF_Font* statusFont;

    int selection = 1;
    bool keyDown = false;
    bool keyUp = false;
    bool keyZ = false;  
};