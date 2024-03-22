#ifndef __DelayState__
#define __DelayState__
#include"State.h"
#include<vector>
#include"GameObject.h"
class DelayState:public State {
public:
    virtual void update();
    virtual void render();

    virtual bool loadState();
    virtual bool exitState();

    int getStateCode() { return code; }
private:
    int code = 3;
    std::vector<GameObject*>gameObjects;

    static void turnToHome();
    static void turnToPlay();

    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Color colorText = { 255,0,0 };
    SDL_Rect textRect = { 400,100,400,400 };

    SDL_Surface* surface_background = nullptr;
    SDL_Texture* texture_background = nullptr;
};
#endif