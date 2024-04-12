#include"PlayState.h"
#include<iostream>
#include"GameControl.h"
#include"Player.h"
#include"ObjectTextureManager.h"
#include"Enemy.h"
#include"InputChecker.h"
#include"DelayState.h"
#include"MapObject.h"
#include"Camera.h"
#include"Aim.h"
#include"CollisionChecker.h"
#include"GameOver.h"
#include"GameItem.h"
#include"UpgradeState.h"
#include"Healthbar.h"
TTF_Font* font = nullptr;
TTF_Font* font2 = nullptr;
TTF_Font* font3 = nullptr;
TTF_Font* font4 = nullptr;
TTF_Font* font5 = nullptr;

int chua_trung = 0;
int dan_trung = 1;
int dan_xoay = 2;
int dan_no = 3;


// cac bien dieu khien ham random
int ran_num = 0;
int next_create = 0;
int next_create2 = 0;
bool check_ran = false;

// cac bien dieu khien sinh bullet
int next_bullet = 0;
int next_bullet2 = 0;
int next_bullet3 = 0;
int next_reload = 0;
GameObject* crosshair = nullptr;

// thong so cua dan
std::string bullet_id = "bullet";
int bullet_w = 19;
int bullet_h = 19;
int bullet_dame=1;
int bullet_frame = 1;

// dieu kien upgrade
int current_score=0;
int next_score=0;

void PlayState:: rand_enemy(int type) {
	ran_num = ran();
	if (ran_num) {
		check_ran = true;
	}
	if (type == 1) {
		if (check_ran) {
			int time = SDL_GetTicks();
			if (time - next_create2 >= 300) {
				Vector cam = Camera::getInstance()->GetPosition();
				enemys.push_back(new Enemy("fire",bosses.back()->getPos().getX(), bosses.back()->getPos().getY(), 78, 120, 8,1));
			}
			check_ran = false;
			next_create2 = time;
		}
	}
	else {
		if (check_ran) {
			int time = SDL_GetTicks();
			if (time - next_create >= 2000) {
				if (ran_num <= 1400) {
					enemys.push_back(new Enemy("enemy", ran_num, ran_num, 100, 80, 8,5));
				}
				else if (ran_num <= 1900) {
					enemys.push_back(new Enemy("enemy2", ran_num, ran_num, 60, 60, 7,3));
				}
				check_ran = false;
				next_create = time;
			}
		}
	}
}


