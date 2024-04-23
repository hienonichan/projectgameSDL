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

	const int q_cooldown = 3000;
	const int e_cooldown = 10000;
};
#endif