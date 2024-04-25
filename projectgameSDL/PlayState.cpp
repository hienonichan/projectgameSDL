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

void PlayState::update() {
	Map::getInstance()->MapCollision(player1);  

	// random tao enemy 
	rand_enemy(2);

     next_score = score;
	if (next_score - current_score >= 40) {
		current_score = next_score;
		GameControl::getInstance()->getStateManager()->addState(new UpgradeState());
	}

	// nap dan 
	if (checkReload()) {
		reload();
	}
	// ban bang crosshair 1 vien
	if (InputChecker::getInstance()->checkClicked(LEFT) == true) {
		if (mode_shot == 3) { shot3();}
		// ban ba vien
		else if (mode_shot == 1) {shot1();}
		else {shot5();}
	}
	// check item sau do change bullet
	for (int i = 0; i < items.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(items[i], player1)) {
			check_item[items[i]] = 1;
			int ran_id = rand() % 4;
			if (ran_id == 0) {
				bullet_id = "bullet";
				bullet_w = bullet_h = 20;
				bullet_frame = 1;
				bullet_dame = 1;
				
			}
			else if (ran_id == 1) {
				bullet_id = "bullet2";
				bullet_h = 25;
				bullet_w = 32;
				bullet_frame = 6;
				bullet_dame = 2;
				
			}
			else if (ran_id == 2) {
				bullet_id = "bullet3";
				bullet_h = 25;
				bullet_w = 31;
				bullet_frame = 6;
				bullet_dame = 4;
				
			}
			else {
				bullet_id = "bullet4";
				bullet_h = 25;
				bullet_w = 32;
				bullet_frame = 6;
				bullet_dame = 10;
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
					check_enemy[enemys[j]] = DIE;
					// cap nhat texture Score
					render_score();
				}
				else {
					enemys[j]->lowHealth(static_cast<Player*>(player1)->getAttack()+bullets[i]->getBulletDame());
				}
				check_bullet[bullets[i]] = BULLET_EXPLOSION;
				bullets[i]->explosion();
			}
		}


		// check ban trung boss
		for (int z = 0; z < bosses.size(); z++) {
			if (CollisionChecker::getInstance()->CollisionBullet(bosses[z], bullets[i])) {
				if (bosses[z]->getHealth() <= 0) {
					check_boss[bosses[z]] = DIE;
					score += 20;
					// neu boss chet thi cap nhat diem
					render_score();
				}
				else {
					bosses[z]->lowHealth(static_cast<Player*>(player1)->getAttack()+bullets[i]->getBulletDame());
				}
				check_bullet[bullets[i]] = BULLET_EXPLOSION;
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
			if (enemys[i]->getTextureid() == "fire") {
				check_enemy[enemys[i]] = DIE;
				static_cast<Player*>(player1)->lowHealth(30);
			}
			else {
				static_cast<Player*>(player1)->lowHealth(1);
			}
			Mix_PlayChannel(4, hurtSound, 0);
		}
	}
	// va cham voi boss
	for (int i = 0; i < bosses.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(bosses[i], player1)) {
			Mix_PlayChannel(4, hurtSound, 0);
			static_cast<Player*>(player1)->lowHealth(static_cast<Player*>(player1)->getHealth());
		}
	}
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
	// update cho boss
	for (int i = 0; i < bosses.size(); i++) {
		if (check_boss[bosses[i]] == ALIVE) {
			bosses[i]->update(player1);
		}
	}
	// neu enemy con song thi update
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == ALIVE) { 
			enemys[i]->update(player1);
		}
	} 
	// neu dan chua trung thi update
	if (!bullets.empty()) {
		for (int i = 0; i < bullets.size(); i++) {
			if (check_bullet[bullets[i]] == BULLET_NOT_HIT) {
				bullets[i]->update();
			}
			if (check_bullet[bullets[i]] == BULLET_CIRCLE) {
				bullets[i]->updateSpin(player1, 100);
			}
			if (check_bullet[bullets[i]] == BULLET_EXPLOSION) {
				if (bullets[i]->getSprite() < 7) {
					bullets[i]->update();
				}
				else {
					check_bullet[bullets[i]] = BULLET_HIT;
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
	
	// cap nhat ammo
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture4, NULL, &textRect4);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), texture_bar, NULL, &rect_bar);

	
}



