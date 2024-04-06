#include"BulletObject.h"


Bullet::Bullet(std::string id,int x,int y,int w,int h,int framecount):GameObject(id,x,y,w,h,framecount){
	
}

void Bullet::draw() {
	GameObject::draw();
}

void Bullet::update() {
	sprite = int(SDL_GetTicks() / 100) % frame;
	GameObject::update();
}

void Bullet::clean() {
	GameObject::clean();
}

void Bullet::fireBullet(GameObject* crosshair) {
		Vector bonus(crosshair->getW() / 2, crosshair->getH() / 2);
		velocity = crosshair->getPos() + bonus - position;
		velocity.setLength1();
		velocity *= 10;
}

void Bullet::fireBulletup(GameObject* crosshair, float angle) {
	Vector bonus(crosshair->getW() / 2, crosshair->getH() / 2);
	Vector ahead = crosshair->getPos() + bonus - position;
	float rad = angle * M_PI / 180.0f;
	velocity.setX(ahead.getX() * cos(rad) - ahead.getY() * sin(rad));
	velocity.setY(ahead.getX() * sin(rad) + ahead.getY() * cos(rad));

	velocity.setLength1();
	velocity *= 10;
}

void Bullet::updateSpin(GameObject*player,double r) {
	sprite = int(SDL_GetTicks() / 100) % frame;
	Vector cam = Camera::getInstance()->GetPosition();
	float rad = angle * M_PI / 180.0f;
	position.setX(player->getPos().getX() - cam.getX() + r * cos(rad));
	position.setY(player->getPos().getY() - cam.getY() + r * sin(rad));
	angle += 2;
}