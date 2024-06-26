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
    int score = 0;
    std::vector<GameObject*>gameObjects;
    static void restart();
    static void returnMenu();

    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Color colorText = { 255,0,0 };
    SDL_Rect textRect = { 480,90,300,300 };

    SDL_Surface* textSurface2 = nullptr;
    SDL_Texture* textTexture2 = nullptr;
    SDL_Color colorText2 = { 255,255,255 };
    SDL_Rect textRect2 = { 550,125,300,300 };

    SDL_Surface* textSurface3 = nullptr;
    SDL_Texture* textTexture3 = nullptr;
    SDL_Color colorText3 = { 255,255,255 };
    SDL_Rect textRect3 = { 530,145,300,300 };

    SDL_Surface* surface_background = nullptr;
    SDL_Texture* texture_background = nullptr;

    SDL_Surface* surface_home = nullptr;
    SDL_Texture* texture_home = nullptr;
    SDL_Rect rect_home = { 275,50,692,500 };


};
#endif
