#ifndef __MapObject__
#define __MapObject__
#include<SDL.h>
#include<SDL_image.h>
const int map_width = 80;
const int map_height = 40;


class Map {
public:
	Map();
	~Map() { ; }

	void LoadMap(int arr[map_height][map_width]);
	void DrawMap();

private:
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture * grass;
	SDL_Texture* water;
	SDL_Texture* rock;

	int map[map_height][map_width];
};

#endif
