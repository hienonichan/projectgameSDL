#ifndef __MapObject__
#define __MapObject__
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<map>
#include<SDL_mixer.h>
#include"GameObject.h"
#include<vector>
#include<sstream>
#include"fstream"
const int map_width = 80;
const int map_height = 40;

const int tileset_width = 19;
const int tileset_height = 45;
const int tileset_width2 = 20;
const int tileset_height2 = 20;

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

	void LoadMap(std::string arr_layer1 , std::string arr_layer2);
	void DrawMap();
	void changeMap(int idMap);
	bool MapCollision(GameObject*player);
	 
	std::vector<std::vector<int>>stringToArray(std::string s);

	void changeidmap(int idmap){
		id = idmap;
	}

private:
	Map();
	static Map* instance;
	std::vector<std::vector<int>> map_layer1;
	std::vector<std::vector<int>>map_layer2;
	/*int map_layer1[map_height][map_width];
	int map_layer2[map_height][map_width];*/
	int tileset[tileset_height][tileset_width];
	int tileset2[tileset_height2][tileset_width2];
	std::map<int, std::pair<int, int>>mp;
	std::map<int, std::pair<int, int>>mp2;

	int tileSize = 32;
	int id = 0;
};

#endif
