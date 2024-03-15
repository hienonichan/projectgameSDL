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
	virtual void drawchar();

	void changeTexture(std::string id,int framecount) { 
		frame = framecount;
		textureID = id;
	}

	Vector getPos() { return position; }
	Vector getVelocity() { return velocity; }
	int getW() { return width; }
	int getH() { return height; }

	Point* GetOrigin() { return origin; }

	int CheckFlip();

protected:
	Vector position;
	Vector velocity;

	int width;
	int height;

	int sprite;
	int frame;

	std::string textureID;


	Point* origin;

};
#endif
