#ifndef __Player__
#define __Player__

#include<SDL.h>
#include"GameObject.h"
#include<string>
#include"GameOver.h"
#include"Skill.h"
#include"Healthbar.h"

class Player :public GameObject {
public:
	Player(std::string id,int x,int y,int w,int h,int framecount);
	void draw();
	void update();
	void clean();

	void death();

	int getHealth() { return health; }
	int getMaxHealth() { return max_health; }
	void lowHealth(int dame) {
		health -= dame;
	}
	int getAttack() { return attack; }
	void buffAttack(int dame) { attack += dame; }
	void buffHealth(int buff) { health += buff; }

private:
	Skill* skill_q = nullptr;
	Skill* skill_e = nullptr;

    int max_health = 200;
	int health = max_health;
	int attack = 1; 

	Healthbar* healthbar = nullptr;
}; 


#endif