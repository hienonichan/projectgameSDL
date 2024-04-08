#include"Boss.h"
#include"GameControl.h"
#include<vector>
#include"PlayState.h"

Boss::Boss(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){}

// bien check boss da awake chua
bool awake = false;
// bien delay giua 2 lan attack
int next_attack = 0;
void Boss::update(GameObject*player) {
	Vector cam = Camera::getInstance()->GetPosition();
	double distance = abs(((position-cam).length()-(player->getPos()-cam).length()));
	if (distance <= 200) {
		awake = true;
	}
	if (awake) {
		int time = SDL_GetTicks();
		if (time - next_attack >= 2000) {
			changeTexture("bossattack", 15);
			change_speedsprite(300);
			velocity = Vector(0, 0);
			
			// chay het sprite chem thi moi chuyen sang walk
			if (sprite == 9) {
				attack();
			}
			if (sprite == 14) {
				next_attack = time; 
			}
		}
		else {
			changeTexture("bosswalk", 12);
			set_follow(player);
		}
	}
	if (!awake) {
		changeTexture("bossidle", 6); 
		velocity = Vector(0, 0);
	}
	GameObject::update();
}


void Boss::attack() {
	std::vector<State*> loi = GameControl::getInstance()->getStateManager()->getVectorState();
	PlayState* temp = static_cast<PlayState*>(loi.back());
	temp->rand_enemy(1);
}

void Boss::draw() {
	sprite = int(SDL_GetTicks() / 100) % frame;
	GameObject::draw();
}

void Boss::clean() {
	GameObject::clean();
}