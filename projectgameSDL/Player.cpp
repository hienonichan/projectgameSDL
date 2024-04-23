#include"Player.h"
#include"GameObject.h"
#include"InputChecker.h"
#include"ObjectTextureManager.h"
#include"MapObject.h"
#include"Camera.h"

SDL_RendererFlip check_flip = SDL_FLIP_NONE;


Player::Player(std::string id, int x, int y, int w, int h,int framecount):GameObject(id,x,y,w,h,framecount) {
	healthbar = new Healthbar("redbar", 56, 26, 168, 12, 1);
	
	skill_q = new Skill("skill_1_on", 1050, 500, 100, 100, 1, 'Q');
	skill_e = new Skill("skill_2_on", 1150, 450, 100, 100, 1, 'E');
	
}

void Player::draw() {
    if(check_death==false){
		if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_D)) {
			check_flip = SDL_FLIP_NONE;
		}
		if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_A)) {
			check_flip = SDL_FLIP_HORIZONTAL;
		}

		if (velocity.getX() == 0 && velocity.getY() == 0) {
			GameObject::changeTexture("playerstand", 5);
			ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer(), check_flip);
		}
		else {
			GameObject::changeTexture("player", 6);
			ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer(), check_flip);
		}
	}
	else {
		ObjectTextureManager::getInstance()->drawAnimation(textureID, (int)position.getX(), (int)position.getY(), width, height, sprite, GameControl::getInstance()->getRenderer(), check_flip);
	}
	skill_q->draw();
	skill_e->draw();
	healthbar->draw();
}

bool check = true;

void Player::update() {
	if (health <= 0) {
		health = 0;
		death();
	 }
	skill_q->update(this);
	skill_e->update(this);

	if (Map::getInstance()->MapCollision(this)) {
		check = false;
		while (Map::getInstance()->MapCollision(this)) {
			velocity *= -1;
			GameObject::update();
		}
		check = true;
	}
	if (check) {
		velocity.setX(0);
		velocity.setY(0);

		if (check_death == false) {
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_A)) {
				velocity.setX(-2);
			}
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_D)) {
				velocity.setX(2);
			}
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_W)) {
				velocity.setY(-2);
			}
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_S)) {
				velocity.setY(2);
			}
		}
	}
	// lay tam nhan vat
	origin->x = position.getX() +width / 2;
	origin->y = position.getY() + height / 2;

	healthbar->update(this);
	GameObject::update();
	
}

void Player::clean() {
	healthbar->clean();
	GameObject::clean();
}

void Player::death() {
	check_death = true;
	changeTexture("playerdeath", 8);
	change_speedsprite(250);
	std::cout << sprite << std::endl;
	if (sprite == 7) {
		GameControl::getInstance()->getStateManager()->addState(new GameOver());
	}
}

