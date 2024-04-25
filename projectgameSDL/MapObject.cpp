#include"MapObject.h"
#include"ObjectTextureManager.h"
#include"GameControl.h"
#include<iostream>


Map* Map::instance = 0;






std::string encodeMap1_layer1= "";
std::string encodeMap1_layer2 = "";



Map::Map() {

	

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source_picture/tileset map.png", "tileset", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source_picture/tileset2.png", "tileset2", GameControl::getInstance()->getRenderer());
	int z = 1;
	for (int i = 0; i < tileset_height; i++) {
		for (int j = 0; j < tileset_width; j++) {
			mp[z] = std::make_pair(j * 32, i * 32);
			z++;
		}
	}

	int k = 1;
	for (int i = 0; i <tileset_height2; i++) {
		for (int j = 0; j <tileset_width2; j++) {
			mp2[k] = std::make_pair(j * 32, i * 32);
			k++;
		}
	}


	std::cout << "load map\n";
}

void Map::changeMap(int idMap) {
	
	if (idMap == 1) {
		encodeMap1_layer1 = "";
		encodeMap1_layer2 = "";
		changeidmap(1);
		std::ifstream fin;
		fin.open("C:/projectgameSDL/projectgameSDL/map/map1/mp_layer1.txt");
		std::string temp;
		while (fin >> temp) {
			encodeMap1_layer1 += temp;
		}
		fin.close();
		fin.open("C:/projectgameSDL/projectgameSDL/map/map1/mp_layer2.txt");
		std::string temp2;
		while (fin >> temp2) {
			encodeMap1_layer2 += temp2;
		}
		fin.close();
	}
	else if (idMap == 2) {
		encodeMap1_layer1 = "";
		encodeMap1_layer2 = "";
		changeidmap(2);
		std::ifstream fin;
		fin.open("C:/projectgameSDL/projectgameSDL/map/map2/map2_layer1.txt");
		std::string temp;
		while (fin >> temp) {
			encodeMap1_layer1 += temp;
		}
		fin.close();
		fin.open("C:/projectgameSDL/projectgameSDL/map/map2/map2_layer2.txt");
		std::string temp2;
		while (fin >> temp2) {
			encodeMap1_layer2 += temp2;
		}
		fin.close();
	}
	LoadMap(encodeMap1_layer1, encodeMap1_layer2);
}



void Map::LoadMap(std::string arr_layer1, std::string arr_layer2) {
	map_layer1 = stringToArray(arr_layer1);
	map_layer2 = stringToArray(arr_layer2);
}


void Map::DrawMap() {
	if (id == 1) {
		for (int row = 0; row < map_height; row++) {
			for (int col = 0; col < map_width; col++) {
				ObjectTextureManager::getInstance()->drawTile("tileset", col * tileSize, row * tileSize, mp[map_layer1[row][col]].first, mp[map_layer1[row][col]].second, 32, 32, GameControl::getInstance()->getRenderer());
			}
		}

		for (int row = 0; row < map_height; row++) {
			for (int col = 0; col < map_width; col++) {
				ObjectTextureManager::getInstance()->drawTile("tileset", col * tileSize, row * tileSize, mp[map_layer2[row][col]].first, mp[map_layer2[row][col]].second, 32, 32, GameControl::getInstance()->getRenderer());
			}
		}
	}
	else {
		for (int row = 0; row < map_height; row++) {
			for (int col = 0; col < map_width; col++) {
				ObjectTextureManager::getInstance()->drawTile("tileset2", col * tileSize, row * tileSize, mp2[map_layer1[row][col]].first, mp2[map_layer1[row][col]].second, 32, 32, GameControl::getInstance()->getRenderer());
			}
		}

		for (int row = 0; row < map_height; row++) {
			for (int col = 0; col < map_width; col++) {
				ObjectTextureManager::getInstance()->drawTile("tileset2", col * tileSize, row * tileSize, mp2[map_layer2[row][col]].first, mp2[map_layer2[row][col]].second, 32, 32, GameControl::getInstance()->getRenderer());
			}
		}
	}
}

bool Map::MapCollision(GameObject*player) {
	int x = player->getPos().getX() / tileSize+1;
	int y = player->getPos().getY() / tileSize+1;
	
	if (x <=0 || y <=0||x>=map_width||y>=map_height) {
		return true;
	}
	else if (map_layer2[y][x] != 0) {
		return true;
	}
	return false;
}



std::vector<std::vector<int>> Map::stringToArray(std::string s) {
	for (int i = 0; i < s.size(); i++) {
		if(s[i]==','){
			s[i] = ' ';
		}
	}
	std::stringstream ss(s);
	std::string hehe;
	std::vector<std::string>word;
	while (ss >> hehe) {
		word.push_back(hehe);
	}

	std::vector<std::vector<int>>v;
	int l = 0;
	for (int i = 0; i <map_height; i++) {
		std::vector<int>loi;
		for (int j = 1; j <= map_width; j++) {
			loi.push_back(stoi(word[l]));
			l++;
		}
		v.push_back(loi);
	} 
	return v;
}