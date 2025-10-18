#include "BattleField.h"
#include "game.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <list>
#include <random>
#include <iomanip>
#include <sstream> 
#include "menu.h"

BattleField::BattleField() : game(game::getInstance())
{
    
}

BattleField::~BattleField()
{
    
}

void BattleField::init()
{
    //随机数种子
    std::random_device rd;
    gen = std::mt19937(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    startTime = SDL_GetTicks();
    srand((unsigned int)time(NULL));
    
    //载入字体
    statusFont = TTF_OpenFont("../assets/fonts/adfyh.ttf", 24);

    //载入图片
    player.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self1.png");
    player.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self2.png");
    player.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/self3.png");
    player.selfpointTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/selfpoint.png");
    backgroundTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/BattleFieldBackground.png");
    titleTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/title.png");
    healthBarTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/healthBar.png");
    player.combatTexture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/1.png");
    player.combatTexture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/2.png");
    player.combatTexture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/3.png");
    player.combatTexture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/combatParticle/4.png");
    player.skill2Texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/self/skill2.png");

    // 初始化模板
    enemy1BulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet.png");
    enemy1BulletTemplate.textureFrozen = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet_freezed.png");
    enemy1BulletTemplate.textureSlowed = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet_slowed.png");
    enemy1BulletTemplate.textureAlt = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy1/bullet_alt.png");

    enemy2BulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet.png");
    enemy2BulletTemplate.textureFrozen = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_freezed.png");
    enemy2BulletTemplate.textureSlowed = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_slowed.png");
    enemy2BulletTemplate.textureAlt = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy2/bullet_alt.png");

    enemy3LaserTemplate.inactivationTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy3/inactive.png");
    enemy3LaserTemplate.activationTexture = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemyBullet/monster/enemy3/active.png");

    enemyTemplate.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemyTemplate.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemyTemplate.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemyTemplate.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemyTemplate.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    enemy2Template.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemy2Template.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemy2Template.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemy2Template.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemy2Template.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    enemy3Template.texture1 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/1.png");
    enemy3Template.texture2 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/2.png");
    enemy3Template.texture3 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/3.png");
    enemy3Template.texture4 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/4.png");
    enemy3Template.texture5 = IMG_LoadTexture(game.getRenderer(), "../assets/images/enemy1/5.png");

    selfBulletTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/bullet.png");

    powerTemplate.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/power.png");

    bgTemplate1.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/battleBackground/suburbBG1.png");
    
    bgTemplate2.texture = IMG_LoadTexture(game.getRenderer(), "../assets/images/battleBackground/suburbBG2.png");

    if (statusFont != nullptr) 
    {
        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Surface* textSurfacePaused1 = TTF_RenderUTF8_Solid(statusFont, "PAUSED", textColor);
        SDL_Surface* textSurfacePaused2 = TTF_RenderUTF8_Solid(statusFont, "按 [ESC] 继续", textColor);
        SDL_Surface* textSurfacePaused3 = TTF_RenderUTF8_Solid(statusFont, "按 [Q] 退出]", textColor);
        SDL_Surface* textSurfaceDeath1 = TTF_RenderUTF8_Solid(statusFont, "满身疮痍 ! ", textColor);
        SDL_Surface* textSurfaceDeath2 = TTF_RenderUTF8_Solid(statusFont, "按 [Q] 退出", textColor);
        if (textSurfacePaused1 != nullptr) 
        {
            pauseTextTexture1 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfacePaused1);
            SDL_FreeSurface(textSurfacePaused1);
        }
        if (textSurfacePaused2 != nullptr) 
        {
            pauseTextTexture2 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfacePaused2);
            SDL_FreeSurface(textSurfacePaused2);
        }
        if (textSurfacePaused3 != nullptr) 
        {
            pauseTextTexture3 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfacePaused3);
            SDL_FreeSurface(textSurfacePaused3);
        }
        if (textSurfaceDeath1 != nullptr)
        {
            deathTextTexture1 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceDeath1);
            SDL_FreeSurface(textSurfaceDeath1);
        }
        if (textSurfaceDeath2 != nullptr)
        {
            deathTextTexture2 = SDL_CreateTextureFromSurface(game.getRenderer(), textSurfaceDeath2);
            SDL_FreeSurface(textSurfaceDeath2);
        }
    }

    //初始化自机位置
    player.position.x = (fieldW - player.width) / 2.0;
    player.position.y = fieldH - player.height;

}

void BattleField::update(float deltaTime)
{
    if (isPaused) 
    {
        return;
    }
    keyboardControl(deltaTime);
    playerBulletsUpdate(deltaTime);
    powerManage();
    spawnEnemy();
    updateEnemies1(deltaTime);
    updateEnemy1Bullets(deltaTime);
    updateEnemy1Lasers(deltaTime);
    updatePlayer(deltaTime);
    updatePowers(deltaTime);
    updateBattleBackground(deltaTime);
    player.skill1(enemy1Bullets);
}

