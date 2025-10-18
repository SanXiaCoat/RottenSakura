#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "configs.h"
#include "enermy.h"
#include <list>

struct self_bullet
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    int width = selfBulletSize;
    int height = selfBulletSize;
    int speed = selfBulletSpeed;
    int speedX = 0;
    float damage = 1.0f;
};

struct Player
{
    SDL_Texture* texture1 = nullptr;
    SDL_Texture* texture2 = nullptr;
    SDL_Texture* texture3 = nullptr;
    SDL_Texture* combatTexture1 = nullptr;
    SDL_Texture* combatTexture2 = nullptr;
    SDL_Texture* combatTexture3 = nullptr;
    SDL_Texture* combatTexture4 = nullptr;
    SDL_Texture* selfpointTexture = nullptr;
    SDL_Texture* skill2Texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f}; 
    int width = selfSize;
    int height = selfSize;
    float speed = playerSpeed;
    float sneakSpeed = playerSneakSpeed;
    Uint32 FireCooldown = selfFireCooldown;
    Uint32 lastShootTime = 0;
    Uint32 z_signStartTime = 0;
    Uint32 space_signStartTime = 0;
    Uint32 x_signStartTime = 0;
    bool renderSkill2Needed = 0;
    bool renderCombatNeeded = 0;
    float lives = 20.0f;
    bool isDead = false;
    float power = 0.0f;
    float powerMax = 100.0f;
    float level = 0.0f;
    float levelMax = 100.0f;
    float recoverSpeed = 0.02f;

    void skill1(std::list<std::variant<enemy1_bullet*, enemy2_bullet*>> &enemyBullets);//被动技能
    void skill2(std::list<std::variant<enemy1_bullet*, enemy2_bullet*>> &enemyBullets,std::list<std::variant<enemy1*, enemy2*, enemy3*>>& enemies);//主动技能
    void skill2Render();
    void skill3(std::list<std::variant<enemy1_bullet*, enemy2_bullet*>> &enemyBullets,std::list<self_bullet *> &selfBullets);//决战技能

    Uint32 meleeCooldown = 500;  // 近战冷却时间(ms)
    Uint32 lastMeleeTime = 0;    // 上次近战时间
    float meleeRadius = 64.0f;   // 近战攻击半径
    float meleeDamage = 4.0f;    // 近战伤害值

    void combat(std::list<std::variant<enemy1*, enemy2*, enemy3*>>& enemies);
    void combatRender();
};

