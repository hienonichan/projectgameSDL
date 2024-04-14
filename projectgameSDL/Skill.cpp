#include"Skill.h"
#include"Camera.h"
#include"PlayState.h"

Skill::Skill(std::string id,int x,int y,int w,int h,int framecount,char type):GameObject(id,x,y,w,h,framecount){
	skill_type = type;
	velocity = Vector(0,0);
}

void Skill::update(GameObject*player) {
	if (skill_type == 'Q') {
		if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_Q)&&turn_on==true) {
			changeTexture("skill_1_off", 1);  
			turn_on = false;
			next = SDL_GetTicks();
			sword_energy(player);
		}
		if (cool_down(500)) {
			turn_on = true;
			changeTexture("skill_1_on", 1);
		}
	}
	else if (skill_type == 'E') {
		if(InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_E) && turn_on == true) {
			changeTexture("skill_2_off", 1);
			turn_on = false;
			next = SDL_GetTicks();
			std::vector<State*>temp = GameControl::getInstance()->getStateManager()->getVectorState();
			static_cast<PlayState*>(temp.back())->summon();
		}
		if (cool_down(1000)) {
			turn_on = true;
			changeTexture("skill_2_on", 1);
		}
	}
    
	GameObject::update();
	if (left != nullptr && right != nullptr && up != nullptr && down != nullptr) {
		left->update();
		right->update();
		up->update();
		down->update();
	}
}


void Skill::draw() {
	GameObject::draw();
	if (left != nullptr && right != nullptr && up != nullptr && down != nullptr) {
		left->draw();
		right->draw();
		up->draw();
		down->draw();
	}
}

void Skill::clean() {
	GameObject::clean();
}

bool Skill::cool_down(int cooldown) {
	int time = SDL_GetTicks();
	if (time - next >=cooldown) {
		return true;
	}
	return false;
}

void Skill::sword_energy(GameObject* player) {
	std::vector<State*> loi = GameControl::getInstance()->getStateManager()->getVectorState();
	static_cast<PlayState*>(loi.back())->sword_energy_skill();
}