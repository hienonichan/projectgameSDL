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

TTF_Font* font = nullptr;
TTF_Font* font2 = nullptr;
TTF_Font* font3 = nullptr;
TTF_Font* font4 = nullptr;
TTF_Font* font5 = nullptr;
// cac bien dieu khien ham random
int ran_num = 0;
int next_create = 0;
bool check_ran = false;

// cac bien dieu khien sinh bullet
int next_bullet = 0;
int next_reload = 0;
const int max_ammo = 3;
GameObject* crosshair = nullptr;

// thong so cua dan
std::string bullet_id = "bullet";
int bullet_w = 19;
int bullet_h = 19;
int bullet_dame=1;

void PlayState:: rand_enemy() {
	ran_num = ran();
	if (ran_num) {
		check_ran = true;
	}
	if (check_ran) {
		int time = SDL_GetTicks();
		if (time-next_create >= 2000) {
			if (ran_num<=400) {
				enemys.push_back(new Enemy("enemy", ran_num, ran_num, 100, 80, 8));
			}
			else if(ran_num<=900){
				enemys.push_back(new Enemy("enemy2", ran_num, ran_num, 150, 150, 8));
			}
			else {
				bosses.push_back(new Boss("boss", ran_num, ran_num, 300, 200, 10));
			}
			check_ran = false;
			next_create = time;
		}
	}
}



void PlayState::update() {
	// random tao enemy
	rand_enemy();

	

	// het mau chuyen sang GameOver
	if (health <= 0) {
		GameControl::getInstance()->getStateManager()->addState(new GameOver());
	}

	// nap dan 
	if (checkReload()) {
		int time = SDL_GetTicks();
		if (time - next_reload >= 100) {
			if (ammo_count < max_ammo) {
				Mix_PlayChannel(5, reloadSound, 0);
				ammo_count++;
			}

			SDL_FreeSurface(textSurface4);
			SDL_DestroyTexture(textTexture4);
			textSurface4 = TTF_RenderText_Blended(font4, ("AMMO: " + std::to_string(ammo_count)).c_str(), colorText4);
			textTexture4 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface4);
			next_reload = time;
		}
	}


	// ban bang crosshair
	if (InputChecker::getInstance()->checkClicked(LEFT)==true) {
		int time = SDL_GetTicks();
		if (time - next_bullet >= 100) {
			Vector cam = Camera::getInstance()->GetPosition();
			Bullet* bullet = new Bullet(bullet_id, player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY(), bullet_w, bullet_h, 1);
			if(ammo_count>0){
				ammo_count--;

				bullet->fireBullet(crosshair);
				bullets.push_back(bullet);
				Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME / 3);
				Mix_PlayChannel(3, shootingsound, 0);
				next_bullet = time;


				SDL_FreeSurface(textSurface4);
				SDL_DestroyTexture(textTexture4);
				textSurface4 = TTF_RenderText_Blended(font4, ("AMMO: " + std::to_string(ammo_count)).c_str(), colorText4);
				textTexture4 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface4);
			}
			
		}
	}

	// check item sau do change bullet
	for (int i = 0; i < items.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(items[i], player1)) {
			check_item[items[i]] = 1;
			int ran_id = ran() % 4;
			if (ran_id == 0) {
				bullet_id = "bullet";
			}
			else if (ran_id == 1) {
				bullet_id = "bullet2";
			}
			else if (ran_id == 2) {
				bullet_id = "bullet3";
			}
			else {
				bullet_id = "bullet4";
			}
			bullet_w = bullet_h = ran() % 25 + 5;


			if (bullet_w < 10) {
				bullet_dame = 1;
			}
			else if (bullet_w < 15) {
				bullet_dame = 3;
			}
			else {
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
					check_enemy[enemys[j]] = 1;
					
					// cap nhat texture Score
					SDL_FreeSurface(textSurface2);
					SDL_DestroyTexture(textTexture2);
					textSurface2 = TTF_RenderText_Blended(font2, ("SCORE: " + std::to_string(score)).c_str(), colorText2);
					textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
				}
				else {
					enemys[j]->lowHealth(bullet_dame);
				}
				check_bullet[bullets[i]] = 1;
			}
		}

		// check ban trung boss
		for (int z = 0; z < bosses.size(); z++) {
			if (CollisionChecker::getInstance()->CollisionBullet(bosses[z], bullets[i])) {
				if (bosses[z]->getHealth() <= 0) {
					check_boss[bosses[z]] = 1;
					score += 20;

					// neu boss chet thi cap nhat diem
					SDL_FreeSurface(textSurface2);
					SDL_DestroyTexture(textTexture2);
					textSurface2 = TTF_RenderText_Blended(font2, ("SCORE: " + std::to_string(score)).c_str(), colorText2);
					textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
				}
				else {
					bosses[z]->lowHealth(bullet_dame);
				}

				check_bullet[bullets[i]] = 1;
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
			SDL_FreeSurface(textSurface3);
			SDL_DestroyTexture(textTexture3);
			textSurface3 = TTF_RenderText_Blended(font3, ("HEALTH:" + std::to_string(health)).c_str(), colorText3);
			textTexture3 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface3);
		}
	}
	// va cham voi boss
	for (int i = 0; i < bosses.size(); i++) {
		if (CollisionChecker::getInstance()->CollisionEnemy(bosses[i], player1)) {
			Mix_PlayChannel(4, hurtSound, 0);
			health = 0;
			SDL_FreeSurface(textSurface3);
			SDL_DestroyTexture(textTexture3);
			textSurface3 = TTF_RenderText_Blended(font3, ("HEALTH:" + std::to_string(health)).c_str(), colorText3);
			textTexture3 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface3);
		}
	}
	
	




	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
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
		}
	}
	// update cho boss
	for (int i = 0; i < bosses.size(); i++) {
		if (check_boss[bosses[i]] == 0) {
			bosses[i]->update();
			bosses[i]->set_follow(player1);
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


	// neu di chuyen cho  chu bien mat
	if (player1->getVelocity().getX() != 0 || player1->getVelocity().getY() != 0) {
		SDL_SetTextureAlphaMod(textTexture, 0);
		SDL_SetTextureAlphaMod(textTexture5, 0);
	}


	Camera::getInstance()->Update();

}

void PlayState::render() {
	// ve truoc player
	
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
			if (check_bullet[bullets[i]] == 0) {
				bullets[i]->draw();
			}
		}
	}
	



	// hien chu "MISSION START"
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	// cap nhat hien score len man hinh
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture2, NULL, &textRect2);
	// cap nhat health len man hinh
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture3, NULL, &textRect3);
	// cap nhat ammo
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture4, NULL, &textRect4);
	// tai huong dan
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture5, NULL, &textRect5);
}



