#include"UpgradeState.h"
#include"ObjectTextureManager.h"
#include"PlayState.h"

void UpgradeState::update() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->update();
	}
}

void UpgradeState::render() {
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), background_texture, NULL, NULL);
	SDL_RenderCopy(GameControl::getInstance()->getRenderer(), textTexture, NULL, &textRect);
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->draw();
	}

	
}

bool UpgradeState::loadState() {
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/card1.png", "card1", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/card2.png", "card2", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/card3.png", "card3", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/card4.png", "card4", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/card5.png", "card5", GameControl::getInstance()->getRenderer());
	ObjectTextureManager::getInstance()->loadTexture("C:/projectgameSDL/projectgameSDL/source picture/card6.png", "card6", GameControl::getInstance()->getRenderer());

	
     


	GameObject* button1 = new GameButton("card1", 350, 200, 173, 300, 2, upgrade_health);
	GameObject* button2 = new GameButton("card2", 550, 200, 173, 300, 2, upgrade_attack);
	GameObject* button3 = new GameButton("card3", 750, 200, 173, 300, 2, upgrade_ammo);

	GameObject* button4 = new GameButton("card4", 350, 200, 173,300, 2, summon_bullet);
	GameObject* button5 = new GameButton("card5", 550, 200, 173, 300, 2, shotbullet3);
	GameObject* button6 = new GameButton("card6", 750, 200, 173, 300, 2, shotbullet5);
	if (rand_card() == 1) {
		gameObjects.push_back(button1);
		gameObjects.push_back(button2);
		gameObjects.push_back(button3);
	}
	else {
		gameObjects.push_back(button4);
		gameObjects.push_back(button5);
		gameObjects.push_back(button6);
	}

	std::string background = "C:/projectgameSDL/projectgameSDL/source picture/anh ma mi.jpg";
	background_surface = IMG_Load(background.c_str());
	background_texture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), background_surface);

	TTF_Font* font = TTF_OpenFont("C:/projectgameSDL/projectgameSDL/source ttf/LibreBaskerville-Bold.ttf", 30);
	textSurface = TTF_RenderText_Blended(font, "YOU GOT NEW LEVEL! CHOOSE YOUR BOOST", colorText);
	textTexture = SDL_CreateTextureFromSurface(GameControl::getInstance()->getRenderer(), textSurface);
	SDL_QueryTexture(textTexture, NULL, NULL, &textRect.w, &textRect.h);

	std::cout << "loading UpgradeState\n";
	return true;
}

bool UpgradeState::exitState() {
	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->clean();
	}
	gameObjects.clear();

	SDL_FreeSurface(textSurface);
	SDL_FreeSurface(background_surface);

	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(background_texture);
	
	ObjectTextureManager::getInstance()->eraseTexture("card1");
	ObjectTextureManager::getInstance()->eraseTexture("card2");
	ObjectTextureManager::getInstance()->eraseTexture("card3");
	ObjectTextureManager::getInstance()->eraseTexture("card4");
	ObjectTextureManager::getInstance()->eraseTexture("card5");
	ObjectTextureManager::getInstance()->eraseTexture("card6");


	std::cout << "exiting UpgradeState\n";
	return true; 
}



void UpgradeState::upgrade_health() {
	PlayState* check = nullptr;
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	if (check) {
		check->up_health();
	}
	GameControl::getInstance()->getStateManager()->deleteState();
}

void UpgradeState::upgrade_attack() {
	PlayState* check = nullptr;
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	if (check) {
		check->up_attack();
	}
	GameControl::getInstance()->getStateManager()->deleteState();

}

void UpgradeState::upgrade_ammo() {
	PlayState* check = nullptr;
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	if (check) {
		check->up_ammo();
	}
	GameControl::getInstance()->getStateManager()->deleteState();
}

void UpgradeState::summon_bullet() {
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	PlayState* check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	if (check) {
		check->summon();
	}
	GameControl::getInstance()->getStateManager()->deleteState();
}

void UpgradeState::shotbullet3() {
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	PlayState* check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	if (check) {
		check->mode(3);
	}
	GameControl::getInstance()->getStateManager()->deleteState();
}

void UpgradeState::shotbullet5() {
	std::vector<State*>loi = GameControl::getInstance()->getStateManager()->getVectorState();
	PlayState* check = dynamic_cast<PlayState*>(loi[loi.size() - 2]);
	if (check) {
		check->mode(5);
	}
	GameControl::getInstance()->getStateManager()->deleteState();
}