void BattleField::render()
{   
    //渲染窗口背景
    SDL_RenderCopy(game.getRenderer(), backgroundTexture, NULL, NULL);

    //渲染战斗背景（黑色框）
    SDL_Rect fieldRect = { 0, 0, fieldW, fieldH };
    SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
    SDL_RenderFillRect(game.getRenderer(), &fieldRect);

    //渲染滚动背景
    rollingBackgroundRender();

    //渲染自机子弹
    playerBulletsRender();

    //渲染敌机1子弹
    enemy1BulletsRender();

    //渲染敌机1激光
    enemy1LasersRender();

    //渲染p点
    renderPowers();

    if (!player.isDead)
    {
        if (player.renderSkill2Needed)
        {
            player.skill2Render();
        }

        //渲染自机
        SDL_Rect playerRect = 
        {
            static_cast<int>(player.position.x),
            static_cast<int>(player.position.y),
            static_cast<int>(player.width),
            static_cast<int>(player.height)
        };
        int currentFrame = (SDL_GetTicks() - startTime) / 500;
        if (currentFrame % 3 == 0)
        {
            SDL_RenderCopy(game.getRenderer(), player.texture1, NULL, &playerRect);
        }
        else if (currentFrame % 3 == 1)
        {
            SDL_RenderCopy(game.getRenderer(), player.texture2, NULL, &playerRect);
        }
        else
        {
            SDL_RenderCopy(game.getRenderer(), player.texture3, NULL, &playerRect);
        }
        
        SDL_Rect selfpoint = 
        {
            static_cast<int>(player.position.x + 16),
            static_cast<int>(player.position.y + 16),
            16,
            16
        };
        SDL_RenderCopy(game.getRenderer(), player.selfpointTexture, NULL, &selfpoint);
    }
    
    //渲染敌机
    renderEnemies1();

    //渲染右侧状态栏
    statusRender();

    if (player.renderCombatNeeded)
    {
        player.combatRender();
    }

    if (isPaused) 
    {
        SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
        // 半透明黑色覆盖层
        SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 64);
        SDL_RenderFillRect(game.getRenderer(), &fieldRect);

        // 渲染暂停文字
        if (pauseTextTexture1 != nullptr && pauseTextTexture2 != nullptr && pauseTextTexture3 != nullptr) 
        {
            int textW1, textH1;
            SDL_QueryTexture(pauseTextTexture1, NULL, NULL, &textW1, &textH1);

            int textW2, textH2;
            SDL_QueryTexture(pauseTextTexture2, NULL, NULL, &textW2, &textH2);

            int textW3, textH3;
            SDL_QueryTexture(pauseTextTexture3, NULL, NULL, &textW3, &textH3);

            SDL_Rect renderRect1 = {
                (fieldW - textW1) / 2,
                (fieldH - textH1) / 2 - textH1 - 10,
                textW1,
                textH1
            };
            SDL_Rect renderRect2 = {
                (fieldW - textW2) / 2,
                (fieldH - textH2) / 2,
                textW2,
                textH2
            };
            SDL_Rect renderRect3 = {
                (fieldW - textW3) / 2,
                (fieldH - textH3) / 2 + textH3 + 10,
                textW3,
                textH3
            };
            SDL_RenderCopy(game.getRenderer(), pauseTextTexture1, NULL, &renderRect1);
            SDL_RenderCopy(game.getRenderer(), pauseTextTexture2, NULL, &renderRect2);
            SDL_RenderCopy(game.getRenderer(), pauseTextTexture3, NULL, &renderRect3);
        }
    }

    if (player.isDead)
    {
        SDL_SetRenderDrawBlendMode(game.getRenderer(), SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 64);
        SDL_RenderFillRect(game.getRenderer(), &fieldRect);

        // 渲染死亡文字
        if (deathTextTexture1 != nullptr && deathTextTexture2 != nullptr) 
        {
            int textW1, textH1;
            SDL_QueryTexture(deathTextTexture1, NULL, NULL, &textW1, &textH1);

            int textW2, textH2;
            SDL_QueryTexture(deathTextTexture2, NULL, NULL, &textW2, &textH2);

            SDL_Rect renderRect1 = {
                (fieldW - textW1) / 2,
                (fieldH - textH1) / 2 - 10,
                textW1,
                textH1
            };

            SDL_Rect renderRect2 = {
                (fieldW - textW2) / 2,
                (fieldH - textH2) / 2 + textH2 + 10,
                textW2,
                textH2
            };
            
            SDL_RenderCopy(game.getRenderer(), deathTextTexture1, NULL, &renderRect1);
            SDL_RenderCopy(game.getRenderer(), deathTextTexture2, NULL, &renderRect2);
        }
    
        
    }
    
}

