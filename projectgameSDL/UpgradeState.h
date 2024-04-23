#ifndef __UpgradeState__
#define __UpgradeState__
#include"State.h"
#include<vector>
#include"GameObject.h"
#include"GameButton.h"


class UpgradeState :public State {
public:
	virtual void update();
	virtual void render();

	virtual bool loadState();
	virtual bool exitState();

	int getStateCode(){ return code; }

	int rand_card() { return rand() % 2 + 1; }
private:
	int code = 5;
	std::vector<GameObject*>gameObjects;
	static void upgrade_health();
	static void upgrade_attack();
	static void upgrade_ammo();
	static void summon_bullet();
	static void shotbullet3();
	static void shotbullet5();

	SDL_Surface*background_surface = nullptr;
	SDL_Texture* background_texture = nullptr;

	SDL_Surface* textSurface = nullptr;
	SDL_Texture* textTexture = nullptr; 
	SDL_Color colorText = { 255,255,255 };
	SDL_Rect textRect = { 250,100,300,300 };
};
#endif
