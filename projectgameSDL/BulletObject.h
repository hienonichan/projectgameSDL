#ifndef __BulletObject__
#define __BulletObject__
#include"GameObject.h"
#include<SDL.h>
#include<SDL_image.h>
#include<string>
class Bullet:public GameObject {
public:
	Bullet(std::string id,int x, int y, int w, int h, int framecount);

	void draw();
	void update();
	void clean();
	void fireBullet(GameObject*crosshair) {
		Vector bonus(crosshair->getW()/2, crosshair->getH()/2);
		velocity =  crosshair->getPos() +bonus- position;
		velocity.setLength1();
		velocity *= 3;
	}


private:
};
#endif