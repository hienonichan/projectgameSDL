#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"

#include"GameObject.h"
#include"Enemy.h"



Enemy::Enemy(std::string id, int x, int y, int w, int h,int framecount,int heal,int type) : GameObject(id, x, y, w, h,framecount) {
	max_health = heal;
	health = max_health;
	id_enemy = type;
	healthbar = new Healthbar("redbar2", position.getX()+10, position.getY()-10, 40,5, 1);
}

void Enemy::draw() {
	GameObject::draw();
	healthbar->draw();
}


void Enemy::update(GameObject*player) {
    healthbar->update(this);
	if (getTextureid() == "fire") {
		set_follow(player);
	}
	else {
		if (sprite == frame-1&&textureID=="enemy"+std::to_string(id_enemy)+"attack") {
			attack_state = false;
		}
		Vector cam = Camera::getInstance()->GetPosition();
		if (abs((position-cam).length() - (player->getPos()-cam).length()) <= 10) {
			attack_state = true;
			velocity = Vector(0, 0);
			change_speedsprite(150);
			changeTexture("enemy" + std::to_string(id_enemy) + "attack", 10);
	     }
		else{
			if (attack_state == false) {
				changeTexture("enemy"+std::to_string(id_enemy), 10);
				set_follow(player);
				change_speedsprite(100);
			}
		}
	}
	GameObject::update();
}

void Enemy::clean() {
	healthbar->clean();
	GameObject::clean();
}



