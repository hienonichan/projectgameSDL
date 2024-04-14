#include"BulletObject.h"


Bullet::Bullet(std::string id,int x,int y,int w,int h,int framecount,int bulletdame):GameObject(id,x,y,w,h,framecount){
	bullet_dame = bulletdame;
}

void Bullet::draw() {
	GameObject::draw();
}

void Bullet::update() {
	//sprite = int(SDL_GetTicks() / speed_sprite) % frame;
	GameObject::update();
}

void Bullet::clean() {
	GameObject::clean();
}

void Bullet::fireBullet(GameObject* crosshair) {
		Vector bonus(crosshair->getW() / 2, crosshair->getH() / 2);
		velocity = crosshair->getPos() + bonus - position;
		velocity.setLength1();
		velocity *= 5;
}

void Bullet::fireBulletup(GameObject* crosshair, float angle) {
	Vector bonus(crosshair->getW() / 2, crosshair->getH() / 2);
	Vector ahead = crosshair->getPos() + bonus - position;
	float rad = angle * M_PI / 180.0f;
	velocity.setX(ahead.getX() * cos(rad) - ahead.getY() * sin(rad));
	velocity.setY(ahead.getX() * sin(rad) + ahead.getY() * cos(rad));

	velocity.setLength1();
	velocity *= 5;
}

void Bullet::updateSpin(GameObject*player,double r) {
	sprite = int(SDL_GetTicks() / 100) % frame;
	Vector cam = Camera::getInstance()->GetPosition();
	float rad = angle * M_PI / 180.0f;
	position.setX(player->getPos().getX() - cam.getX() + r * cos(rad));
	position.setY(player->getPos().getY() - cam.getY() + r * sin(rad));
	angle += 2;
}


void Bullet::explosion() {
	Vector cam = Camera::getInstance()->GetPosition();
	sprite = 0;
	changeTexture("explosion", 8);
	change_speedsprite(100);
	velocity = Vector(0, 0);
	position += cam;
	changeW(32);
	changeH(32);
}






