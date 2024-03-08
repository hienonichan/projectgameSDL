#ifndef __GameObject__
#define __GameObject__

#include<SDL.h>
#include<SDL_image.h>
#include<string>
class GameObject {
public:
	GameObject(){}

	void load(std::string id, int x, int y, int w, int h);
	void draw();
	void update();
	void clean();



private:
	int xpos;
	int ypos;
	int width;
	int height;

	std::string textureID;
};
#endif
