#ifndef __PlayState__
#define __PlayState__
#include"State.h"
#include<vector>
#include"GameObject.h"
#include<SDL_mixer.h>
#include<thread>
#include"Enemy.h"
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

private:
    int code = 2;
    std::vector<GameObject*>gameObjects;
    std::vector<Enemy*>enemys;
    Mix_Chunk* sound1 = Mix_LoadWAV("C:/projectgameSDL/projectgameSDL/soundplay.wav");
};

#endif