void PlayState::update() {

	//std::cout << bullets.size() << std::endl;

	Map::getInstance()->MapCollision(player1);

	// random tao enemy 
	rand_enemy(2);
	
	// het mau chuyen sang GameOver
	if (health == 0) {
		static_cast<Player*>(player1)->death();
	}

     next_score = score;
	if (next_score - current_score >= 100) {
		current_score = next_score;
		GameControl::getInstance()->getStateManager()->addState(new UpgradeState());
	}

	// nap dan 
	if (checkReload()) {
		reload();
	}
	// ban bang crosshair 1 vien
	if (InputChecker::getInstance()->checkClicked(LEFT) == true) {
		if (mode_shot == 3) {
			shot3();
		}
		// ban ba vien
		else if (mode_shot == 1) {
			shot1();
		}
		else {
			shot5();
		}
	}
	// check item sau do change bullet
	for (int i = 0; i < items.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(items[i], player1)) {
			check_item[items[i]] = 1;
			int ran_id = ran() % 4;
			if (ran_id == 0) {
				bullet_id = "bullet";
				bullet_w = bullet_h = 20;
				bullet_frame = 1;
				
			}
			else if (ran_id == 1) {
				bullet_id = "bullet2";
				bullet_h = 25;
				bullet_w = 32;
				bullet_frame = 6;
				
			}
			else if (ran_id == 2) {
				bullet_id = "bullet3";
				bullet_h = 25;
				bullet_w = 31;
				bullet_frame = 6;
				
			}
			else {
				bullet_id = "bullet4";
				bullet_h = 25;
				bullet_w = 32;
				bullet_frame = 6;
				
			}
		}
	}
	// goi lop check bullet ban trung enemy
	for (int i = 0; i < bullets.size(); i++) {
		for (int j = 0; j < enemys.size(); j++) {
			if (CollisionChecker::getInstance()->CollisionBullet(enemys[j], bullets[i])) {
				if (enemys[j]->getHealth() <= 0) {
					score++;
					// danh dau enemy chet
					check_enemy[enemys[j]] = 1;
					// cap nhat texture Score
					render_score();
				}
				else {
					enemys[j]->lowHealth(bullet_dame);
				}
				check_bullet[bullets[i]] = 3;
				bullets[i]->explosion();
			}
		}


		// check ban trung boss
		for (int z = 0; z < bosses.size(); z++) {
			if (CollisionChecker::getInstance()->CollisionBullet(bosses[z], bullets[i])) {
				if (bosses[z]->getHealth() <= 0) {
					check_boss[bosses[z]] = 1;
					score += 20;
					// neu boss chet thi cap nhat diem
					render_score();
				}
				else {
					bosses[z]->lowHealth(bullet_dame);
				}

				check_bullet[bullets[i]] = 3;
				bullets[i]->explosion();
			}
		}
	}

	// ham clear object toi uu cho game
	clearBullet();
	clearEnemy();
	clearBoss();
	clearItem();


	// neu va cham voi ke dich thi bi tru mau
	// cap nhat texture health
	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(enemys[i], player1)) {
			check_enemy[enemys[i]] = 1;
			Mix_PlayChannel(4, hurtSound, 0);
			health--;
			if (health < 0) {
				health = 0;
			}
			render_health();
		}
	}
	// va cham voi boss
	for (int i = 0; i < bosses.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(bosses[i], player1)) {
			Mix_PlayChannel(4, hurtSound, 0);
			health = 0;
			render_health();
		}
	}
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
	// update cho boss
	for (int i = 0; i < bosses.size(); i++) {
		if (check_boss[bosses[i]] == 0) {
			bosses[i]->update(player1);
		}
	}
	// neu enemy con song thi update
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == 0) {
			enemys[i]->update();
			enemys[i]->set_follow(player1);
		}
	} 
	// neu dan chua trung thi update
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			if (check_bullet[bullets[i]] == 0) {
				bullets[i]->update();
			}
			if (check_bullet[bullets[i]] == 2) {
				bullets[i]->updateSpin(player1, 100);
			}
			if (check_bullet[bullets[i]] == 3) {
				if (bullets[i]->getSprite() < 7) {
					bullets[i]->update();
				}
				else {
					check_bullet[bullets[i]] = 1;
				}
			}
		}
	}
	// update item
	for (int i = 0; i < items.size(); i++) {
		if (check_item[items[i]] == 0) {
			items[i]->update();
		}
	}

	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_ESCAPE)) {
		GameControl::getInstance()->getStateManager()->addState(new DelayState());
	}
	Camera::getInstance()->Update();
}

void PlayState::render() {
	// ve truoc player
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_background, NULL, NULL);
	Map::getInstance()->DrawMap();

	for (int i = 0; i < items.size(); i++) {
		if (check_item[items[i]] == 0) {
			items[i]->draw();
		}
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == 0) {
			enemys[i]->draw();
		}
	}
	for (int i = 0; i < bosses.size(); i++) {
		if (check_boss[bosses[i]] == 0) {
			bosses[i]->draw();
		}
	}

	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			if (check_bullet[bullets[i]] == 0||check_bullet[bullets[i]]==2) {
				bullets[i]->draw();
			}
			if (check_bullet[bullets[i]] == 3) {
				if (bullets[i]->getSprite() < 7) {
					bullets[i]->draw();
				}
			}
		}
	}
	
	
	// cap nhat hien score len man hinh
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture2, NULL, &textRect2);
	// cap nhat health len man hinh
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture3, NULL, &textRect3);
	// cap nhat ammo
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture4, NULL, &textRect4);
}



