#ifndef __MapObject__
#define __MapObject__
#include<SDL.h>
#include<SDL_image.h>
class Map {
public:
	Map();
	~Map() { ; }

	void LoadMap(int arr[20][40]);
	void DrawMap();

private:
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture * grass;
	SDL_Texture* water;

	int map[20][40];
};

#endif
