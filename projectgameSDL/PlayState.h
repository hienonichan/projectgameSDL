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

private:
    int code = 2;
    std::vector<GameObject*>gameObjects;
    std::vector<Enemy*>enemys;
    std::vector<Bullet*>bullets;
    Mix_Chunk* sound1 = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/soundplay.wav");
    Mix_Chunk* shootingsound = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/shooting sound.wav");
    std::map<Enemy*, int>check_enemy;
    std::map<Bullet*, int>check_bullet;
    GameObject* player1 = nullptr;

    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Color colorText = { 255,255,255 };
    SDL_Rect textRect = { 500,300,300,300 };

};

#endif