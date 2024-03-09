#ifndef __GameObject__
#define __GameObject__

#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include"Vector.h"
class GameObject {
public:
	GameObject(std::string id, int x, int y, int w, int h,int framecount);
	void draw();
	void update();
	void clean();


protected:
	Vector position;
	Vector velocity;

	int width;
	int height;

	int sprite;
	int frame;

	std::string textureID;

};
#endif
