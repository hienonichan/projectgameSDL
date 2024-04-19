#ifndef __PlayState__
#define __PlayState__
#include"State.h"
#include<vector>
#include"GameObject.h"
#include<SDL_mixer.h>
#include<thread>
#include"Enemy.h"
#include"BulletObject.h"
#include<map>
#include"InputChecker.h"
#include"Boss.h"
#include"GameItem.h"
#include"Healthbar.h"

class PlayState :public State {
public:
    virtual void update();
    virtual void render();
    virtual bool loadState();
    virtual bool exitState();
    virtual int getStateCode() { return code; }

    void PlayMusic() {
        Mix_PlayChannel(-1, sound1, 0);
    }


    void rand_enemy(int type);

    void clearBullet();
    void clearEnemy();
    void clearBoss();
    void clearItem();

    // ham check reload
    bool checkReload() {
        if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_R)) {
            return true;
        }
        return false;
    }
    
    std::pair<int,int> ranPos() {  
        int hehe = rand() % 2;
        int x = rand() % 2860 - 150;
        int y;
        if (hehe == 1) { y= sqrt(8192000 - pow(x - 1280, 2)) + 640; }
        else { y=-sqrt(8192000 - pow(x - 1280, 2)) + 640; }
        return std::make_pair(x, y);
    }
   
       

    // xu li boost
    void up_health();
    void up_attack();
    void up_ammo();

    // xu li render stat
    void render_ammo();
    void render_score();

    // xu li sung
    void reload();
    // mode ban 1 vien
    void shot1();
    // mode ban 3 vien
    void shot3();
    // mode shot 5 vien
    void shot5();
    // summon dan xung quanh
    void summon();
    // ham thay doi mode
    void mode(int p) {
        mode_shot = p;
    }
    void sword_energy_skill();

    std::vector<Enemy*>& getEnemyArray() {
        return enemys;
    }

private:
    int code = 2;
    std::vector<GameObject*>gameObjects;
    std::vector<Enemy*>enemys;
    std::vector<Bullet*>bullets;
    std::vector<Boss*>bosses;
    std::vector<GameItem*>items;
    Mix_Chunk* sound1 = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/playing music.wav");
    Mix_Chunk* shootingsound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/shooting sound.wav");
    Mix_Chunk* hurtSound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/roblox-death-sound-effect.wav");
    Mix_Chunk* reloadSound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/1911-reload-6248.wav");
    std::map<Enemy*, int>check_enemy;
    std::map<Bullet*, int>check_bullet;
    std::map<Boss*, int>check_boss;
    std::map<GameItem*, int>check_item;
    GameObject* player1 = nullptr;
    

    SDL_Surface* textSurface2 = nullptr;
    SDL_Texture* textTexture2 = nullptr;
    SDL_Color colorText2 = { 255,255,255 };
    SDL_Rect textRect2 = { 50,80,300,300 };


    SDL_Surface* textSurface4 = nullptr;
    SDL_Texture* textTexture4 = nullptr;
    SDL_Color colorText4 = { 255,255,255 };
    SDL_Rect textRect4 = { 50,100,300,300 };

  

    SDL_Surface* surface_background = nullptr;
    SDL_Texture* texture_background = nullptr;

    SDL_Surface* surface_bar = nullptr;
    SDL_Texture* texture_bar = nullptr;
    SDL_Rect rect_bar = { 0,0,228,60 };
   
    int mode_shot = 1;

    enum BULLET_STATE {
        BULLET_NOT_HIT = 0,
        BULLET_HIT = 1,
        BULLET_CIRCLE = 2,
        BULLET_EXPLOSION = 3
    };

    enum ENEMY_STATE {
        ALIVE = 0,
        DIE = 1
    };

   

};

#endif