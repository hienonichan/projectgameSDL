#ifndef __GameOver__
#define __GameOver__
#include"State.h"
#include<vector>
#include"GameObject.h"

#include"GameControl.h"

class GameOver :public State {
public:
    virtual void update();
    virtual void render();

    virtual bool loadState();
    virtual bool exitState();

    virtual int getStateCode() { return code; }
private:
    int code = 4;
    std::vector<GameObject*>gameObjects;

    static void restart();
    static void returnMenu();

    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Color colorText = { 255,0,0 };
    SDL_Rect textRect = { 450,50,300,300 };

    SDL_Surface* textSurface2 = nullptr;
    SDL_Texture* textTexture2 = nullptr;
    SDL_Color colorText2 = { 255,255,255 };
    SDL_Rect textRect2 = { 500,130,300,300 };

    int max_score = 0;

    SDL_Surface* surface_background = nullptr;
    SDL_Texture* texture_background = nullptr;
};
#endif
