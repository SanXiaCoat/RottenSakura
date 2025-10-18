#pragma once
#include <list>
#include "scene.h"
#include "self.h"
#include "enermy.h"
#include "item.h"
#include <random>

class game;

struct background
{
    SDL_Texture* texture = nullptr;
    SDL_FPoint position = {0.0f, 0.0f};
    float offset = 0;
    int width = fieldBGw;
    int height = fieldBGh / 2;
    int speed = 20;
};

class BattleField : public scene
{
public:
    BattleField();
    ~BattleField(); 

    void update(float deltaTime) override;
    void render() override;
    void init() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;

    void keyboardControl(float deltaTime);
    void selfShoot();
    void playerBulletsUpdate(float deltaTime);
    void playerBulletsRender();
    void generateEnemy();
    void spawnEnemy();
    void updateEnemies1(float deltaTime);
    void renderEnemies1();
    void enemyShot(std::variant<enemy1*, enemy2*, enemy3*> enemy);
    void enemyLaserShot(std::variant<enemy1*, enemy2*, enemy3*> enemy);
    template<typename EnemyType>
    SDL_FPoint getDirection(EnemyType *enemy);
    void updateEnemy1Bullets(float deltaTime);
    void updateEnemy1Lasers(float deltaTime);
    void enemy1BulletsRender();
    void enemy1LasersRender();
    void enemy1Death(std::variant<enemy1*, enemy2*, enemy3*> enemy);
    void updatePlayer(float deltaTime);
    void generatePower(std::variant<enemy1*, enemy2*, enemy3*> enemy);
    void updatePowers(float deltaTime);
    void renderPowers();
    void statusRender();
    void rollingBackgroundRender();
    void updateBattleBackground(float deltaTime);
    void powerManage();

    Uint32 startTime;
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* titleTexture = nullptr;
    SDL_Texture* healthBarTexture = nullptr;
    bool z_sign = 1;
    bool spaceSign = 0;
    bool c_sign = 0;
    bool x_sign = 0;
    bool isPaused = false;
    SDL_Texture* pauseTextTexture1 = nullptr;
    SDL_Texture* pauseTextTexture2 = nullptr;
    SDL_Texture* pauseTextTexture3 = nullptr;
    SDL_Texture* deathTextTexture1 = nullptr;
    SDL_Texture* deathTextTexture2 = nullptr;

private:
    //随机数种子
    std::mt19937 gen;
    std::uniform_real_distribution<float> dist;

    //实例与玩家
    game &game;
    Player player;

    //字体
    TTF_Font* statusFont;

    int exp = 0;

    //模版与容器
    self_bullet selfBulletTemplate;
    std::list<self_bullet*> playerBullets;

    enemy1 enemyTemplate;
    enemy2 enemy2Template;
    enemy3 enemy3Template;
    std::list<std::variant<enemy1*, enemy2*, enemy3*>> enemies;

    enemy1_bullet enemy1BulletTemplate;
    enemy2_bullet enemy2BulletTemplate;
    enemy3_laser enemy3LaserTemplate;
    std::list<std::variant<enemy1_bullet*, enemy2_bullet*>> enemy1Bullets;
    std::list<enemy3_laser*> enemyLasers;

    power powerTemplate;
    std::list<power*> powers;

    background bgTemplate1;
    background bgTemplate2;
    std::list<background*> battleBackgrounds;

};