bool PlayState::loadState() {
	
	// phat am thanh
	Mix_VolumeChunk(sound1, MIX_MAX_VOLUME /20);
	Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME/20);
	Mix_VolumeChunk(hurtSound, MIX_MAX_VOLUME / 20);
	Mix_VolumeChunk(reloadSound, MIX_MAX_VOLUME/20);
	
	PlayMusic();

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/solider run.png", "player",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy3.png", "enemy3", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/solider stand.png", "playerstand", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/bullet.png", "bullet", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/bullet2.png", "bullet2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/bullet3.png", "bullet3", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/bullet4.png", "bullet4", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/crosshair.png", "crosshair", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/boss.png","boss",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/item.png", "item", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/solider death.png","playerdeath", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/boss walk.png", "bosswalk", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/boss attack.png", "bossattack", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/boss idle.png", "bossidle", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/fire.png", "fire", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/explosion.png", "explosion", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/q_circle_on.png", "skill_1_on", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/q_circle_off.png", "skill_1_off", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/e_circle_on.png", "skill_2_on", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/e_circle_off.png", "skill_2_off", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/skill_left.png", "skill_left", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/skill_up.png", "skill_up", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/skill_down.png", "skill_down", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/Skeleton_01_White_Attack1.png", "enemy3attack", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy4.png", "enemy4", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy4attack.png", "enemy4attack", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/health bar red.png", "redbar", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/red bar.png", "redbar2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy5.png", "enemy5", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy5attack.png", "enemy5attack", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy6.png", "enemy6", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/enemy6attack.png", "enemy6attack", GameControl::getInstance()->getRenderer());


	enemys.push_back(new Enemy("enemy3", 200, 200, 96, 64, 10, 50,3)); check_enemy[enemys.back()] = ALIVE;
	bosses.push_back(new Boss("bossidle", 2200, 500, 288, 160, 6)); check_boss[bosses.back()] = ALIVE;
	player1 = new Player("player", 700, 500, 60, 60, 6);
	 crosshair = new Aim("crosshair", 100, 100, 150, 150, 1);
	gameObjects.push_back(player1);
	gameObjects.push_back(crosshair);


	for (int i = 1; i <= 20; i++) {
		items.push_back(new GameItem("item",rand()%2000 , rand()%1640 , 32, 32, 1));
	}
	std::string background = "C:/projectgameSDL/projectgameSDL/source picture/background play.png";
	surface_background = IMG_Load(background.c_str());
	texture_background = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_background);
	std::string bar = "C:/projectgameSDL/projectgameSDL/source picture/health bar origin.png";
	surface_bar = IMG_Load(bar.c_str());
	texture_bar = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), surface_bar);

	// lay player lam trung tam camera
	Camera::getInstance()->SetTarget(player1->GetOrigin());
	// tai score len goc trai
	font2 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source ttf/LibreBaskerville-Bold.ttf", 18);
	render_score();
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);
	

	// tai chu ammo
	font4 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source ttf/LibreBaskerville-Bold.ttf", 18);
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
	ObjectTextureManager::getInstance()->eraseTexture("skill_left");
	ObjectTextureManager::getInstance()->eraseTexture("skill_up");
	ObjectTextureManager::getInstance()->eraseTexture("skill_down");
	ObjectTextureManager::getInstance()->eraseTexture("enemy3attack");
	ObjectTextureManager::getInstance()->eraseTexture("enemy4attack");
	ObjectTextureManager::getInstance()->eraseTexture("enemy4");
	ObjectTextureManager::getInstance()->eraseTexture("enemy5attack");
	ObjectTextureManager::getInstance()->eraseTexture("enemy5");
	ObjectTextureManager::getInstance()->eraseTexture("enemy6");
	ObjectTextureManager::getInstance()->eraseTexture("enemy6attack");

	
	SDL_FreeSurface(textSurface2);
	SDL_FreeSurface(textSurface4);
	SDL_FreeSurface(surface_background);
	SDL_FreeSurface(surface_bar);
	
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(textTexture4);
	SDL_DestroyTexture(texture_background);
	SDL_DestroyTexture(texture_bar);

	Mix_FreeChunk(sound1);
	Mix_FreeChunk(shootingsound);
	Mix_FreeChunk(hurtSound);
	Mix_FreeChunk(reloadSound);

	std::cout << "exting playState\n";
	return true;
}

