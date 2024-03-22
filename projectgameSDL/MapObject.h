#ifndef __MapObject__
#define __MapObject__
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<map>
#include<SDL_mixer.h>
const int map_width = 80;
const int map_height = 40;

const int tileset_width = 19;
const int tileset_height = 45;
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
	int map[map_height][map_width];
	int tileset[tileset_height][tileset_width];

	std::map<int, std::pair<int, int>>mp;
};

#endif