void BattleField::clean()
{
    //清理子弹容器
    for (auto &projectile  : playerBullets)
    {
        if (projectile != nullptr)
        {
            delete projectile;
        }
    }
    playerBullets.clear();

    //清理敌机1容器
    for (auto &enemy : enemies)
    {
        std::visit([](auto&& enemy) {
            if (enemy != nullptr)
            {
                delete enemy;
            }
        }, enemy);
    }
    enemies.clear();

    //清理敌机1子弹容器
    for (auto &bullet : enemy1Bullets)
    {
        std::visit([](auto&& bullet) {
            if (bullet != nullptr)
            {
                delete bullet;
            } 
        },bullet);
    }
    enemy1Bullets.clear();

    //清理激光容器
    for (auto &laser : enemyLasers)
    {
        if (laser != nullptr)
        {
            delete laser;
        }
    }
    enemyLasers.clear();

    //清理p点容器
    for (auto &power : powers)
    {
        if (power != nullptr)
        {
            delete power;
        }
    }
    powers.clear();

    //清理背景容器
    for (auto &bg : battleBackgrounds)
    {
        if (bg != nullptr)
        {
            delete bg;
        }
    }

    //清理自机
    if (player.texture1 != nullptr)
    {
        SDL_DestroyTexture(player.texture1);
    }

    if (player.texture2 != nullptr)
    {
        SDL_DestroyTexture(player.texture2);
    }

    if (player.texture3 != nullptr)
    {
        SDL_DestroyTexture(player.texture3);
    }

    //清理模板
    if (selfBulletTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(selfBulletTemplate.texture);
    }

    if (enemyTemplate.texture1 != nullptr || enemyTemplate.texture2 != nullptr || enemyTemplate.texture3 != nullptr || enemyTemplate.texture4 != nullptr || enemyTemplate.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemyTemplate.texture1);
        SDL_DestroyTexture(enemyTemplate.texture2);
        SDL_DestroyTexture(enemyTemplate.texture3);
        SDL_DestroyTexture(enemyTemplate.texture4);
        SDL_DestroyTexture(enemyTemplate.texture5);
    }

    if (enemy2Template.texture1 != nullptr || enemy2Template.texture2 != nullptr || enemy2Template.texture3 != nullptr || enemy2Template.texture4 != nullptr || enemy2Template.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemy2Template.texture1);
        SDL_DestroyTexture(enemy2Template.texture2);
        SDL_DestroyTexture(enemy2Template.texture3);
        SDL_DestroyTexture(enemy2Template.texture4);
        SDL_DestroyTexture(enemy2Template.texture5);
    }

    if (enemy3Template.texture1 != nullptr || enemy3Template.texture2 != nullptr || enemy3Template.texture3 != nullptr || enemy3Template.texture4 != nullptr || enemy3Template.texture5 != nullptr)
    {
        SDL_DestroyTexture(enemy3Template.texture1);
        SDL_DestroyTexture(enemy3Template.texture2);
        SDL_DestroyTexture(enemy3Template.texture3);
        SDL_DestroyTexture(enemy3Template.texture4);
        SDL_DestroyTexture(enemy3Template.texture5);
    }

    if (player.combatTexture1 != nullptr || player.combatTexture2 != nullptr || player.combatTexture3 != nullptr || player.combatTexture4 != nullptr)
    {
        SDL_DestroyTexture(player.combatTexture1);
        SDL_DestroyTexture(player.combatTexture2);
        SDL_DestroyTexture(player.combatTexture3);
        SDL_DestroyTexture(player.combatTexture4);
    }

    if (player.skill2Texture != nullptr)
    {
        SDL_DestroyTexture(player.skill2Texture);
    }

    if (enemy1BulletTemplate.texture != nullptr || enemy1BulletTemplate.textureFrozen != nullptr || enemy1BulletTemplate.textureSlowed != nullptr || enemy1BulletTemplate.textureAlt != nullptr)
    {
        SDL_DestroyTexture(enemy1BulletTemplate.texture);
    }

    if (enemy2BulletTemplate.texture != nullptr || enemy2BulletTemplate.textureFrozen != nullptr || enemy2BulletTemplate.textureSlowed != nullptr || enemy2BulletTemplate.textureAlt != nullptr)
    {
        SDL_DestroyTexture(enemy2BulletTemplate.texture);
    }

    if (enemy3LaserTemplate.activationTexture != nullptr || enemy3LaserTemplate.inactivationTexture!= nullptr)
    {
        SDL_DestroyTexture(enemy3LaserTemplate.activationTexture);
        SDL_DestroyTexture(enemy3LaserTemplate.inactivationTexture);
    }

    if (backgroundTexture != nullptr)
    {
        SDL_DestroyTexture(backgroundTexture);
    }

    if (powerTemplate.texture != nullptr)
    {
        SDL_DestroyTexture(powerTemplate.texture);
    }

    if (bgTemplate1.texture != nullptr)
    {
        SDL_DestroyTexture(bgTemplate1.texture);
    }

    if (bgTemplate2.texture != nullptr)
    {
        SDL_DestroyTexture(bgTemplate2.texture);
    }

    if (enemy1BulletTemplate.textureFrozen != nullptr)
    {
        SDL_DestroyTexture(enemy1BulletTemplate.textureFrozen);
    }

    if (enemy1BulletTemplate.textureSlowed != nullptr)
    {
        SDL_DestroyTexture(enemy1BulletTemplate.textureSlowed);
    }

    if (enemy1BulletTemplate.textureAlt != nullptr)
    {
        SDL_DestroyTexture(enemy1BulletTemplate.textureAlt);
    }

    //清理标题
    if (titleTexture != nullptr)
    {
        SDL_DestroyTexture(titleTexture);
    }

    //清理字体
    if (statusFont != nullptr)
    {
        TTF_CloseFont(statusFont);
    }

    //清理血条
    if (healthBarTexture != nullptr) 
    {
        SDL_DestroyTexture(healthBarTexture);
    }

    if (pauseTextTexture1 != nullptr) 
    {
        SDL_DestroyTexture(pauseTextTexture1);
        pauseTextTexture1 = nullptr;
    }

    if (pauseTextTexture2 != nullptr)
    {
        SDL_DestroyTexture(pauseTextTexture2);
        pauseTextTexture2 = nullptr;
    }

    if (pauseTextTexture3 != nullptr)
    {
        SDL_DestroyTexture(pauseTextTexture3);
        pauseTextTexture3 = nullptr;
    }

    if (deathTextTexture1 != nullptr)
    {
        SDL_DestroyTexture(deathTextTexture1);
        deathTextTexture1 = nullptr;
    }

    if (deathTextTexture2 != nullptr)
    {
        SDL_DestroyTexture(deathTextTexture2);
        deathTextTexture2 = nullptr;
    }

}

void BattleField::handleEvents(SDL_Event* event)
{
    if (event->type == SDL_KEYDOWN) 
    {
        if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE && player.isDead == false) {
            isPaused = !isPaused; 
        }
        if (isPaused) 
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_Q)
            {
                game::getInstance().changeScene(new menu());
            }
        }
        if (player.isDead)
        {
            if (event->key.keysym.scancode == SDL_SCANCODE_Q)
            {
                game::getInstance().changeScene(new menu());
            }
        }
    }

}

