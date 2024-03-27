#ifndef __GameObject__
#define __GameObject__

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"Vector.h"
#include"Point.h"

class GameObject {
public:
	GameObject(std::string id, int x, int y, int w, int h,int framecount);
	virtual void draw();
	virtual void update();
	virtual void clean();
	

	void changeTexture(std::string id,int framecount) { 
		frame = framecount;
		textureID = id;
	}
	void changeW(int w) {
		width=w;
	}
	void changeH(int h) {
		height = h;
	}
	

	Vector getPos() { return position; }
	Vector getVelocity() { return velocity; }
	int getW() { return width; }
	int getH() { return height; }

	Point* GetOrigin() { return origin; }

	void change_speedsprite(int speed) {
		speed_sprite = speed;
	}

	int CheckFlip();
    
	

protected:
	Vector position;
	Vector velocity;

	int width;
	int height;

	int sprite;
	int frame;

	std::string textureID;

	int speed_sprite = 100;

	Point* origin;
	SDL_RendererFlip check_flip = SDL_FLIP_NONE;
	bool check_death = false;
};
#endif
