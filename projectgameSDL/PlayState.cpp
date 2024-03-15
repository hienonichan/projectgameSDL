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
Map* map;


// cac bien dieu khien ham random
int ran_num = 0;
int next_create = 0;
bool check_ran = false;

// cac bien dieu khien sinh bullet
int next_bullet = 0;
GameObject* crosshair = nullptr;

void PlayState:: rand_enemy() {
	ran_num = rand() % 1000 + 1;
	if (ran_num) {
		check_ran = true;
	}
	if (check_ran) {
		int time = SDL_GetTicks();
		if (time-next_create >= 2000) {
			if (ran_num<=500) {
				enemys.push_back(new Enemy("enemy", ran_num, ran_num, 100, 80, 8));
			}
			else{
				enemys.push_back(new Enemy("enemy2", ran_num, ran_num, 150, 150, 8));
			}
			check_ran = false;
			next_create = time;
		}
	}
}



void PlayState::update() {
	// random tao enemy
	rand_enemy();

	

	// ban bang crosshair
	if (InputChecker::getInstance()->checkClicked(LEFT)==true) {
		int time = SDL_GetTicks();
		if (time - next_bullet >= 100) {

			Vector cam = Camera::getInstance()->GetPosition();
			Bullet* bullet = new Bullet("bullet", player1->getPos().getX() - cam.getX(), player1->getPos().getY() - cam.getY(), 19, 19, 1);
			bullet->fireBullet(crosshair);
			bullets.push_back(bullet);
			Mix_VolumeChunk(shootingsound, MIX_MAX_VOLUME / 4);
			Mix_PlayChannel(3, shootingsound, 0);
			next_bullet = time;
		}
	}




	// goi lop check bullet ban trung enemy
	for (int i = 0; i < enemys.size(); i++) {
		for (int j = 0; j < bullets.size(); j++) {
			if (CollisionChecker::getInstance()->CollisionBullet(enemys[i], bullets[j])) {
				check_enemy[enemys[i]] = 1;
				check_bullet[bullets[j]]= 1;
			}
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

	// ham clear object toi uu cho game
	clearBullet();
	clearEnemy();


	if (InputChecker::getInstance()->checkKeyboard(SDL_SCANCODE_ESCAPE)) {
		GameControl::getInstance()->getStateManager()->addState(new DelayState());
	}
	Camera::getInstance()->Update();

	


	// neu di chuyen cho  chu bien mat
	if (player1->getVelocity().getX() != 0 || player1->getVelocity().getY() != 0) {
		SDL_SetTextureAlphaMod(textTexture, 0);
	}

}

void PlayState::render() {
	// ve truoc player
	
	Map::getInstance()->DrawMap();


	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}
	for (int i = 0; i < enemys.size(); i++) {
		if (check_enemy[enemys[i]] == 0) {
			enemys[i]->draw();
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
}




bool PlayState::loadState() {
	
	// phat am thanh
	Mix_VolumeChunk(sound1, MIX_MAX_VOLUME / 3);
	PlayMusic();

	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider run.png", "player",GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/zom2.png", "enemy", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/solider stand.png", "playerstand", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/bullet.png", "bullet", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/enemy2.png", "enemy2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/crosshair.png", "crosshair", GameControl::getInstance()->getRenderer());
	player1 = new Player("player", 100, 100, 60, 60, 6);
	 crosshair = new Aim("crosshair", 100, 100, 150, 150, 1);
	gameObjects.push_back(player1);
	gameObjects.push_back(crosshair);
	// lay player lam trung tam camera
	Camera::getInstance()->SetTarget(player1->GetOrigin());


	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/phong chu2.ttf", 45);
	textSurface = TTF_RenderText_Blended(font, "MISSION START", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);


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


