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

class PlayState :public State {
public:
    virtual void update();
    virtual void render();
    virtual bool loadState();
    virtual bool exitState();
   virtual int getStateCode() { return code; }

   void PlayMusic() {
       Mix_PlayChannel(-1, sound1, -1);
   }


   void rand_enemy();

   void clearBullet() {
       // clear dan trung muc tieu
       for (int i = 0; i < bullets.size(); i++) {
           if (check_bullet[bullets[i]] == 1) {
               bullets.erase(bullets.begin() + i);
               i--;
           }
           else if (abs(bullets[i]->getPos().length() - player1->getPos().length()) >= 2000) {
               bullets.erase(bullets.begin() + i);
               i--;
           }
       }
   }

   void clearEnemy() {
       // clear enemy bi chet
       for (int i = 0; i < enemys.size(); i++) {
           if (check_enemy[enemys[i]] == 1) {
               enemys.erase(enemys.begin() + i);
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

private:
    int code = 2;
    std::vector<GameObject*>gameObjects;
    std::vector<Enemy*>enemys;
    std::vector<Bullet*>bullets;
    Mix_Chunk* sound1 = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/Warriyo - Mortals (feat. Laura Brehm) [NCS Release] (1).wav");
    Mix_Chunk* shootingsound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/shooting sound.wav");
    Mix_Chunk* hurtSound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/roblox-death-sound-effect.wav");
    Mix_Chunk* reloadSound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/1911-reload-6248.wav");
    std::map<Enemy*, int>check_enemy;
    std::map<Bullet*, int>check_bullet;
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

};

#endif