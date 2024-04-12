#include"Player.h"
#include"GameObject.h"
#include"InputChecker.h"
#include"ObjectTextureManager.h"
#include"MapObject.h"
#include"Camera.h"
SDL_RendererFlip check_flip = SDL_FLIP_NONE;


Player::Player(std::string id, int x, int y, int w, int h,int framecount):GameObject(id,x,y,w,h,framecount) {
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
}

bool check = true;

void Player::update() {

	skill_q->update();
	skill_e->update();

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
				velocity.setX(-3);
			}
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_D)) {
				velocity.setX(3);
			}
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_W)) {
				velocity.setY(-3);
			}
			if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_S)) {
				velocity.setY(3);
			}
		}
	}
	// lay tam nhan vat
	origin->x = position.getX() +width / 2;
	origin->y = position.getY() + height / 2;
	  
	//sprite = int(SDL_GetTicks() /speed_sprite) % frame;
	
	GameObject::update();
}

void Player::clean() {
	GameObject::clean();
}

void Player::death() {
	check_death = true;
	changeTexture("playerdeath", 8);
	change_speedsprite(250);
	update();
	draw();
	if (sprite == 7) {
		GameControl::getInstance()->getStateManager()->addState(new GameOver());
	}
}

