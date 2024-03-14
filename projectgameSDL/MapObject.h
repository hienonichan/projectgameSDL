#ifndef __MapObject__
#define __MapObject__
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
const int map_width = 80;
const int map_height = 40;


class Map {
public:
	static Map* getInstance() {
		if (instance == 0) {
			instance = new Map();
			return instance;
		}
		return instance;
	}


	~Map() { ; }

	void LoadMap(int arr[map_height][map_width]);
	void DrawMap();

	void changeMap(int idMap);

private:
	Map();
	static Map* instance;
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture * grass;
	SDL_Texture* water;
	SDL_Texture* rock;

	int map[map_height][map_width];
};

#endif