void PlayState::up_attack() {
	static_cast<Player*>(player1)->buffAttack(2);
}
void PlayState::up_health() {
	static_cast<Player*>(player1)->buffHealth(2);
}
void PlayState::up_ammo() {
	max_ammo += 2;
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
			bullets.push_back(new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame));  check_bullet[bullets.back()] = BULLET_NOT_HIT;
			bullets.back()->fireBullet(crosshair);
			ammo_count--;
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
		Bullet* bullet2 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet2] = BULLET_NOT_HIT;
		Bullet* bullet3 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet3] = BULLET_NOT_HIT;
		Bullet* bullet4 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet4] = BULLET_NOT_HIT;
		if (ammo_count >= 3) {
			ammo_count -= 3;
			bullet2->fireBullet(crosshair);
			bullet3->fireBulletup(crosshair, 10);
			bullet4->fireBulletup(crosshair, -10);
			bullets.push_back(bullet2);
			bullets.push_back(bullet3);
			bullets.push_back(bullet4);
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
		Bullet* bullet = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet] = BULLET_NOT_HIT;
		Bullet* bullet2 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet2] = BULLET_NOT_HIT;
		Bullet* bullet3 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame);  check_bullet[bullet3] = BULLET_NOT_HIT;
		Bullet* bullet4 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet4] = BULLET_NOT_HIT;
		Bullet* bullet5 = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame,bullet_dame); check_bullet[bullet5] = BULLET_NOT_HIT;
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
			Mix_PlayChannel(3, shootingsound, 0);
			next_bullet3= time;
			render_ammo();
		}
	}
}
void PlayState::summon() {
	Vector cam = Camera::getInstance()->GetPosition();
	for (int i = 1; i <= 20; i++) {
		bullets.push_back(new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY() + 10, bullet_w, bullet_h, bullet_frame, bullet_dame));
		check_bullet[bullets.back()] = BULLET_CIRCLE;
		bullets.back()->changeAngle(i * 20);
	}
}
void PlayState::sword_energy_skill() {
	int x = player1->getPos().getX() - Camera::getInstance()->GetPosition().getX();
	int y = player1->getPos().getY() - Camera::getInstance()->GetPosition().getY();
	bullets.push_back( new Bullet("skill_left", x, y, 50, 100, 1,100));
	bullets.back()->changeVelo(Vector(5, 0)); check_bullet[bullets.back()] = 0;
	bullets.push_back(new Bullet("skill_left", x, y, 50, 100, 1,100));
	bullets.back()->changeVelo(Vector(-5, 0));  check_bullet[bullets.back()] = 0;
	bullets.push_back(new Bullet("skill_up", x, y, 100, 50, 1,100));
	bullets.back()->changeVelo(Vector(0, -5)); check_bullet[bullets.back()] = 0;
	bullets.push_back(new Bullet("skill_down", x, y, 100, 50, 1,100));

	bullets.back()->changeVelo(Vector(0, 5)); check_bullet[bullets.back()] = 0;
}
void PlayState::rand_enemy(int type) {
	if (type == 1) {
			int time = SDL_GetTicks();
			if (time - next_create2 >= 500) {
				Vector cam = Camera::getInstance()->GetPosition();
				enemys.push_back(new Enemy("fire", bosses.back()->getPos().getX(), bosses.back()->getPos().getY(), 78, 120, 8, 1,0));
				check_enemy[enemys.back()] = ALIVE;
			}
			next_create2 = time;
	}
	else {
		int ran_num = rand() % 4;
			int time = SDL_GetTicks();
			if (time - next_create >= 1500) {
				if (ran_num ==0) {
					//enemys.push_back(new Enemy("enemy", ranPos().first,ranPos().second, 100, 80, 8, 10)); check_enemy[enemys.back()] = ALIVE;
					enemys.push_back(new Enemy("enemy3", ranPos().first, ranPos().second, 96, 64, 10, 10,3)); check_enemy[enemys.back()] = ALIVE;
				}
				else if (ran_num ==1) {
					//enemys.push_back(new Enemy("enemy2",ranPos().first,ranPos().second, 60, 60, 7, 15));  check_enemy[enemys.back()] = ALIVE;
					enemys.push_back(new Enemy("enemy4", ranPos().first, ranPos().second, 96, 64, 10, 20,4)); check_enemy[enemys.back()] = ALIVE;
				}
				else if (ran_num == 2) {
					enemys.push_back(new Enemy("enemy5", ranPos().first, ranPos().second, 96, 96, 10, 40, 5)); check_enemy[enemys.back()] = ALIVE;
				}
				else {
					enemys.push_back(new Enemy("enemy6", ranPos().first, ranPos().second, 120, 80, 10, 50, 6)); check_enemy[enemys.back()] = ALIVE;
				}
				next_create = time;
			}
	}
	
}
void PlayState::clearBullet() {
	// clear dan trung muc tieu
	for (int i = 0; i < bullets.size(); i++) {
		Vector cam = Camera::getInstance()->GetPosition();
		if (check_bullet[bullets[i]] == BULLET_HIT) {
			bullets[i]->clean();
			bullets.erase(bullets.begin() + i);
			i--;
		}
		else if (abs(bullets[i]->getPos().length() - (player1->getPos() - cam).length()) >= SCREEN_WIDTH) {
			bullets[i]->clean();
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}
}
void PlayState::clearEnemy() {
	// clear enemy bi chet
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == DIE) {
			enemys[i]->clean();
			enemys.erase(enemys.begin() + i);
			i--;
		}
	}
}
void PlayState::clearBoss() {
	for (int i = 0; i < bosses.size(); i++) {
		if (check_boss[bosses[i]] == DIE) {
			bosses[i]->clean();
			bosses.erase(bosses.begin() + i);
			i--;
		}
	}
}
void PlayState::clearItem() {
	for (int i = 0; i < items.size(); i++) {
		if (check_item[items[i]] == 1) {
			items[i]->clean();
			items.erase(items.begin() + i);
			i--;
		}
	}
}