void BattleField::keyboardControl(float deltaTime)
{
    auto keyboardState = SDL_GetKeyboardState(NULL); 
    if (!player.isDead)
    {
        // 自机移动
        if (keyboardState[SDL_SCANCODE_LEFT])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.x -= deltaTime * player.sneakSpeed;
            else
                player.position.x -= deltaTime * player.speed;
            if (player.position.x < 0) 
                player.position.x = 0;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.x += deltaTime * player.sneakSpeed;
            else
                player.position.x += deltaTime * player.speed;
            if (player.position.x > fieldW - player.width) 
                player.position.x = fieldW - player.width;
        }
        if (keyboardState[SDL_SCANCODE_UP])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.y -= deltaTime * player.sneakSpeed;
            else
                player.position.y -= deltaTime * player.speed;
            if (player.position.y < 0) 
                player.position.y = 0;
        }
        if (keyboardState[SDL_SCANCODE_DOWN])
        {
            if(keyboardState[SDL_SCANCODE_LSHIFT])
                player.position.y += deltaTime * player.sneakSpeed;
            else
                player.position.y += deltaTime * player.speed;
            if (player.position.y > fieldH - player.height) 
                player.position.y = fieldH - player.height;
        }
        //自机射击
        if(keyboardState[SDL_SCANCODE_Z])
        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - player.lastShootTime > player.FireCooldown / sqrt(1 + player.power * 0.2f))
            {
                selfShoot();
                player.lastShootTime = currentTime;
            }
        }

        //不射击恢复体力
        if (!keyboardState[SDL_SCANCODE_Z])
        {
            player.power += deltaTime * player.recoverSpeed;
        }

        if (keyboardState[SDL_SCANCODE_SPACE] && !spaceSign)
        {
            Uint32 currentTime = SDL_GetTicks();
            if (currentTime - player.lastMeleeTime > player.meleeCooldown / sqrt(1 + player.power))
            {
                player.combat(enemies); 
                player.renderCombatNeeded = true; 
                player.lastMeleeTime = currentTime; 
                player.space_signStartTime = currentTime; 
            }
            spaceSign = true;
        }

        if (!keyboardState[SDL_SCANCODE_SPACE])
        {
            spaceSign = false;
        }
        
        //主动技能
        if (keyboardState[SDL_SCANCODE_X] && !x_sign)
        {
            if (player.power >= 3.0f)
            {
                player.skill2(enemy1Bullets, enemies);
                player.x_signStartTime = SDL_GetTicks();
                player.renderSkill2Needed = true;
                player.power -= 3.0f;
            }
            x_sign = true;
        }

        if (!keyboardState[SDL_SCANCODE_X])
        {
            x_sign = false;
        }

        //终决技
        if (keyboardState[SDL_SCANCODE_C] && !c_sign)
        {
            if (player.power >= 10.0f)
            {
                player.skill3(enemy1Bullets, playerBullets);
                if (player.lives <= 19.0f)
                    player.lives += 1.0f;
                player.power -= 10.0f;
            }
            c_sign = true;
        }

        if (!keyboardState[SDL_SCANCODE_C])
        {
            c_sign = false;
        }

    }
}

void BattleField::selfShoot()
{
    auto projectile1 = new self_bullet(selfBulletTemplate);
    projectile1->position.x = player.position.x + (player.width - projectile1->width) / 2.0f;
    projectile1->position.y = player.position.y - projectile1->height;
    playerBullets.push_back(projectile1);  

    if (player.power >= 5.0f)
    {
        auto projectile2 = new self_bullet(selfBulletTemplate);
        projectile2->position.x = player.position.x + (player.width - projectile2->width) / 2.0f - 24;
        projectile2->position.y = player.position.y - projectile2->height;
        projectile2->damage /= 4.0f;
        if (player.power >= 10.0f)
        {
            projectile2->damage *= 2.0f;
        }
        if (player.power >= 25.0f)
        {
            projectile2->damage *= 2.0f;
        }
        playerBullets.push_back(projectile2);

        auto projectile3 = new self_bullet(selfBulletTemplate);
        projectile3->position.x = player.position.x + (player.width - projectile3->width) / 2.0f + 24;
        projectile3->position.y = player.position.y - projectile3->height;
        projectile3->damage /= 4.0f;
        if (player.power >= 10.0f)
        {
            projectile3->damage *= 2.0f;
        }
        if (player.power >= 25.0f)
        {
            projectile3->damage *= 2.0f;
        }
        playerBullets.push_back(projectile3);
    }
    if (player.power >= 25.0f)
    {
        auto projectile4 = new self_bullet(selfBulletTemplate);
        projectile4->position.x = player.position.x + (player.width - projectile4->width) / 2.0f - 32;
        projectile4->position.y = player.position.y - projectile4->height;
        projectile4->damage /= 4.0f;
        projectile4->speedX = -1 * projectile4->speed * 0.1f;
        if (player.power >= 50.0f)
        {
            projectile4->damage *= 2.0f;
        }
        playerBullets.push_back(projectile4);

        auto projectile5 = new self_bullet(selfBulletTemplate);
        projectile5->position.x = player.position.x + (player.width - projectile5->width) / 2.0f + 32;
        projectile5->position.y = player.position.y - projectile5->height;
        projectile5->damage /= 4.0f;
        projectile5->speedX = projectile5->speed * 0.1f;
        if (player.power >= 50.0f)
        {
            projectile5->damage *= 2.0f;
        }
        playerBullets.push_back(projectile5);
    }
}

