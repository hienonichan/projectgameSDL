#ifndef __Skill__
#define __Skill__
#include"GameObject.h"
#include<vector>
#include<string>
#include"InputChecker.h"
#include"GameControl.h"
#include"BulletObject.h"


class Skill :public GameObject {
public:
	Skill(std::string id, int x, int y, int w, int h, int framecount,char type);
	void update(GameObject*player);
	void draw();
	void clean();
	bool cool_down(int cooldown);

	void sword_energy(GameObject*player);
private:
	char skill_type;
	bool turn_on = true;
	int next = 0;

	Bullet* left = nullptr;
	Bullet* right = nullptr;
	Bullet* up = nullptr;
	Bullet* down = nullptr;
	
	
};
#endif