bool PlayState::loadState() {
	
	// phat am thanh
	Mix_VolumeChunk(sound1, MIX_MAX_VOLUME / 4);
	PlayMusic();

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider run.png", "player",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/zom2.png", "enemy", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider stand.png", "playerstand", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/bullet.png", "bullet", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/bullet2.png", "bullet2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/bullet3.png", "bullet3", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/bullet4.png", "bullet4", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/enemy2.png", "enemy2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/crosshair.png", "crosshair", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/boss.png","boss",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/item.png", "item", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider death.png","playerdeath", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/boss walk.png", "bosswalk", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/boss attack.png", "bossattack", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/boss idle.png", "bossidle", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/fire.png", "fire", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/explosion.png", "explosion", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/red bar.png", "redbar", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/q_circle_on.png", "skill_1_on", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/q_circle_off.png", "skill_1_off", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/e_circle_on.png", "skill_2_on", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/e_circle_off.png", "skill_2_off", GameControl::getInstance()->getRenderer());

	player1 = new Player("player", 700, 500, 60, 60, 6);
	 crosshair = new Aim("crosshair", 100, 100, 150, 150, 1);
	gameObjects.push_back(player1);
	gameObjects.push_back(crosshair);


	bosses.push_back(new Boss("bossidle", 1200, 500, 288, 160, 6));

	for (int i = 1; i <= 20; i++) {
		items.push_back(new GameItem("item",ran() , ran() , 32, 32, 1));
	}


	std::string background = "C:/projectgameSDL/projectgameSDL/background play.png";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);

	// lay player lam trung tam camera
	Camera::getInstance()->SetTarget(player1->GetOrigin());
	// tai score len goc trai
	font2 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 30);
	render_score();
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);
	// tai chu health
	font3 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 25);
	render_health();
	SDL_QueryTexture(textTexture3, NULL, NULL, &textRect3.w, &textRect3.h);
	// tai chu ammo
	font4 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 25);
	render_ammo();
	SDL_QueryTexture(textTexture4, NULL, NULL, &textRect4.w, &textRect4.h);

	std::cout << "loading playState\n";
	return true;
}

bool PlayState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();
	ObjectTextureManager::getInstance()->eraseTexture("player");
	ObjectTextureManager::getInstance()->eraseTexture("enemy");
	ObjectTextureManager::getInstance()->eraseTexture("playerstand");
	ObjectTextureManager::getInstance()->eraseTexture("bullet");
	ObjectTextureManager::getInstance()->eraseTexture("bullet2");
	ObjectTextureManager::getInstance()->eraseTexture("bullet3");
	ObjectTextureManager::getInstance()->eraseTexture("bullet4");
	ObjectTextureManager::getInstance()->eraseTexture("playerdeath");
	ObjectTextureManager::getInstance()->eraseTexture("bosswalk");
	ObjectTextureManager::getInstance()->eraseTexture("bossattack");
	ObjectTextureManager::getInstance()->eraseTexture("bossidle");
	ObjectTextureManager::getInstance()->eraseTexture("explosion");
	ObjectTextureManager::getInstance()->eraseTexture("fire");
	ObjectTextureManager::getInstance()->eraseTexture("redbar");
	ObjectTextureManager::getInstance()->eraseTexture("skill_1_on");
	ObjectTextureManager::getInstance()->eraseTexture("skill_1_off");
	ObjectTextureManager::getInstance()->eraseTexture("skill_2_on");
	ObjectTextureManager::getInstance()->eraseTexture("skill_2_off");
	
	SDL_FreeSurface(textSurface2);
	SDL_FreeSurface(textSurface3);
	SDL_FreeSurface(textSurface4);
	SDL_FreeSurface(surface_background);

	
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(textTexture3);
	SDL_DestroyTexture(textTexture4);
	SDL_DestroyTexture(texture_background);


	Mix_FreeChunk(sound1);
	Mix_FreeChunk(shootingsound);
	Mix_FreeChunk(hurtSound);
	Mix_FreeChunk(reloadSound);

	std::cout << "exting playState\n";
	return true;
}