void BattleField::playerBulletsUpdate(float deltaTime)
{
    for(auto it = playerBullets.begin(); it != playerBullets.end(); )
    {
        auto bullet = *it;
        bullet->position.y -= bullet->speed * deltaTime;
        bullet->position.x += bullet->speedX * deltaTime;
        //子弹超出屏幕范围，删除子弹
        if ((bullet->position.y < 0 - bullet->height) ||
            (bullet->position.y > fieldH) ||
            (bullet->position.x < 0 - bullet->width) ||
            (bullet->position.x > fieldW) )
        {
            delete bullet;
            it = playerBullets.erase(it);
        }
        else
        {
            bool hit = false;
            SDL_Rect bulletRect = 
                {
                    static_cast<int>(bullet->position.x),
                    static_cast<int>(bullet->position.y),
                    bullet->width,
                    bullet->height
                };
            for (auto enemy : enemies)
            {
                if (std::visit([&bulletRect](auto&& enemy)
                {
                    SDL_Rect enemyRect = 
                    {
                        static_cast<int>(enemy->position.x),
                        static_cast<int>(enemy->position.y),
                        enemy->width,
                        enemy->height
                    };
                    return SDL_HasIntersection(&bulletRect, &enemyRect);
                }, enemy))
                {
                    std::visit([&bullet](auto&& enemy)
                    {
                        enemy->health -= bullet->damage;
                    }, enemy);
                    delete bullet;
                    it = playerBullets.erase(it);
                    hit = true;
                    break; 
                }
            }
            if (!hit)
            {
                ++it;
            }
        }
    }
}

void BattleField::playerBulletsRender()
{
    for(auto projectile : playerBullets)
    {
        SDL_Rect bulletRect = 
        {
            static_cast<int>(projectile->position.x),
            static_cast<int>(projectile->position.y),
            projectile->width,
            projectile->height
        };
        SDL_RenderCopy(game.getRenderer(), projectile->texture, NULL, &bulletRect);
    }
}

void BattleField::generateEnemy()
{
    if (dist(gen) < 0.7f)
    {
        enemy1* Enemy1 = new enemy1(enemyTemplate);
        Enemy1->position.x = dist(gen) * (fieldW - Enemy1->width);
        Enemy1->position.y = -Enemy1->height; 
        enemies.push_back(Enemy1);
    }
    if (dist(gen) < 0.08f)
    {
        enemy2* Enemy2 = new enemy2(enemy2Template);
        Enemy2->position.x = dist(gen) * (fieldW - Enemy2->width);
        Enemy2->position.y = -Enemy2->height; 
        enemies.push_back(Enemy2);
    }
    if (dist(gen) < 0.05f)
    {
        enemy3* Enemy3 = new enemy3(enemy3Template);
        Enemy3->position.x = dist(gen) * (fieldW - Enemy3->width);
        Enemy3->position.y = -Enemy3->height; 
        enemies.push_back(Enemy3);
    }
}

void BattleField::spawnEnemy()
{
    if (dist(gen) < 0.0015f && player.power < 5.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.0025f && player.power >= 5.0f && player.power < 10.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.005f && player.power >= 10.0f && player.power < 25.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.012f && player.power >= 25.0f && player.power < 50.0f)
    {
        generateEnemy();
    }
    if (dist(gen) < 0.015f && player.power >= 50.0f)
    {
        generateEnemy();
    }
}

