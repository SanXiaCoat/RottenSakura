#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "configs.h"

struct enemy1
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = enemy1Speed;
    Uint32 FireCooldown = 800;
    Uint32 lastShootTime = 0;
    float health = 8.0f;
    int score = 1;
};

struct enemy2
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = 20;
    Uint32 FireCooldown = 1000;
    Uint32 lastShootTime = 0;
    float health = 10.0f;
    int score = 2;
};

struct enemy3
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* texture4 = nullptr;
    SDL_Texture* texture5 = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = enemySize;
    int height = enemySize;
    int speed = 20;
    Uint32 FireCooldown = 10000;
    Uint32 lastShootTime = 0;
    float health = 20.0f;
    int score = 2;
    bool isShooting = false;         // 是否正在发射
};

struct enemy1_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureFrozen = nullptr;
    SDL_Texture* textureSlowed = nullptr;
    SDL_Texture* textureAlt = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0.0f, 1.0f};
    int width = enemy1BulletSize;
    int height = enemy1BulletSize;
    int speed = enemy1BulletSpeed;
    int damage = 1;
    bool hasBeenSlowed = false;
    bool hasBeenSlowedBySkill2 = false;
};

struct enemy2_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_Texture* textureFrozen = nullptr;
    SDL_Texture* textureSlowed = nullptr;
    SDL_Texture* textureAlt = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    SDL_FPoint direction = {0.0f, 1.0f};
    int width = 12;
    int height = 12;
    int speed = 40;
    int damage = 1;
    bool hasBeenSlowed = false;
    bool hasBeenSlowedBySkill2 = false;
};

struct enemy3_laser
{
    SDL_Texture* inactivationTexture = nullptr;   // 激光纹理
    SDL_Texture* activationTexture = nullptr;    // 激光纹理
    SDL_FPoint startPosition;         // 激光起始位置
    SDL_FPoint endPosition;           // 激光结束位置
    int width = 8;                        // 激光宽度
    float damage = 5.0f;                     
    Uint32 startTime;                 // 发射开始时间
    Uint32 alarmTime = 3000;           // 警告时间
    Uint32 duration = 2000;           // 持续时间
    bool isActive = false;                    // 是否激活
};