void PlayState::up_attack() {
	bullet_dame += 2;
}
void PlayState::up_health() {
	health += 2;
}
void PlayState::up_ammo() {
	max_ammo += 2;
}
void PlayState:: render_health() {
	SDL_FreeSurface(textSurface3);
	SDL_DestroyTexture(textTexture3);
	textSurface3 = TTF_RenderText_Blended(font3, ("HEALTH:" + std::to_string(health)).c_str(), colorText3);
	textTexture3 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface3);
}
void PlayState::render_ammo() {
	SDL_FreeSurface(textSurface4);
	SDL_DestroyTexture(textTexture4);
	textSurface4 = TTF_RenderText_Blended(font4, ("AMMO: " + std::to_string(ammo_count)).c_str(), colorText4);
	textTexture4 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface4);
}
void PlayState::render_score() {
	SDL_FreeSurface(textSurface2);
	SDL_DestroyTexture(textTexture2);
	textSurface2 = TTF_RenderText_Blended(font2, ("SCORE: " + std::to_string(score)).c_str(), colorText2);
	textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
}
void PlayState::reload() {
	int time = SDL_GetTicks();
	if (time - next_reload >= 100) {
		if (ammo_count < max_ammo) {
			Mix_PlayChannel(5, reloadSound, 0);
			ammo_count++;
		}
		render_ammo();
		next_reload = time;
	}
}
void PlayState::shot1() {
	int time = SDL_GetTicks();
	if (time - next_bullet >= 150) {
		Vector cam = Camera::getInstance()->GetPosition();
		if (ammo_count >= 1) {
			bullets.push_back(new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame));
			bullets.back()->fireBullet(crosshair);
			ammo_count--;
			Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME / 3);
			Mix_PlayChannel(3, shootingsound, 0);
			next_bullet = time;
			render_ammo();
		}
	}
}
void PlayState::shot3() {
	int time = SDL_GetTicks();
	if (time - next_bullet2 >= 200) {
		Vector cam = Camera::getInstance()->GetPosition();
		Bullet* bullet2 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		Bullet* bullet3 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		Bullet* bullet4 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		if (ammo_count >= 3) {
			ammo_count -= 3;
			bullet2->fireBullet(crosshair);
			bullet3->fireBulletup(crosshair, 10);
			bullet4->fireBulletup(crosshair, -10);
			bullets.push_back(bullet2);
			bullets.push_back(bullet3);
			bullets.push_back(bullet4);
			Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME / 3);
			Mix_PlayChannel(3, shootingsound, 0);
			next_bullet2 = time;
			render_ammo();
		}
	}
}
void PlayState::shot5() {
	int time = SDL_GetTicks();
	if (time - next_bullet3>=300) {
		Vector cam = Camera::getInstance()->GetPosition();
		Bullet* bullet = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		Bullet* bullet2 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		Bullet* bullet3 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		Bullet* bullet4 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		Bullet* bullet5 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
		if (ammo_count >= 5) {
			ammo_count -= 5;
			bullet->fireBullet(crosshair);
			bullet2->fireBulletup(crosshair, 10);
			bullet3->fireBulletup(crosshair, -10);
			bullet4->fireBulletup(crosshair, 15);
			bullet5->fireBulletup(crosshair, -15);
			bullets.push_back(bullet);
			bullets.push_back(bullet2);
			bullets.push_back(bullet3);
			bullets.push_back(bullet4);
			bullets.push_back(bullet5);
			Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME / 3);
			Mix_PlayChannel(3, shootingsound, 0);
			next_bullet3= time;
			render_ammo();
		}
	}
}
void PlayState::summon() {
	Vector cam = Camera::getInstance()->GetPosition();
	Bullet* bullet = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
	Bullet* bullet2 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame);
	check_bullet[bullet] = 2;
	check_bullet[bullet2] = 2;
	bullets.push_back(bullet);
	bullets.push_back(bullet2);
}