void BattleField::updateEnemies1(float deltaTime)
{
    auto currentTime = SDL_GetTicks();
    for(auto it = enemies.begin(); it != enemies.end(); )
    {
        std::visit([&it, &currentTime, &player = this->player, deltaTime, this](auto&& enemy) {
            using T = std::decay_t<decltype(enemy)>;
            if constexpr (std::is_same_v<T, enemy1*> || std::is_same_v<T, enemy2*>)
            {
                enemy->position.y += enemy->speed * deltaTime;
            }
            if constexpr (std::is_same_v<T, enemy3*>)
            {
                if (!enemy->isShooting)
                    enemy->position.y += enemy->speed * deltaTime;
            }
            
            if ((enemy->position.y > fieldH) ||
                (enemy->position.y < 0 - enemy->height) ||
                (enemy->position.x < 0 - enemy->width) ||
                (enemy->position.x > fieldW) )
            {
                delete enemy;
                it = enemies.erase(it);
            }
            else
            {
                using T = std::decay_t<decltype(enemy)>;
                if constexpr (std::is_same_v<T, enemy1*> || std::is_same_v<T, enemy2*>)
                {
                    if (currentTime - enemy->lastShootTime > enemy->FireCooldown && !player.isDead)
                    {
                        enemyShot(enemy);
                        enemy->lastShootTime = currentTime;
                    }
                }
                if constexpr (std::is_same_v<T, enemy3*>) 
                {
                    if (currentTime - enemy->lastShootTime > enemy->FireCooldown && !player.isDead) 
                    {
                        enemy->isShooting = true;
                        enemyLaserShot(enemy);
                        enemy->lastShootTime = currentTime;
                    }
                    if (enemy->isShooting && currentTime - enemy->lastShootTime >= (enemy3LaserTemplate.alarmTime + enemy3LaserTemplate.duration)) 
                    {
                        enemy->isShooting = false;
                    }
                }
                if (enemy->health <= 0)
                {
                    enemy1Death(enemy);
                    it = enemies.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }, *it);
    }
}

void BattleField::renderEnemies1()
{
    for(auto enemy : enemies)
    {
        std::visit([this](auto&& enemy)
        {
            SDL_Rect enemyRect = 
            {
                static_cast<int>(enemy->position.x),
                static_cast<int>(enemy->position.y),
                enemy->width,
                enemy->height
            };
            int currentFrame = (SDL_GetTicks() - startTime) / 100;
            if (currentFrame % 5 == 0)
            {
                SDL_RenderCopy(game.getRenderer(), enemy->texture1, NULL, &enemyRect);
            }
            else if (currentFrame % 5 == 1)
            {
                SDL_RenderCopy(game.getRenderer(), enemy->texture2, NULL, &enemyRect);
            }
            else if (currentFrame % 5 == 2)
            {
                SDL_RenderCopy(game.getRenderer(), enemy->texture3, NULL, &enemyRect);
            }
            else if (currentFrame % 5 == 3)
            {
                SDL_RenderCopy(game.getRenderer(), enemy->texture4, NULL, &enemyRect);
            }
            else if (currentFrame % 5 == 4)
            {
                SDL_RenderCopy(game.getRenderer(), enemy->texture5, NULL, &enemyRect);
            }
    }, enemy);
    }
}

void BattleField::enemyShot(std::variant<enemy1*, enemy2*, enemy3*> enemy)
{
    std::visit([this](auto&& e) {
        using T = std::decay_t<decltype(e)>;
        if constexpr (std::is_same_v<T, enemy1*>) 
        {
            auto projectile = new enemy1_bullet(enemy1BulletTemplate);
            projectile->position.x = e->position.x + (e->width - projectile->width) / 2.0f;
            projectile->position.y = e->position.y + e->height;
            projectile->direction = getDirection(e);
            enemy1Bullets.push_back(projectile);
        } 
        else if constexpr (std::is_same_v<T, enemy2*>) 
        {
            for(int i = 0; i < 12; i++)
            {
                auto projectile = new enemy2_bullet(enemy2BulletTemplate);
                projectile->position.x = e->position.x + (e->width - projectile->width) / 2.0f;
                projectile->position.y = e->position.y + e->height / 2.0f;
                //根据i决定方向
                projectile->direction = SDL_FPoint{cos(static_cast<float>(i * M_PI / 6.0f)), sin(static_cast<float>(i * M_PI / 6.0f))};
                enemy1Bullets.push_back(projectile);
            }
        }
    }, enemy);
}

void BattleField::enemyLaserShot(std::variant<enemy1 *, enemy2 *, enemy3 *> enemy)
{
    std::visit([this](auto&& enemy) {
        using T = std::decay_t<decltype(enemy)>;
        if constexpr (std::is_same_v<T, enemy3*>) 
        {
            auto laser = new enemy3_laser(enemy3LaserTemplate);
            laser->isActive = false;
            laser->startPosition.x = enemy->position.x + (enemy->width - laser->width) / 2.0f;
            laser->startPosition.y = enemy->position.y + enemy->height / 2.0f;
            laser->endPosition.x = player.position.x + player.width / 2.0f + getDirection(enemy).x * sqrt(fieldW*fieldW + fieldH*fieldH);
            laser->endPosition.y = player.position.y + player.height / 2.0f + getDirection(enemy).y * sqrt(fieldW*fieldW + fieldH*fieldH);
            laser->startTime = SDL_GetTicks();
            enemyLasers.push_back(laser);

        }
    }, enemy);
}

template<typename EnemyType>
SDL_FPoint BattleField::getDirection(EnemyType *enemy)
{
    auto dx = (player.position.x + player.width / 2.0f) - (enemy->position.x + enemy->width / 2.0f);
    auto dy = (player.position.y + player.height / 2.0f) - (enemy->position.y + enemy->height / 2.0f);
    auto distance = sqrt(dx * dx + dy * dy);
    dx /= distance;
    dy /= distance;
    return SDL_FPoint{dx, dy};
}

void BattleField::updateEnemy1Bullets(float deltaTime)
{
    for(auto it = enemy1Bullets.begin(); it != enemy1Bullets.end(); )
    {
        bool shouldErase = std::visit([this, deltaTime](auto&& bullet) {
            bullet->position.x += bullet->speed * bullet->direction.x * deltaTime;
            bullet->position.y += bullet->speed * bullet->direction.y * deltaTime;
            
            if ((bullet->position.y > fieldH) ||
                (bullet->position.y < 0 - bullet->height) ||
                (bullet->position.x < 0 - bullet->width) ||
                (bullet->position.x > fieldW) )
            {
                delete bullet;
                return true;
            }
            
            SDL_Rect bulletRect = 
                {
                    static_cast<int>(bullet->position.x),
                    static_cast<int>(bullet->position.y),
                    bullet->width,
                    bullet->height
                };
            SDL_Rect selfpointBox = 
                {
                    static_cast<int>(player.position.x + 16),
                    static_cast<int>(player.position.y + 16),
                    16,
                    16
                };
            int boxCenterX = selfpointBox.x + selfpointBox.w / 2;
            int boxCenterY = selfpointBox.y + selfpointBox.h / 2;
            int bulletCenterX = bulletRect.x + bulletRect.w / 2;
            int bulletCenterY = bulletRect.y + bulletRect.h / 2;
            int distanceX = boxCenterX - bulletCenterX;
            int distanceY = boxCenterY - bulletCenterY;
            int distance = sqrt(distanceX * distanceX + distanceY * distanceY);
            if (distance < (selfpointBox.w + bulletRect.w) / 2 - 5 && !player.isDead)
            {
                player.lives -= bullet->damage;
                player.power -= (bullet->damage * (player.power / player.powerMax) * 10.0f);
                delete bullet;
                return true;
            }
            return false;
        }, *it);

        if (shouldErase)
        {
            it = enemy1Bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void BattleField::updateEnemy1Lasers(float deltaTime)
{
    for (auto it = enemyLasers.begin(); it != enemyLasers.end(); )
    {
        auto laser = *it;
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsed = currentTime - laser->startTime;

        // 检查是否激活（3秒后）
        if (elapsed >= enemy3LaserTemplate.alarmTime && !laser->isActive)
        {
            laser->isActive = true;
        }

        // 检查是否结束
        if (elapsed >= laser->duration + enemy3LaserTemplate.alarmTime)
        {
            delete laser;
            it = enemyLasers.erase(it);
        }
        else
        {
            // 如果激光已激活，检查与玩家的碰撞
            if (laser->isActive)
            {
                SDL_FPoint playerCenter = {
                    player.position.x + player.width / 2.0f,
                    player.position.y + player.height / 2.0f
                };

                // 计算点到线段的距离
                float A = laser->endPosition.y - laser->startPosition.y;
                float B = laser->startPosition.x - laser->endPosition.x;
                float C = laser->endPosition.x * laser->startPosition.y - laser->startPosition.x * laser->endPosition.y;
                float distance = abs(A * playerCenter.x + B * playerCenter.y + C) / sqrt(A * A + B * B);

                // 如果距离小于激光宽度的一半，造成伤害
                if (distance < laser->width / 2.0f && !player.isDead)
                {
                    player.lives -= laser->damage * deltaTime;
                    player.power -= (laser->damage * (player.power / player.powerMax) * 0.1f);
                }
            }
            ++it;
        }
    }
}

void BattleField::enemy1BulletsRender()
{
    for(auto projectile : enemy1Bullets)
    {
        std::visit([this](auto&& bullet) {
            SDL_Rect bulletRect = 
            {
                static_cast<int>(bullet->position.x),
                static_cast<int>(bullet->position.y),
                bullet->width,
                bullet->height
            };
            float angle = atan2(bullet->direction.y, bullet->direction.x) * 180.0f / M_PI - 90.0f;
            SDL_RenderCopyEx(game.getRenderer(), bullet->texture, NULL, &bulletRect, angle, NULL, SDL_FLIP_NONE);
        }, projectile);
    }
}

void BattleField::enemy1LasersRender()
{
    for (auto laser : enemyLasers)
    {
        float dx = laser->endPosition.x - laser->startPosition.x;
        float dy = laser->endPosition.y - laser->startPosition.y;
        float length = sqrt(dx * dx + dy * dy);
        
        float angle = atan2(-dx, dy) * 180.0f / M_PI;
        
        SDL_Rect laserRect = 
        {
            static_cast<int>(laser->startPosition.x),
            static_cast<int>(laser->startPosition.y),
            static_cast<int>(laser->width),  
            static_cast<int>(length)  
        };
        

        SDL_Point center = {laser->width / 2, 0}; 
        
        if (laser->isActive)
        {
            SDL_RenderCopyEx(game.getRenderer(), laser->activationTexture, NULL, &laserRect, angle, &center, SDL_FLIP_NONE);
        }
        else
        {
            SDL_RenderCopyEx(game.getRenderer(), laser->inactivationTexture, NULL, &laserRect, angle, &center, SDL_FLIP_NONE);
        }
    }
}

void BattleField::enemy1Death(std::variant<enemy1*, enemy2*, enemy3*> enemy)
{
    std::visit([this](auto&& enemy) {
        generatePower(enemy);
        exp += enemy->score;
        delete enemy;
    }, enemy);

}

void BattleField::updatePlayer(float)
{
    if (player.isDead)
        return;
    if (player.lives <= 0)
    {            
        player.isDead = true;
    }
}

void BattleField::generatePower(std::variant<enemy1*, enemy2*, enemy3*> enemy)
{
    std::visit([this](auto&& enemy) {
        power* Power = new power(powerTemplate);
        using T = std::decay_t<decltype(enemy)>;
        if constexpr (std::is_same_v<T, enemy1*>)
        {
            Power->value = dist(gen) / 2.0f + 0.1f;
        }
        else if constexpr (std::is_same_v<T, enemy2*>)
        {
            Power->value = dist(gen) / 1.6f + 0.12f;
        }
        else if constexpr (std::is_same_v<T, enemy3*>)
        {
            Power->value = dist(gen) / + 0.15f;
        }
        Power->direction.x = static_cast<int>(dist(gen) * 200.0f) /10 * 10;
        Power->direction.y = static_cast<int>(dist(gen) * 100.0f) /10 * 10 + 50;
        if(dist(gen) > 0.5f)
            Power->direction.x = -Power->direction.x;
        Power->sizeTrue = Power->width * (0.5f + sqrtf(Power->value) * 0.5f);
        Power->position.x = enemy->position.x + (enemy->width - Power->sizeTrue) / 2.0f;
        Power->position.y = enemy->position.y + (enemy->height - Power->sizeTrue) / 2.0f;
        powers.push_back(Power);
    },enemy);
}

void BattleField::updatePowers(float deltaTime)
{
    SDL_Rect playerRect = 
    {
        static_cast<int>(player.position.x),
        static_cast<int>(player.position.y),
        static_cast<int>(player.width),
        static_cast<int>(player.height)
    };
    for(auto it = powers.begin(); it != powers.end(); )
    {
        auto power = *it;
        if (power->direction.x < 0)
        {
            power->direction.x += power->acceleration;
        }
        else if (power->direction.x > 0)
        {
            power->direction.x -= power->acceleration;
        }
        power->position.x += power->direction.x * deltaTime;
        power->position.y += power->direction.y * deltaTime;

        //当按shift时p点向自机靠近
        Uint32 currentTime = SDL_GetTicks();
        auto keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_LSHIFT])
        {
            z_sign = 1;
            player.z_signStartTime = currentTime;
        }
        //2秒后z_sign归0
        if (z_sign == 1 && currentTime - player.z_signStartTime > 1000)
        {
            z_sign = 0;
        }

        if (z_sign == 1)
        {
            //p点和自机距离小于200px时，p点向自机靠近
            if (sqrt(pow(power->position.x - player.position.x, 2) + pow(power->position.y - player.position.y, 2)) < 200)
            {
                auto dx = (player.position.x + player.width / 2.0f) - (power->position.x + power->sizeTrue / 2.0f);
                auto dy = (player.position.y + player.height / 2.0f) - (power->position.y + power->sizeTrue / 2.0f);
                auto distance = sqrt(dx * dx + dy * dy);
                dx /= distance;
                dy /= distance;
                power->position.x += dx * power->acceleration * deltaTime * 300;
                power->position.y += dy * power->accelerationY * deltaTime * 300;
            }
        }
        SDL_Rect powerRect = 
        {
            static_cast<int>(power->position.x),
            static_cast<int>(power->position.y),
            power->sizeTrue,
            power->sizeTrue
        };
        if ((power->position.y > fieldH) ||
            (power->position.y < 0 - power->sizeTrue) ||
            (power->position.x < 0 - power->sizeTrue) ||
            (power->position.x > fieldW) )
        {
            delete power;
            it = powers.erase(it);
        }
        else if (SDL_HasIntersection(&playerRect, &powerRect))
        {
            player.power += power->value;
            delete power;
            it = powers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void BattleField::renderPowers()
{
    for(auto power : powers)
    {
        SDL_Rect powerRect = 
        {
            static_cast<int>(power->position.x),
            static_cast<int>(power->position.y),
            power->sizeTrue,
            power->sizeTrue
        };
        SDL_RenderCopy(game.getRenderer(), power->texture, NULL, &powerRect);
    }
}

void BattleField::statusRender()
{
    //残机（生命值)
    std::ostringstream lifeTextRaw;
    lifeTextRaw << "生命: ";
    std::string lifeText = lifeTextRaw.str();
    SDL_Surface* lifeSurface = TTF_RenderUTF8_Solid(statusFont, lifeText.c_str(), {255, 255, 255, 255});

    SDL_Texture* lifeTexture = SDL_CreateTextureFromSurface(game.getRenderer(), lifeSurface);
    SDL_Rect lifeRect = { fieldW + 32, 32, lifeSurface->w, lifeSurface->h };
    SDL_RenderCopy(game.getRenderer(), lifeTexture, NULL, &lifeRect);
    SDL_FreeSurface(lifeSurface);
    SDL_DestroyTexture(lifeTexture);

    SDL_Rect healthBar = { fieldW + 96, 36, healthBarW, healthBarH };
    SDL_RenderCopy(game.getRenderer(), healthBarTexture, NULL, &healthBar);
    if (player.lives < 20.0f)
    {
        SDL_SetRenderDrawColor(game.getRenderer(), 0, 0, 0, 255);
        SDL_Rect healthRect = { 
                            fieldW + 96 + static_cast<int>(healthBarW * (player.lives / 20.0f)) + 1, 
                            37, 
                            healthBarW - static_cast<int>(healthBarW * (player.lives / 20.0f)) - 2, 
                            healthBarH - 2
                            };
        SDL_RenderFillRect(game.getRenderer(), &healthRect);
    }

    //渲染灵力
    std::ostringstream powerTextRaw;
    powerTextRaw << "体力: " << std::fixed << std::setprecision(2) << player.power;
    std::string powerText = powerTextRaw.str();
    SDL_Surface* powerSurface = TTF_RenderUTF8_Solid(statusFont, powerText.c_str(), {255, 255, 255, 255});

    SDL_Texture* powerTexture = SDL_CreateTextureFromSurface(game.getRenderer(), powerSurface);
    SDL_Rect powerRect = { fieldW + 32, 64, powerSurface->w, powerSurface->h };
    SDL_RenderCopy(game.getRenderer(), powerTexture, NULL, &powerRect);
    SDL_FreeSurface(powerSurface);
    SDL_DestroyTexture(powerTexture);

    //渲染经验
    std::ostringstream expTextRaw;
    expTextRaw << "经验: " << exp;
    std::string expText = expTextRaw.str();
    SDL_Surface* expSurface = TTF_RenderUTF8_Solid(statusFont, expText.c_str(), {255, 255, 255, 255});

    SDL_Texture* expTexture = SDL_CreateTextureFromSurface(game.getRenderer(), expSurface);
    SDL_Rect expRect = { fieldW + 32, 96, expSurface->w, expSurface->h };
    SDL_RenderCopy(game.getRenderer(), expTexture, NULL, &expRect);
    SDL_FreeSurface(expSurface);
    SDL_DestroyTexture(expTexture);
    
    //渲染标题
    SDL_Rect titleRect = { fieldW + 160, 450, static_cast<int>(titleW / 1.5), static_cast<int>(titleH / 1.5) };
    SDL_RenderCopy(game.getRenderer(), titleTexture, NULL, &titleRect);
}

void BattleField::updateBattleBackground(float deltaTime)
{
    // 如果背景容器为空，初始化两个背景
    if (battleBackgrounds.empty())
    {
        background* bg1 = new background(bgTemplate1);
        background* bg2 = new background(bgTemplate2);
        
        bg1->position.x = 0;
        bg1->position.y = 0;
        
        bg2->position.x = 0;
        bg2->position.y = -bg1->height;  // 第二个背景在第一个背景上方
        
        battleBackgrounds.push_back(bg1);
        battleBackgrounds.push_back(bg2);
    }
    
    // 更新背景位置
    for (auto bg : battleBackgrounds)
    {
        bg->position.y += bg->speed * deltaTime;
        
        // 如果背景完全移出屏幕，将其重置到另一个背景的上方
        if (bg->position.y > fieldH)
        {
            for (auto otherBg : battleBackgrounds)
            {
                if (otherBg != bg)
                {
                    bg->position.y = otherBg->position.y - bg->height;
                    break;
                }
            }
        }
    }
}

void BattleField::powerManage()
{
    if (player.power > 100.0f)
    {
        player.power = 100.0f;
    }

    if (player.power < 0.0f)
    {
        player.power = 0.0f;
    }
}

void BattleField::rollingBackgroundRender()
{
    for (auto bg : battleBackgrounds)
    {
        SDL_Rect bgRect = { static_cast<int>(bg->position.x), static_cast<int>(bg->position.y), bg->width, bg->height };
        SDL_RenderCopy(game.getRenderer(), bg->texture, NULL, &bgRect);
    }
}
