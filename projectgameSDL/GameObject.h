#ifndef __GameObject__
#define __GameObject__

#include<SDL.h>
#include<SDL_image.h>
#include<string>
class GameObject {
public:
	GameObject(std::string id, int x, int y, int w, int h);
	void draw();
	void update();
	void clean();


protected:
	int xpos;
	int ypos;

	int width;
	int height;

	std::string textureID;
};
#endif