bool PlayState::loadState() {
	
	// phat am thanh
	Mix_VolumeChunk(sound1, MIX_MAX_VOLUME / 6);
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

	player1 = new Player("player", 100, 100, 60, 60, 6);
	 crosshair = new Aim("crosshair", 100, 100, 150, 150, 1);
	gameObjects.push_back(player1);
	gameObjects.push_back(crosshair);
	for (int i = 1; i <= 20; i++) {
		items.push_back(new GameItem("item",ran() , ran() , 32, 32, 1));
	}

	// lay player lam trung tam camera
	Camera::getInstance()->SetTarget(player1->GetOrigin());


	// tai chu MISSION START
	font=TTF_OpenFont("C:/projectgameSDL/projectgameSDL/phong chu2.ttf", 45); 
	textSurface = TTF_RenderText_Blended(font, "MISSION START", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

    // tai huong dan tro choi
	font5 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/phong chu2.ttf", 25);
	textSurface5 = TTF_RenderText_Blended(font5, "A,W,S,D to move. LEFT MOUSE to shoot. R to reload", colorText5);
	textTexture5 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface5);
	SDL_QueryTexture(textTexture5, NULL, NULL, &textRect5.w, &textRect5.h);


	// tai score len goc trai
	font2 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 30);
	textSurface2 = TTF_RenderText_Blended(font2, ("SCORE:" + std::to_string(score)).c_str(), colorText2);
	textTexture2 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface2);
	SDL_QueryTexture(textTexture2, NULL, NULL, &textRect2.w, &textRect2.h);

	// tai chu health
	font3 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 25);
	textSurface3 = TTF_RenderText_Blended(font3, ("HEALTH:" + std::to_string(health)).c_str(), colorText3);
	textTexture3 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface3);
	SDL_QueryTexture(textTexture3, NULL, NULL, &textRect3.w, &textRect3.h);
     

	// tai chu ammo
	font4 = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/LibreBaskerville-Bold.ttf", 25);
	textSurface4 = TTF_RenderText_Blended(font3, ("AMMO:" + std::to_string(ammo_count)).c_str(), colorText4);
	textTexture4 = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface4);
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
	ObjectTextureManager::getInstance()->eraseTexture("solider stand");
	std::cout << "exting playState\n";
	return true;

}



