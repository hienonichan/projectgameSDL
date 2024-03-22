#ifndef __SetupState__
#define __SetupState__

#include"State.h"
#include"GameObject.h"
#include<vector>
#include<SDL_ttf.h>
#include<SDL.h>
#include"GameControl.h"
#include"MapObject.h"
class SetupState :public State {

public:
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();


	virtual int getStateCode() { return code; }
private:
	int code = 4;
	
	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr;
	SDL_Color colorText = { 255,255,255 };
	SDL_Rect textRect = { 250,100,300,300 };

	SDL_Surface* textSurface1 = nullptr;
	SDL_Texture* textTexture1 = nullptr;
	SDL_Color colorText1 = { 255,255,255 };
	SDL_Rect textRect1 = { 300,250,300,300 };

	SDL_Surface* textSurface2 = nullptr;
	SDL_Texture* textTexture2 = nullptr;
	SDL_Color colorText2 = { 255,255,255 };
	SDL_Rect textRect2 = { 800,250,300,300 };
	std::vector<GameObject*>gameObjects;

	static void map1ToPlay();
	static void map2ToPlay();

	SDL_Surface* surface_background = nullptr;
	SDL_Texture* texture_background = nullptr;

};
#endif