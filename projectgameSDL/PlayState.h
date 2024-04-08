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

    void clearBullet() {
        // clear dan trung muc tieu
        for (int i = 0; i < bullets.size(); i++) {
            Vector cam = Camera::getInstance()->GetPosition();
            if (check_bullet[bullets[i]] == 1) {
                bullets[i]->clean();
                bullets.erase(bullets.begin() + i);
                i--;
            }
            else if (abs(bullets[i]->getPos().length() - (player1->getPos()-cam).length()) >= SCREEN_WIDTH) {
                bullets[i]->clean();
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }
    }

    void clearEnemy() {
        // clear enemy bi chet
        for (int i = 0; i < enemys.size(); i++) {
            if (check_enemy[enemys[i]] == 1) {
                enemys[i]->clean();
                enemys.erase(enemys.begin() + i);
                i--;
            }
        }
    }

    void clearBoss() {
        for (int i = 0; i < bosses.size(); i++) {
            if (check_boss[bosses[i]] == 1) {
                bosses[i]->clean();
                bosses.erase(bosses.begin() + i);
                i--;
            }
        }
    }

    void clearItem() {
        for (int i = 0; i < items.size(); i++) {
            if (check_item[items[i]] == 1) {
                items[i]->clean();
                items.erase(items.begin() + i);
                i--;
            }
        }
    }

    // ham check reload
    bool checkReload() {
        if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_R)) {
            return true;
        }
        return false;
    }

    int ran() {
        int loi = rand() % 2000 + 1;
        return loi;
    }


    // xu li boost
    void up_health();
    void up_attack();
    void up_ammo();

    // xu li render stat
    void render_health();
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
    

    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Color colorText = { 255,255,255 };
    SDL_Rect textRect = { 500,300,300,300 };


    SDL_Surface* textSurface2 = nullptr;
    SDL_Texture* textTexture2 = nullptr;
    SDL_Color colorText2 = { 255,255,255 };
    SDL_Rect textRect2 = { 50,50,300,300 };


    SDL_Surface* textSurface3 = nullptr;
    SDL_Texture* textTexture3 = nullptr;
    SDL_Color colorText3 = { 255,255,255 };
    SDL_Rect textRect3 = { 50,100,300,300 };

    SDL_Surface* textSurface4 = nullptr;
    SDL_Texture* textTexture4 = nullptr;
    SDL_Color colorText4 = { 255,255,255 };
    SDL_Rect textRect4 = { 50,150,300,300 };

    SDL_Surface* textSurface5 = nullptr;
    SDL_Texture* textTexture5 = nullptr;
    SDL_Color colorText5 = { 255,255,255 };
    SDL_Rect textRect5 = { 350,400,300,300 };

    SDL_Surface* surface_background = nullptr;
    SDL_Texture* texture_background = nullptr;

   
    int mode_shot = 5;

};

#endif