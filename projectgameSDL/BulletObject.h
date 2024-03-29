#ifndef __BulletObject__
#define __BulletObject__
#include"GameObject.h"
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"Camera.h"
class Bullet:public GameObject {
public:
	Bullet(std::string id,int x, int y, int w, int h, int framecount);
	void draw();
	void update();
	void clean();
	void fireBullet(GameObject* crosshair);
	void fireBulletup(GameObject* crosshair, float angle);

	void updateSpin(GameObject*player,double r);
private:
	

	double angle = 0;
};
#endif